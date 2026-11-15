// Runs web/worker.js (the same file the browser uses) against web/plain.wasm in Node, and checks
// that programs run, errors are explained, `ask` reads typed answers, and the step trace comes out.
//   node tests/wasm_test.js
"use strict";
const fs = require("fs");
const path = require("path");
const root = path.join(__dirname, "..", "web");
if (!fs.existsSync(path.join(root, "plain.wasm"))) { console.log("wasm: skipped (web/plain.wasm is not built: see tools/build-wasm.sh)"); process.exit(0); }

// run worker.js with the few browser things it needs, supplied by Node
function runPlain(args, stdin) {
  return new Promise((resolve, reject) => {
    const messages = [];
    const g = {
      self: {}, postMessage: (m) => { messages.push(m); if (m.type === "done" || m.type === "failed") finish(m); },
      fetch: async (url) => ({ ok: true, status: 200, arrayBuffer: async () => { const b = fs.readFileSync(path.join(root, url)); return b.buffer.slice(b.byteOffset, b.byteOffset + b.byteLength); } }),
    };
    function finish(m) {
      const stdout = messages.filter((x) => x.type === "out" && x.fd === 1).map((x) => x.text).join("");
      const stderr = messages.filter((x) => x.type === "out" && x.fd === 2).map((x) => x.text).join("");
      resolve({ stdout, stderr, last: m });
    }
    const code = fs.readFileSync(path.join(root, "worker.js"), "utf8");
    new Function("self", "postMessage", "fetch", code)(g.self, g.postMessage, g.fetch);
    g.self.onmessage({ data: { args, stdin: stdin || "", wasmUrl: "plain.wasm" } }).catch(reject);
  });
}

let failures = 0;
function check(name, ok, detail) { if (!ok) { failures++; console.log("FAILED: " + name + (detail ? "\n  " + detail : "")); } }

(async () => {
  let r = await runPlain(["-e", 'say "hi"\nsay 6 * 7']);
  check("say works", r.stdout === "hi\n42\n" && r.last.code === 0, JSON.stringify(r));

  r = await runPlain(["-e", "say 1 + \"a\" - 2"]);
  check("errors are explained with the line", /Oops! Line 1/.test(r.stderr) && /1 \| say/.test(r.stderr) && r.last.code === 1, JSON.stringify(r));

  r = await runPlain(["-e", 'ask "Name?" into n\nsay "Hello,", n'], "Asha\n");
  check("ask reads typed answers", r.stdout.includes("Hello, Asha"), JSON.stringify(r));

  r = await runPlain(["-e", 'use "dsa"\nset s to new Stack()\ns\'s push(1)\ns\'s push(2)\nsay s\'s pop()']);
  check("the built-in library works", r.stdout === "2\n", JSON.stringify(r));

  r = await runPlain(["-e", "start_task(action gives 1)"]);
  check("tasks are refused politely", /web playground/.test(r.stderr), JSON.stringify(r));

  r = await runPlain(["-e", "set t to clock()\nwait(0.05)\nsay clock() - t is at least 0.04"]);
  check("wait() sleeps", r.stdout === "true\n", JSON.stringify(r));

  r = await runPlain(["-e", "set x to read_file(\"nope.txt\")"]);
  check("files are not there", r.last.code === 1 && /Oops/.test(r.stderr), JSON.stringify(r));

  r = await runPlain(["visualize", "--json", "-e", "set xs to [3, 1, 2]\nset total to 0\nfor each x in xs\n    increase total by x\nend\nsay total"]);
  let trace = null;
  try { trace = JSON.parse(r.stdout.replace(/<\\\//g, "</")); } catch (e) { /* reported below */ }
  check("the step trace is valid JSON", trace && trace.steps.length >= 5 && trace.out[0] === "6\n", r.stdout.slice(0, 200));

  r = await runPlain(["count", "-e", "define f with n\n    if n is at most 1 then\n        give back n\n    end\n    give back f(n - 1) + f(n - 2)\nend\nsay f(10)"]);
  check("count reports calls", /55/.test(r.stdout) && /calls\s+177/.test(r.stdout), r.stdout);

  r = await runPlain(["-e", "define f with n\n    give back f(n + 1)\nend\nsay f(1)"]);
  check("endless recursion is stopped with an explanation", /keeps calling itself/.test(r.stderr), JSON.stringify(r).slice(0, 300));

  console.log(failures ? failures + " check(s) failed" : "wasm: ok");
  process.exit(failures ? 1 : 0);
})().catch((e) => { console.log("FAILED: " + e.stack); process.exit(1); });
