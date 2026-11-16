// Desktop windows (use "desktop") driven in Chromium: the program runs with PLAIN_NO_BROWSER=1,
// prints its address, and the test plays the person at the window.
//   node tests/desktop_test.js        (needs Playwright; skipped without it)
let chromium;
try { ({ chromium } = require("playwright")); } catch (e) { console.log("desktop: skipped (no Playwright)"); process.exit(0); }
const { spawn } = require("child_process");
const path = require("path");
const ROOT = path.join(__dirname, ".."), PLAIN = path.join(ROOT, "build", "plain");
const results = [];
const ok = (c, what) => results.push((c ? "ok   " : "FAIL ") + what);
function start(file) {
  const p = spawn(PLAIN, [file], { env: Object.assign({}, process.env, { PLAIN_NO_BROWSER: "1" }), cwd: path.dirname(file) });
  p.out = "";
  p.stdout.on("data", (d) => (p.out += d));
  p.stderr.on("data", (d) => (p.out += d));
  p.exited = new Promise((r) => p.on("exit", (code) => r(code)));
  p.url = new Promise((resolve) => { const t = setInterval(() => { const m = p.out.match(/(http:\/\/127\.0\.0\.1:\d+\/\?t=[0-9a-f]+)/); if (m) { clearInterval(t); resolve(m[1]); } }, 50); });
  return p;
}
const within = (promise, ms) => Promise.race([promise, new Promise((r) => setTimeout(() => r("timeout"), ms))]);
(async () => {
  const b = await chromium.launch();
  const errs = [];
  // ---------- the to-do example
  let app = start(path.join(ROOT, "examples", "desktop_todo.plain"));
  let page = await b.newPage({ viewport: { width: 460, height: 560 } });
  page.on("pageerror", (e) => errs.push(e.message));
  await page.goto(await app.url);
  await page.waitForSelector("h1");
  ok((await page.title()) === "To-do", "title");
  const box = page.getByLabel("Something to do");
  for (const t of ["Buy milk", "Walk <the> dog", "Read"]) { await box.fill(t); await box.press("Enter"); }
  await page.waitForFunction(() => document.querySelectorAll("ul.list li").length === 3);
  ok((await page.locator("ul.list li").allTextContents()).join("|") === "Buy milk|Walk <the> dog|Read", "Enter adds tasks (text shown as text, not HTML)");
  ok((await box.inputValue()) === "", "the program cleared the input");
  // typing on while the program is still answering: what the person typed must win
  await page.route("**/event", async (route) => { await new Promise((r) => setTimeout(r, 300)); await route.continue(); });
  for (const t of ["Fast one", "Fast two"]) { await box.fill(t); await box.press("Enter"); }
  await page.waitForFunction(() => document.querySelectorAll("ul.list li").length === 5, null, { timeout: 5000 });
  await page.unroute("**/event");
  ok(true, "typing quickly while the program answers loses nothing");
  for (let k = 0; k < 2; k++) {
    await page.locator("ul.list li", { hasText: "Fast" }).first().click();
    await page.waitForFunction((n) => document.querySelectorAll("ul.list li").length === n, 4 - k);
  }
  ok((await page.textContent("p")).includes("3 to do"), "label updated");
  await page.locator("ul.list li", { hasText: "Walk" }).click();
  await page.waitForFunction(() => document.querySelectorAll("ul.list li").length === 2);
  ok(await page.locator(".toast", { hasText: "Done: Walk <the> dog" }).isVisible(), "picking a task shows a message");
  await box.fill("Half typed");
  await page.getByRole("button", { name: "Add" }).click();
  await page.waitForFunction(() => document.querySelectorAll("ul.list li").length === 3);
  ok(true, "the Add button works");
  await page.reload();
  await page.waitForFunction(() => document.querySelectorAll("ul.list li").length === 3);
  ok(true, "a reload reconnects and keeps the program's state");
  await page.getByRole("button", { name: "Clear all" }).click();
  await page.waitForFunction(() => document.querySelector("ul.list li.empty"));
  ok(true, "Clear all");
  // a hidden (minimised) window checks in rarely: the program must not take that for closed
  await page.evaluate(() => {
    Object.defineProperty(document, "hidden", { configurable: true, get: () => true });
    document.dispatchEvent(new Event("visibilitychange"));
  });
  ok((await within(app.exited, 11000)) === "timeout", "a hidden window keeps the program running");
  await page.evaluate(() => {
    Object.defineProperty(document, "hidden", { configurable: true, get: () => false });
    document.dispatchEvent(new Event("visibilitychange"));
  });
  await box.fill("Back again");
  await box.press("Enter");
  await page.waitForFunction(() => document.querySelectorAll("ul.list li:not(.empty)").length === 1);
  ok(true, "and works again when it is shown");
  await page.close();
  ok((await within(app.exited, 15000)) === 0, "closing the window ends the program");
  // ---------- other widgets, timers, errors, close()
  app = start(path.join(__dirname, "apps", "widgets.plain"));
  page = await b.newPage({ viewport: { width: 500, height: 600 } });
  page.on("pageerror", (e) => errs.push(e.message));
  await page.goto(await app.url);
  await page.waitForSelector("button");
  await page.getByLabel("Big numbers").check();
  await page.getByLabel("Colour").selectOption("blue");
  await page.getByLabel("Age").fill("41");
  await page.getByRole("button", { name: "Report" }).click();
  await page.waitForFunction(() => document.querySelector("p").textContent.includes("big=true"));
  ok((await page.textContent("p")) === "big=true size=1 colour=blue age+1=42", "checkbox, choice and number reach the program: " + (await page.textContent("p")));
  await page.locator("input[type=range]").fill("7");
  await page.waitForFunction(() => document.querySelector("p").textContent.includes("size=7"));
  ok(true, "moving the slider runs its action");
  await page.waitForFunction(() => document.title === "Ticked twice", null, { timeout: 5000 });
  ok(true, "every(seconds) runs a timer");
  await page.getByRole("button", { name: "Break" }).click();
  await page.waitForSelector("#problem:not(.hidden)");
  ok((await page.textContent("#problem")).includes("divide by zero"), "a problem in an action is shown in the window");
  await page.getByRole("button", { name: "Report" }).click();
  await page.waitForSelector("#problem.hidden", { state: "attached" });
  ok(true, "and the window keeps working after it");
  // a request without the window's token is refused
  const port = (await app.url).match(/:(\d+)\//)[1];
  const forged = await page.evaluate(async (port) => (await fetch("http://127.0.0.1:" + port + "/event", { method: "POST", body: "{}" })).status, port);
  ok(forged === 403, "a request without the token is refused (" + forged + ")");
  await page.getByRole("button", { name: "Quit" }).click();
  await page.waitForSelector("#ended");
  ok((await within(app.exited, 5000)) === 0, "close() ends the window and the program goes on");
  ok(app.out.includes("the program carried on after the window closed"), "code after run() runs");
  ok(errs.length === 0, "no page errors " + JSON.stringify(errs));
  await b.close();
  if (results.some((r) => r.startsWith("FAIL"))) { console.log(results.join("\n")); process.exit(1); }
  console.log("desktop: ok (" + results.length + " checks)");
})().catch((e) => { console.log(results.join("\n")); console.log("FAILED (desktop):", e.message); process.exit(1); });
