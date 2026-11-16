// The playground page (web/index.html) in a real browser, with the interpreter run natively:
// a stand-in for worker.js sends each run to the test, which runs build/plain. So this checks the
// page itself (colouring, blocks, Tidy, saving, lessons) without needing plain.wasm.
//   node tests/web_ui_test.js        (needs Playwright; skipped without it)
let chromium;
try { ({ chromium } = require("playwright")); } catch (e) { console.log("web ui: skipped (no Playwright)"); process.exit(0); }
const { spawnSync } = require("child_process");
const fs = require("fs"), path = require("path"), os = require("os");
const ROOT = path.join(__dirname, ".."), WEB = path.join(ROOT, "web"), PLAIN = path.join(ROOT, "build", "plain");
const FAKE_WORKER = 'self.onmessage = async (e) => {\n' +
  '  const r = await fetch("/__run", { method: "POST", body: JSON.stringify(e.data) }).then((x) => x.json());\n' +
  '  if (r.stdout) postMessage({ type: "out", fd: 1, text: r.stdout });\n' +
  '  if (r.stderr) postMessage({ type: "out", fd: 2, text: r.stderr });\n' +
  '  postMessage({ type: "done", code: r.code });\n};\n';
const TMP = fs.mkdtempSync(path.join(os.tmpdir(), "plain-webui-"));
const results = [];
const ok = (cond, what) => { results.push((cond ? "ok   " : "FAIL ") + what); };
(async () => {
  const b = await chromium.launch();
  const ctx = await b.newContext({ viewport: { width: 1300, height: 950 }, deviceScaleFactor: 1 });
  await ctx.route("http://plain.test/**", async (route) => {
    const url = new URL(route.request().url());
    if (url.pathname === "/__run") {
      const { args, stdin } = JSON.parse(route.request().postData());
      const r = spawnSync(PLAIN, args, { input: stdin || "", encoding: "utf8", cwd: fs.mkdtempSync(path.join(TMP, "run-")) });
      return route.fulfill({ contentType: "application/json", body: JSON.stringify({ stdout: r.stdout, stderr: r.stderr, code: r.status }) });
    }
    if (url.pathname === "/worker.js") return route.fulfill({ contentType: "text/javascript", body: FAKE_WORKER });
    const file = path.join(WEB, url.pathname === "/" ? "index.html" : url.pathname);
    if (url.pathname === "/player.html") return route.fulfill({ contentType: "text/html", body: fs.readFileSync(path.join(ROOT, "lib", "viz", "player.html")) });
    if (!fs.existsSync(file)) return route.fulfill({ status: 404, body: "" });
    return route.fulfill({ contentType: file.endsWith(".html") ? "text/html" : "text/javascript", body: fs.readFileSync(file) });
  });
  const p = await ctx.newPage();
  const errs = [];
  p.on("pageerror", (e) => errs.push(e.message));
  p.on("dialog", (d) => d.accept(d.type() === "prompt" ? "Times table" : undefined));
  await p.goto("http://plain.test/");
  await p.waitForFunction(() => document.getElementById("status").textContent === "Ready");
  ok(true, "page ready");
  // colouring lines up with the text
  await p.fill("#code", '# hi\nset name to "Asha"\nsay "Hello {name}!", 3 + 4\nfor i from 1 to 2\n    say i\nend\n');
  const hl = await p.evaluate(() => ({ text: document.getElementById("hl").textContent, kw: document.querySelectorAll("#hl .t-kw").length,
    ins: document.querySelectorAll("#hl .t-ins").length, hole: document.querySelector("#hl .t-hole") && document.querySelector("#hl .t-hole").textContent,
    com: document.querySelector("#hl .t-com").textContent, code: document.getElementById("code").value }));
  ok(hl.text === hl.code + "\n ", "colouring has exactly the editor's text");
  ok(hl.kw >= 4 && hl.ins >= 3 && hl.hole === "{name}" && hl.com === "# hi", "keywords, instructions, a template hole and a comment are coloured");
  // run
  await p.click("#run");
  await p.waitForFunction(() => !document.getElementById("run").disabled);
  ok((await p.textContent("#output")).includes("Hello Asha! 7"), "Run shows what the program says");
  // tidy
  await p.fill("#code", 'set x to 1\nif x == 1\nprint "one"\nend\n');
  await p.click("#tidy");
  await p.waitForFunction(() => !document.getElementById("tidy").disabled);
  ok((await p.inputValue("#code")) === 'set x to 1\nif x is 1\n    say "one"\nend\n', "Tidy rewrites it in the standard style");
  // blocks
  await p.fill("#code", "");
  await p.click("#blocks button:has-text('repeat')");
  await p.click("#blocks button:has-text('say {name}')");
  const afterBlocks = await p.inputValue("#code");
  ok(afterBlocks.startsWith('repeat 3 times\n    say "Hip hip hooray!"\nend\nsay "Hello, {name}!"'), "blocks go in on their own lines: " + JSON.stringify(afterBlocks));
  // save and open
  await p.fill("#code", "say 6 * 7\n");
  await p.click("#save");
  await p.fill("#code", "say 1\n");
  await p.selectOption("#programs", "Times table");
  ok((await p.inputValue("#code")) === "say 6 * 7\n", "a saved program opens again");
  // lessons
  await p.click("#lessonsBtn");
  await p.waitForSelector(".tile");
  ok((await p.locator(".tile").count()) === 10, "ten lesson tiles");
  await p.locator(".tile").nth(2).click();
  await p.waitForSelector(".exercise");
  ok((await p.inputValue("#code")).startsWith("# Lesson 3, exercise 1: Count to ten"), "the exercise's starter is in the editor");
  await p.locator("#code").press("End");
  await p.fill("#code", (await p.inputValue("#code")) + 'say 1\n');
  await p.click("text=Check my program");
  await p.waitForSelector(".result.bad");
  ok((await p.textContent(".result")).includes("using 'for'"), "a wrong answer is explained");
  await p.click("text=A hint");
  ok((await p.locator(".hints p").count()) === 1, "a hint is shown");
  await p.fill("#code", "for i from 1 to 10\n    say i\nend\n");
  await p.click("text=Check my program");
  await p.waitForSelector(".result.good");
  ok(await p.isVisible("text=Next exercise"), "a right answer unlocks the next exercise");
  await p.click("text=Next exercise");
  await p.waitForFunction(() => document.getElementById("code").value.startsWith("# Lesson 3, exercise 2"));
  ok((await p.inputValue("#stdin")) === "3\n", "the exercise's typed answer is filled in");
  await p.click("text=Try it");
  await p.waitForFunction(() => !document.getElementById("run").disabled);
  ok((await p.textContent("#output")).includes("Hip hip hooray!"), "Try it runs a lesson's example");
  await p.click("#lessonsClose");
  ok((await p.inputValue("#code")) === "say 6 * 7\n", "closing the lessons brings back the program from before");
  await p.reload();
  await p.waitForFunction(() => document.getElementById("status").textContent === "Ready");
  await p.click("#lessonsBtn");
  await p.waitForSelector(".tile");
  ok((await p.locator(".tile").nth(2).textContent()).includes("1 of 4 done"), "lesson progress is kept");
  await p.click("#lessonsClose");
  // phone width: no sideways scrolling
  await p.setViewportSize({ width: 390, height: 800 });
  const wide = await p.evaluate(() => document.documentElement.scrollWidth);
  ok(wide <= 390, "no sideways scroll at phone width (" + wide + ")");
  ok(errs.length === 0, "no page errors " + JSON.stringify(errs));
  await b.close();
  fs.rmSync(TMP, { recursive: true, force: true });
  const failed = results.filter((r) => r.startsWith("FAIL"));
  if (failed.length) { console.log(results.join("\n")); process.exit(1); }
  console.log("web ui: ok (" + results.length + " checks)");
})().catch((e) => { console.log(results.join("\n")); console.log("FAILED (web ui):", e.message); process.exit(1); });
