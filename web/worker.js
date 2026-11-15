// Runs the Plain interpreter (plain.wasm) off the page's main thread, so a program that never
// ends can simply be stopped. Each run starts a fresh copy of the interpreter, so nothing
// leaks from one run into the next.
//
// The interpreter was built for WASI (a tiny "operating system" interface). This file is the
// whole of that interface: where the program writes, what `ask` reads, the clock, and "no files".
"use strict";

let compiled = null;

function loadModule(url) {
  if (!compiled) {
    compiled = fetch(url).then(async (response) => {
      if (!response.ok) throw new Error("I could not load plain.wasm (" + response.status + ").");
      const bytes = await response.arrayBuffer();
      return WebAssembly.compile(bytes);
    });
    compiled.catch(() => { compiled = null; });
  }
  return compiled;
}

class ProcExit {
  constructor(code) { this.code = code; }
}

const ERRNO = { SUCCESS: 0, BADF: 8, NOENT: 44, NOSYS: 52, SPIPE: 70 };

async function runPlain(args, stdin, wasmUrl) {
  const enc = new TextEncoder();
  const decoders = { 1: new TextDecoder("utf-8"), 2: new TextDecoder("utf-8") };
  const argv = ["plain", ...args].map((a) => enc.encode(a + "\0"));
  const input = enc.encode(stdin || "");
  let inputAt = 0;
  let memory = null;
  const view = () => new DataView(memory.buffer);
  const bytes = () => new Uint8Array(memory.buffer);

  const wasi = {
    args_sizes_get(argcPtr, sizePtr) {
      const v = view();
      v.setUint32(argcPtr, argv.length, true);
      v.setUint32(sizePtr, argv.reduce((n, a) => n + a.length, 0), true);
      return ERRNO.SUCCESS;
    },
    args_get(argvPtr, bufPtr) {
      const v = view(), b = bytes();
      for (const a of argv) {
        v.setUint32(argvPtr, bufPtr, true);
        argvPtr += 4;
        b.set(a, bufPtr);
        bufPtr += a.length;
      }
      return ERRNO.SUCCESS;
    },
    environ_sizes_get(countPtr, sizePtr) {
      const v = view();
      v.setUint32(countPtr, 0, true);
      v.setUint32(sizePtr, 0, true);
      return ERRNO.SUCCESS;
    },
    environ_get() { return ERRNO.SUCCESS; },
    clock_res_get(id, resPtr) { view().setBigUint64(resPtr, 1000000n, true); return ERRNO.SUCCESS; },
    clock_time_get(id, precision, timePtr) {
      const ns = id === 0 ? BigInt(Date.now()) * 1000000n : BigInt(Math.round(performance.now() * 1e6));
      view().setBigUint64(timePtr, ns, true);
      return ERRNO.SUCCESS;
    },
    fd_write(fd, iovs, iovsLen, writtenPtr) {
      if (fd !== 1 && fd !== 2) return ERRNO.BADF;
      const v = view(), b = bytes();
      let total = 0, text = "";
      for (let i = 0; i < iovsLen; i++) {
        const ptr = v.getUint32(iovs + i * 8, true), len = v.getUint32(iovs + i * 8 + 4, true);
        text += decoders[fd].decode(b.subarray(ptr, ptr + len), { stream: true });
        total += len;
      }
      if (text) postMessage({ type: "out", fd, text });
      v.setUint32(writtenPtr, total, true);
      return ERRNO.SUCCESS;
    },
    fd_read(fd, iovs, iovsLen, readPtr) {
      if (fd !== 0) return ERRNO.BADF;
      const v = view(), b = bytes();
      let total = 0;
      for (let i = 0; i < iovsLen && inputAt < input.length; i++) {
        const ptr = v.getUint32(iovs + i * 8, true), len = v.getUint32(iovs + i * 8 + 4, true);
        const n = Math.min(len, input.length - inputAt);
        b.set(input.subarray(inputAt, inputAt + n), ptr);
        inputAt += n;
        total += n;
      }
      v.setUint32(readPtr, total, true);
      return ERRNO.SUCCESS;
    },
    fd_fdstat_get(fd, ptr) {
      if (fd > 2) return ERRNO.BADF;
      const v = view();
      v.setUint8(ptr, 2);                      // a terminal-like device
      v.setUint16(ptr + 2, 0, true);
      v.setBigUint64(ptr + 8, 0xFFFFFFFFFFFFFFFFn, true);
      v.setBigUint64(ptr + 16, 0xFFFFFFFFFFFFFFFFn, true);
      return ERRNO.SUCCESS;
    },
    fd_prestat_get() { return ERRNO.BADF; },   // no folders are offered to the program
    fd_prestat_dir_name() { return ERRNO.BADF; },
    fd_close() { return ERRNO.SUCCESS; },
    fd_seek() { return ERRNO.SPIPE; },
    fd_tell() { return ERRNO.SPIPE; },
    fd_sync() { return ERRNO.SUCCESS; },
    fd_datasync() { return ERRNO.SUCCESS; },
    fd_filestat_get() { return ERRNO.BADF; },
    path_open() { return ERRNO.NOENT; },        // there are no files in the browser
    path_filestat_get() { return ERRNO.NOENT; },
    path_unlink_file() { return ERRNO.NOENT; },
    path_create_directory() { return ERRNO.NOSYS; },
    path_remove_directory() { return ERRNO.NOENT; },
    path_rename() { return ERRNO.NOENT; },
    path_readlink() { return ERRNO.NOENT; },
    sched_yield() { return ERRNO.SUCCESS; },
    random_get(ptr, len) {
      const b = bytes();
      for (let at = 0; at < len; at += 65536) crypto.getRandomValues(b.subarray(ptr + at, ptr + Math.min(len, at + 65536)));
      return ERRNO.SUCCESS;
    },
    // Used by wait(seconds). Only timers are supported: sleep, then say they fired.
    poll_oneoff(inPtr, outPtr, nsubs, neventsPtr) {
      const v = view();
      let longest = 0;
      for (let i = 0; i < nsubs; i++) {
        const sub = inPtr + i * 48;
        if (v.getUint8(sub + 8) === 0) {
          const timeout = Number(v.getBigUint64(sub + 24, true)) / 1e6;
          const absolute = (v.getUint16(sub + 40, true) & 1) !== 0;
          const ms = absolute ? timeout - Date.now() : timeout;
          longest = Math.max(longest, ms);
        }
      }
      const end = performance.now() + Math.min(longest, 600000);
      while (performance.now() < end) { /* the program asked to wait */ }
      for (let i = 0; i < nsubs; i++) {
        const ev = outPtr + i * 32, sub = inPtr + i * 48;
        v.setBigUint64(ev, v.getBigUint64(sub, true), true);   // userdata
        v.setUint16(ev + 8, 0, true);                           // no error
        v.setUint8(ev + 10, v.getUint8(sub + 8));               // same kind of event
      }
      v.setUint32(neventsPtr, nsubs, true);
      return ERRNO.SUCCESS;
    },
    proc_exit(code) { throw new ProcExit(code); },
  };
  // anything the program asks for that is not above is politely refused
  const imports = { wasi_snapshot_preview1: new Proxy(wasi, { get: (t, name) => t[name] || (() => ERRNO.NOSYS) }) };

  const module = await loadModule(wasmUrl);
  const instance = await WebAssembly.instantiate(module, imports);
  memory = instance.exports.memory;
  let code = 0;
  try {
    instance.exports._start();
  } catch (e) {
    if (e instanceof ProcExit) code = e.code;
    else throw e;
  }
  for (const fd of [1, 2]) {
    const rest = decoders[fd].decode();
    if (rest) postMessage({ type: "out", fd, text: rest });
  }
  return code;
}

self.onmessage = async (event) => {
  const { args, stdin, wasmUrl } = event.data;
  try {
    const code = await runPlain(args, stdin, wasmUrl);
    postMessage({ type: "done", code });
  } catch (e) {
    let message = String(e && e.message ? e.message : e);
    if (e instanceof RangeError) message = "This program used up all the room it was given (is something calling itself forever?).";
    postMessage({ type: "failed", message });
  }
};
