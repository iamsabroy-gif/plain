// The documentation site (tools/build-docs.js) in a real browser, laid out as GitHub Pages
// publishes it: the playground at / and the documentation at /docs/. The playground's
// interpreter is the native build/plain behind a stand-in worker (as in web_ui_test.js).
//   node tests/docs_site_test.js        (needs Playwright; skipped without it)
let chromium;
try { ({ chromium } = require("playwright")); } catch (e) { console.log("docs site: skipped (no Playwright)"); process.exit(0); }
const { spawnSync, execFileSync } = require("child_process");
const fs = require("fs"), path = require("path"), os = require("os");
const ROOT = path.join(__dirname, ".."), WEB = path.join(ROOT, "web"), PLAIN = path.join(ROOT, "build", "plain");
const TMP = fs.mkdtempSync(path.join(os.tmpdir(), "plain-docs-"));
const SITE = path.join(TMP, "docs");
execFileSync("node", [path.join(ROOT, "tools", "build-docs.js"), SITE], { stdio: "pipe" });
const FAKE_WORKER = 'self.onmessage = async (e) => {\n' +
  '  const r = await fetch("/__run", { method: "POST", body: JSON.stringify(e.data) }).then((x) => x.json());\n' +
  '  if (r.stdout) postMessage({ type: "out", fd: 1, text: r.stdout });\n' +
  '  if (r.stderr) postMessage({ type: "out", fd: 2, text: r.stderr });\n' +
  '  postMessage({ type: "done", code: r.code });\n};\n';
const TYPES = { ".html": "text/html", ".css": "text/css", ".js": "text/javascript", ".json": "application/json" };
const results = [];
const ok = (cond, what) => results.push((cond ? "ok   " : "FAIL ") + what);

