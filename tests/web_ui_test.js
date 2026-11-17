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
  // colouring that knows what the program defines
  await p.fill("#code", 'class Dog\n    define bark\n        say "Woof"\n    end\nend\ndefine greet with who\n    say who\nend\nset d to new Dog()\nset f to greet\nd\'s bark()\n');
  const names = await p.evaluate(() => {
    const get = (c) => [...document.querySelectorAll("#hl ." + c)].map((e) => e.textContent).join(" ");
    return { def: get("t-def"), cls: get("t-cls"), fn: get("t-fn") };
  });
  ok(names.def === "bark greet", "the names after define are coloured: " + names.def);
  ok(names.cls === "Dog Dog", "class names are coloured, also after new: " + names.cls);
  ok(names.fn === "greet bark", "using a defined action is coloured even without brackets: " + names.fn);
  // typing like a person: end is added, the cursor lands inside, end and otherwise line up
  await p.fill("#code", "");
  await p.click("#code");
  await p.keyboard.type("for i from 1 to 3");
  await p.keyboard.press("Enter");
  ok((await p.inputValue("#code")) === "for i from 1 to 3\n    \nend", "Enter after a block line adds its end: " + JSON.stringify(await p.inputValue("#code")));
  await p.keyboard.type("if i is 2 then");
  await p.keyboard.press("Enter");
  await p.keyboard.type("say i");
  await p.keyboard.press("Enter");
  await p.keyboard.type("otherwise");
  await p.keyboard.press("Enter");
  await p.keyboard.type("say 0");
  const typed = await p.inputValue("#code");
  ok(typed === "for i from 1 to 3\n    if i is 2 then\n        say i\n    otherwise\n        say 0\n    end\nend", "nested blocks get one end each, and otherwise lines up with its if: " + JSON.stringify(typed));
  await p.click("#run");
  await p.waitForFunction(() => !document.getElementById("run").disabled);
  ok((await p.textContent("#output")).replace(/\s+/g, " ").trim() === "0 2 0", "and what was typed runs");
  // pressing Enter after a block that already has its end must not add another
  await p.fill("#code", "if 1 is 1 then\n    say 1\nend\n");
  await p.click("#code");
  await p.keyboard.press("Control+Home");
  await p.keyboard.press("End");
  await p.keyboard.press("Enter");
  ok((await p.inputValue("#code")) === "if 1 is 1 then\n    \n    say 1\nend\n", "no second end when the block is already closed");
  // mistakes are underlined after typing stops, and an unfinished block is only a gentle warning
  await p.fill("#code", "set total to 0\ntotal = 5\nsay total\n");
  await p.waitForSelector("#hl .t-bad", { timeout: 6000 });
  ok((await p.textContent("#liveProblem")).includes("Line 2:") && (await p.textContent("#liveProblem")).includes("start the line with 'set'"), "a mistake is underlined, with its message: " + (await p.textContent("#liveProblem")));
  ok((await p.locator("#gutter .gbad").textContent()) === "2", "and its line number is marked");
  ok((await p.evaluate(() => document.querySelector("#hl .t-bad").textContent)) === "total = 5", "on the right line");
  await p.fill("#code", "set total to 0\nsay total\n");
  await p.waitForSelector("#liveProblem", { state: "hidden", timeout: 6000 });
  ok((await p.locator("#hl .t-bad").count()) === 0, "the underline goes away when it is fixed");
  await p.fill("#code", "set x to 1\nif x is 1 then\n    say x\n");
  await p.waitForSelector("#hl .t-warn", { timeout: 6000 });
  ok((await p.textContent("#liveProblem")).startsWith("Not finished, line 2"), "an unclosed block is a warning, not an error");
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
