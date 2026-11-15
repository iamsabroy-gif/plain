// Opens the real playground (web/) in a real browser, with the real plain.wasm, and uses it like a person would.
// Skipped when plain.wasm is not built or Playwright is not installed.   node tests/web_e2e.js
"use strict";
const fs = require("fs"), path = require("path"), http = require("http");
const root = path.join(__dirname, "..", "web");
if (!fs.existsSync(path.join(root, "plain.wasm")) || !fs.existsSync(path.join(root, "player.html"))) { console.log("web e2e: skipped (web/plain.wasm is not built)"); process.exit(0); }
let chromium;
try { ({ chromium } = require("playwright")); } catch (e) { console.log("web e2e: skipped (Playwright is not installed)"); process.exit(0); }

const types = { ".html": "text/html", ".js": "text/javascript", ".wasm": "application/wasm" };
const server = http.createServer((req, res) => {
  const f = path.join(root, req.url === "/" ? "index.html" : req.url.split("?")[0]);
  if (!f.startsWith(root) || !fs.existsSync(f)) { res.statusCode = 404; return res.end(); }
  res.setHeader("content-type", types[path.extname(f)] || "application/octet-stream");
  res.end(fs.readFileSync(f));
});
let failures = 0;
const check = (name, ok, detail) => { if (!ok) { failures++; console.log("FAILED: " + name + (detail ? "\n  " + detail : "")); } };

server.listen(0, "127.0.0.1", async () => {
  const url = "http://127.0.0.1:" + server.address().port + "/";
  const browser = await chromium.launch();
  try {
    const page = await browser.newPage({ viewport: { width: 1280, height: 900 } });
    const errors = [];
    page.on("pageerror", (e) => errors.push(e.message));
    await page.goto(url);
    await page.waitForFunction(() => !document.getElementById("run").disabled, null, { timeout: 15000 });
    const text = () => page.textContent("#output");
    const until = (needle, ms) => page.waitForFunction((n) => document.getElementById("output").textContent.includes(n), needle, { timeout: ms || 15000 });

    await page.click("#run"); await until("42");
    check("the first example runs", (await text()).includes("Hello, world!"), await text());

    await page.fill("#code", "set xs to [1, 2]\nsay xs[5]\n"); await page.click("#run"); await until("Oops");
    check("an error is explained with its line", /Line 2/.test(await text()) && /no item 5/.test(await text()), await text());

    await page.fill("#code", 'ask "Name?" into n\nsay "Hello,", n\n');
    await page.evaluate(() => { document.querySelector("details").open = true; });
    await page.fill("#stdin", "Asha"); await page.click("#run"); await until("Hello, Asha");

    await page.fill("#code", 'use "dsa"\nset q to new Queue()\nq\'s enqueue(1)\nsay q\'s dequeue()\n'); await page.click("#run"); await until("1");
    check("the library loads", !/Oops/.test(await text()), await text());

    await page.selectOption("#examples", "Sort a list (watch it!)");
    await page.click("#watch");
    await page.waitForFunction(() => !document.getElementById("vizCard").hidden, null, { timeout: 15000 });
    const frame = page.frameLocator("#vizFrame");
    await frame.locator("#next").click();
    await page.waitForTimeout(300);
    check("the step viewer works", /step 2 of \d+/.test(await frame.locator("#count").textContent()));
    await page.click("#closeViz");

    await page.click("#count"); await until("comparisons");

    // a program that talks without end is stopped by the page itself, with an explanation
    await page.fill("#code", 'while true\n    say "x"\nend\n'); await page.click("#run");
    await until("said far too much", 20000);
    await page.waitForFunction(() => !document.getElementById("run").disabled, null, { timeout: 5000 });
    check("a flood of output is stopped", (await text()).length < 400000);

    // a silent endless loop is ended with the Stop button
    await page.fill("#code", 'set n to 0\nwhile true\n    increase n by 1\nend\n'); await page.click("#run");
    await page.waitForSelector("#stop:not([hidden])"); await page.waitForTimeout(400); await page.click("#stop");
    await page.waitForFunction(() => !document.getElementById("run").disabled, null, { timeout: 5000 });
    await page.fill("#code", 'say "alive"'); await page.click("#run"); await until("alive");
    check("Stop ends an endless loop and the page keeps working", true);

    const m = await browser.newPage({ viewport: { width: 390, height: 844 } });
    await m.goto(url); await m.waitForFunction(() => !document.getElementById("run").disabled);
    check("no sideways scrolling on a phone", !(await m.evaluate(() => document.documentElement.scrollWidth > innerWidth)));
    check("no errors in the page", errors.length === 0, errors.join("\n"));
  } catch (e) { failures++; console.log("FAILED: " + e.message); }
  await browser.close();
  server.close();
  console.log(failures ? failures + " check(s) failed" : "web e2e: ok");
  process.exit(failures ? 1 : 0);
});