(async () => {
  const b = await chromium.launch();
  const ctx = await b.newContext({ viewport: { width: 1300, height: 900 } });
  await ctx.route("http://plain.test/**", async (route) => {
    const url = new URL(route.request().url());
    if (url.pathname === "/__run") {
      const { args, stdin } = JSON.parse(route.request().postData());
      const r = spawnSync(PLAIN, args, { input: stdin || "", encoding: "utf8", cwd: TMP });
      return route.fulfill({ contentType: "application/json", body: JSON.stringify({ stdout: r.stdout, stderr: r.stderr, code: r.status }) });
    }
    if (url.pathname === "/worker.js") return route.fulfill({ contentType: "text/javascript", body: FAKE_WORKER });
    let file;
    if (url.pathname.startsWith("/docs/")) file = path.join(SITE, url.pathname.slice(6) || "index.html");
    else file = path.join(WEB, url.pathname === "/" ? "index.html" : url.pathname);
    if (fs.existsSync(file) && fs.statSync(file).isDirectory()) file = path.join(file, "index.html");
    if (!fs.existsSync(file)) return route.fulfill({ status: 404, body: "not found: " + url.pathname });
    return route.fulfill({ contentType: TYPES[path.extname(file)] || "application/octet-stream", body: fs.readFileSync(file) });
  });
  const p = await ctx.newPage();
  const errs = [];
  p.on("pageerror", (e) => errs.push(e.message));
  p.on("response", (r) => { if (r.status() >= 400 && r.url().startsWith("http://plain.test/")) errs.push(r.status() + " " + r.url()); });

  // the tab from the playground
  await p.goto("http://plain.test/");
  await p.click("nav.tabs >> text=Documentation");
  await p.waitForSelector("h1");
  ok((await p.textContent("h1")) === "Plain documentation", "the Documentation tab opens the docs");
  const groups = await p.locator("main h2").allTextContents();
  ok(["For children", "For adults learning to program", "Building with Plain", "Working on Plain itself"].every((g) => groups.includes(g)), "home has a path for children, adults and developers");

  // every page in the sidebar: loads, has a title, and fits a phone
  const pages = await p.locator("aside li a").evaluateAll((as) => as.map((a) => a.getAttribute("href")));
  ok(pages.length === 13, "13 pages in the sidebar");
  for (const href of pages) {
    await p.goto("http://plain.test/docs/" + href);
    const h1 = await p.locator("main h1").first().textContent();
    if (!h1) ok(false, href + " has a heading");
  }
  await p.setViewportSize({ width: 390, height: 800 });
  const wide = [];
  for (const href of pages) {
    await p.goto("http://plain.test/docs/" + href);
    const w = await p.evaluate(() => document.documentElement.scrollWidth);
    if (w > 390) wide.push(href + " (" + w + ")");
  }
  ok(wide.length === 0, "no page scrolls sideways on a phone " + wide.join(", "));
  await p.goto("http://plain.test/docs/language.html");
  await p.click(".menu");
  ok(await p.isVisible("aside"), "the menu opens on a phone");
  await p.setViewportSize({ width: 1300, height: 900 });

  // search
  await p.goto("http://plain.test/docs/");
  await p.fill("#q", "for each");
  await p.waitForSelector("#results a");
  const n = await p.locator("#results a").count();
  ok(n >= 3, "searching 'for each' finds sections (" + n + ")");
  await p.fill("#q", "web app sessions");
  await p.waitForSelector("#results a");
  ok((await p.locator("#results a").first().textContent()).toLowerCase().includes("session"), "searching finds the sessions section first");
  await p.press("#q", "Enter");
  await p.waitForURL(/apps\.html/);
  ok(true, "Enter opens the result");
  await p.fill("#q", "zzqqxx");
  await p.waitForSelector("#results .none");
  ok(true, "a search with no match says so");

  // the kids' guide, and Try it
  await p.goto("http://plain.test/docs/kids.html");
  ok(await p.evaluate(() => document.body.classList.contains("kids")), "the kids' guide has its own bigger style");
  const firstCode = await p.locator("pre.lang-plain").first().textContent();
  await p.locator("a.try").first().click();
  await p.waitForFunction(() => document.getElementById("status").textContent === "Ready");
  ok((await p.inputValue("#code")).trim() === firstCode.trim(), "Try it opens the example in the playground");
  await p.click("#run");
  await p.waitForFunction(() => !document.getElementById("run").disabled && document.getElementById("output").textContent.trim() !== "");
  ok(!(await p.locator("#output .err").count()), "and it runs without a problem");

  // code in the docs is coloured by what the words are (the same colours as the playground's editor)
  await p.goto("http://plain.test/docs/advanced.html");
  const colours = await p.evaluate(() => ["t-kw", "t-ins", "t-str", "t-def", "t-cls", "t-fn"].filter((c) => document.querySelector("pre ." + c)));
  ok(colours.length === 6, "code blocks use the richer colours: " + colours.join(" "));
  await p.goto("http://plain.test/docs/apps.html");
  ok((await p.locator("pre .t-def").count()) >= 2 && (await p.locator("pre .t-cls").count()) >= 1, "names after define and class stand out in the apps guide too");
  ok((await p.locator("a.try").count()) === 0, "examples that need a network or a window have no Try it button");

  // lessons page and its link into the playground
  await p.goto("http://plain.test/docs/lessons.html");
  ok((await p.locator(".exercise").count()) === 31, "the lessons page has all 31 exercises");
  await p.locator(".doit a", { hasText: "open it in the playground" }).nth(2).click();
  await p.waitForSelector(".exercise h4");
  ok((await p.inputValue("#code")).startsWith("# Lesson 3, exercise 1"), "a lesson link opens that lesson in the playground");

  // practice problems: the problems, never the answers
  await p.goto("http://plain.test/docs/practice.html");
  ok((await p.locator(".problem").count()) === 50, "the practice page has all 50 problems");
  const text = await p.textContent("main");
  ok(!text.includes("__reference") && !text.includes("hidden: ["), "no solutions or hidden tests on the practice page");

  // library and links between pages
  await p.goto("http://plain.test/docs/library.html");
  ok((await p.locator("main h3").count()) === 18, "the library page has every part");
  await p.goto("http://plain.test/docs/core.html");
  await p.click('main a[href^="language.html"]');
  await p.waitForURL(/language\.html/);
  ok(true, "links between guides go to the right page");

  ok(errs.length === 0, "no page errors or missing files " + JSON.stringify(errs.slice(0, 5)));
  await b.close();
  fs.rmSync(TMP, { recursive: true, force: true });
  if (results.some((r) => r.startsWith("FAIL"))) { console.log(results.join("\n")); process.exit(1); }
  console.log("docs site: ok (" + results.length + " checks)");
})().catch((e) => { console.log(results.join("\n")); console.log("FAILED (docs site):", e.message); process.exit(1); });
