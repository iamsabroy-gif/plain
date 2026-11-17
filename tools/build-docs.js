#!/usr/bin/env node
// Builds the documentation web site (the "Documentation" tab next to the playground):
//
//   node tools/build-docs.js [out-folder]        (default: web/docs)
//
// One page for each guide in docs/ (and the README as "Getting started"), plus pages made from
// the sources themselves, so they can never go stale: the lessons (plain lesson --json), the
// practice problems (plain practice --json) and the library (the comments at the top of lib/*.plain).
// Every page gets the same sidebar, an "On this page" list, search across the whole site, and a
// "Try it" button on each complete Plain example, which opens it in the playground.
// It needs Node and a built plain (make); nothing else.
"use strict";
const fs = require("fs");
const path = require("path");
const { execFileSync } = require("child_process");
const { esc, githubSlug, inline, convert, highlightPlain } = require("./markdown.js");

const root = path.join(__dirname, "..");
const out = path.resolve(process.argv[2] || path.join(root, "web", "docs"));
const PLAIN = process.env.PLAIN || path.join(root, "build", "plain");
const REPO = "https://github.com/iamsabroy-gif/plain";
const version = (fs.readFileSync(path.join(root, "src", "main.cpp"), "utf8").match(/VERSION = "([^"]+)"/) || [0, "?"])[1];

// ------------------------------------------------------------------ the pages
const GUIDES = [
  { slug: "overview", file: "README.md", title: "Getting started", blurb: "Install Plain, run your first program, and every command in one table." },
  { slug: "kids", file: "docs/KIDS.md", title: "Plain for kids", blurb: "A friendly first guide with things to try and challenges.", kids: true },
  { slug: "core", file: "docs/CORE.md", title: "The first fifteen words", blurb: "The beginner core, the lesson map, and names you can't use." },
  { slug: "language", file: "docs/LANGUAGE.md", title: "The language", blurb: "Values, instructions, numbers, text templates, built-in actions, errors." },
  { slug: "learning", file: "docs/LEARNING.md", title: "Data structures and algorithms", blurb: "Watch programs run, count their work, see how it grows, and the data-structure library." },
  { slug: "apps", file: "docs/APPS.md", title: "Making apps", blurb: "Web sites and APIs with use \"web\", programs with a window with use \"desktop\"." },
  { slug: "advanced", file: "docs/ADVANCED.md", title: "Advanced features", blurb: "Closures, classes, tasks, networking and packages." },
  { slug: "developer", file: "docs/DEVELOPER.md", title: "Developer guide", blurb: "How Plain works inside, how to add to it, tests and releases." },
  { slug: "roadmap", file: "docs/ROADMAP.md", title: "Roadmap", blurb: "What each version brought, and what is left (and why)." },
];
const MADE = {
  lessons: { slug: "lessons", title: "Lessons", blurb: "Ten lessons with exercises, from your first line to how a stack is built." },
  practice: { slug: "practice", title: "Practice problems", blurb: "Fifty classic problems, from arrays to dynamic programming." },
  library: { slug: "library", title: "Library reference", blurb: "Every part of the built-in library: data structures, web and desktop." },
};
const NAV = [
  { group: "Start here", items: ["index", "overview"] },
  { group: "For children", items: ["kids", "lessons"] },
  { group: "Learning to program", items: ["core", "language", "learning", "practice"] },
  { group: "Building with Plain", items: ["apps", "advanced", "library"] },
  { group: "Working on Plain", items: ["developer", "roadmap"] },
];
const PAGES = { index: { slug: "index", title: "Documentation" } };
for (const g of GUIDES) PAGES[g.slug] = g;
for (const k in MADE) PAGES[k] = MADE[k];
const ORDER = NAV.flatMap((g) => g.items);
const hrefOf = (slug) => (slug === "index" ? "./" : slug + ".html");

// ------------------------------------------------------------------ links and code
// A Markdown link from the document at srcFile: another guide becomes its page here; anything
// else in the repository becomes its address on GitHub.
function makeLinker(srcFile) {
  const byFile = {};
  for (const g of GUIDES) byFile[g.file.toLowerCase()] = g.slug;
  return (target, ctx) => {
    if (/^(https?:|mailto:)/.test(target)) return target;
    const [p, hash] = target.split("#");
    if (!p) return "#" + ctx.slug + "-" + hash;  // on this page
    const resolved = path.posix.normalize(path.posix.join(path.posix.dirname(srcFile), p)).replace(/^\.\//, "");
    const slug = byFile[resolved.toLowerCase()];
    if (slug) return hrefOf(slug) + (hash ? "#" + slug + "-" + hash : "");
    if (resolved.startsWith("..")) return null;
    const isDir = !path.extname(resolved) || resolved.endsWith("/");
    return REPO + (isDir ? "/tree/main/" : "/blob/main/") + resolved.replace(/\/$/, "") + (hash ? "#" + hash : "");
  };
}
const playLink = (code) => "../#c=" + Buffer.from(code, "utf8").toString("base64").replace(/\+/g, "-").replace(/\//g, "_").replace(/=+$/, "");
const tryButton = (code) => '<a class="try" href="' + playLink(code.endsWith("\n") ? code : code + "\n") + '">&#9654; Try it in the playground</a>';
const afterCode = (lang, code) => (lang === "plain" ? tryButton(code) : "");

// ------------------------------------------------------------------ data from the sources
function runJson(args) {
  try { return JSON.parse(execFileSync(PLAIN, args, { encoding: "utf8", maxBuffer: 1 << 26 })); }
  catch (e) { console.error("I need a built plain to read the " + args[0] + "s (run make first): " + e.message); process.exit(1); }
}

// Teaching text of a lesson: paragraphs, and code (indented four spaces) that can be tried.
function lessonText(text, ctx) {
  const outp = [];
  let para = [], code = [];
  const flush = () => {
    if (para.length) outp.push("<p>" + inline(para.join(" "), ctx) + "</p>");
    if (code.length) {
      const src = code.join("\n");
      outp.push('<pre class="lang-plain"><code>' + highlightPlain(src) + "</code></pre>" + tryButton(src));
    }
    para = []; code = [];
  };
  for (const line of text.split("\n")) {
    if (line.startsWith("    ")) { if (para.length) { outp.push("<p>" + inline(para.join(" "), ctx) + "</p>"); para = []; } code.push(line.slice(4)); }
    else if (!line.trim()) flush();
    else { if (code.length) flush(); para.push(line.trim()); }
  }
  flush();
  return outp.join("\n");
}

function lessonsPage() {
  const { lessons } = runJson(["lesson", "--json"]);
  const ctx = { slug: "lessons", link: makeLinker("docs/LESSONS.md") };
  let h = "<h1>Lessons</h1>\n<p class=\"lead\">Ten lessons for beginners of any age. Each one explains a few new words, shows them working, and gives you exercises. Plain checks your answers: in the <a href=\"../\">playground</a> (press <b>Lessons</b>), or on your computer with <code>plain lesson 1</code>.</p>\n";
  h += '<div class="tiles">' + lessons.map((L) => '<a class="tile" href="#lessons-lesson-' + L.number + '"><span class="pic">' + esc(L.picture || "") + '</span><span class="num">Lesson ' + L.number + '</span><span class="name">' + esc(L.title) + "</span></a>").join("") + "</div>\n";
  for (const L of lessons) {
    h += '<h2 id="lessons-lesson-' + L.number + '"><span class="pic">' + esc(L.picture || "") + "</span> Lesson " + L.number + ": " + esc(L.title) + "</h2>\n";
    h += lessonText(L.teach, ctx);
    h += '<p class="doit">Do this lesson with checking: <a href="../#lesson=' + L.number + '">open it in the playground</a>, or type <code>plain lesson ' + L.number + "</code>.</p>\n";
    L.exercises.forEach((ex, i) => {
      h += '<div class="exercise"><h3 id="lessons-' + L.number + "-" + (i + 1) + '">Exercise ' + L.number + "." + (i + 1) + ": " + esc(ex.title) + "</h3>\n";
      h += "<p>" + inline(ex.task, ctx) + "</p>\n";
      if (ex.input) h += '<pre class="lang-input"><code>' + esc(ex.input.trim()) + "</code></pre>\n";
      h += '<pre class="lang-output"><code>' + esc(ex.output.replace(/\n$/, "")) + "</code></pre>\n";
      if (ex.hints.length) h += "<details><summary>Hints</summary><ol>" + ex.hints.map((t) => "<li>" + inline(t, ctx) + "</li>").join("") + "</ol></details>\n";
      h += '<details><summary>A program that works (try it yourself first!)</summary><pre class="lang-plain"><code>' + highlightPlain(ex.solution.replace(/\n$/, "")) + "</code></pre>" + tryButton(ex.solution) + "</details>\n</div>\n";
    });
  }
  return h;
}

function practicePage() {
  const { problems } = runJson(["practice", "--json"]);
  let h = "<h1>Practice problems</h1>\n<p class=\"lead\">Fifty classic problems, from arrays to dynamic programming. Start one on your computer with <code>plain practice two-sum</code>: Plain writes a file with the problem in it, then checks your answer against the examples <i>and</i> hidden tests, gives hints one at a time, and shows a reference solution with an explanation once you have earned it. (So this page shows the problems, never the answers.)</p>\n";
  const topics = [];
  for (const p of problems) if (!topics.includes(p.topic)) topics.push(p.topic);
  h += '<p class="chips">' + topics.map((t) => '<a href="#practice-' + githubSlug(t) + '">' + esc(t) + "</a>").join("") + "</p>\n";
  for (const t of topics) {
    h += '<h2 id="practice-' + githubSlug(t) + '">' + esc(t[0].toUpperCase() + t.slice(1)) + "</h2>\n";
    for (const p of problems.filter((x) => x.topic === t)) {
      h += '<div class="problem"><h3 id="practice-' + p.id + '">' + esc(p.title) + ' <span class="level" title="level ' + p.level + ' of 3">' + "&#9733;".repeat(p.level) + "</span></h3>\n";
      h += "<p>" + esc(p.statement) + "</p>\n";
      h += "<p>Write <code>define " + esc(p.action) + " with " + esc(p.params) + "</code>.</p>\n";
      h += "<table><thead><tr><th>Example</th><th>Gives back</th></tr></thead><tbody>" + p.examples.map((e) => "<tr><td><code>" + esc(e.call) + "</code></td><td><code>" + esc(e.gives) + "</code></td></tr>").join("") + "</tbody></table>\n";
      h += '<p class="muted">' + p.hidden_tests + " hidden tests, " + p.hints + " hints" + (p.complexity ? ". A good solution is " + esc(p.complexity) : "") + ". Start it with <code>plain practice " + esc(p.id) + "</code></p></div>\n";
    }
  }
  return h;
}

// The first comment block of a library file is written for learners: show it, as it is.
function libraryPage() {
  const parts = [
    ["Data structures", ["stack", "queue", "deque", "ringbuffer", "counter", "unique", "heap", "linkedlist", "tree", "avl", "trie", "graph", "unionfind", "lrucache", "fenwick", "segmenttree"]],
    ["Making apps", ["web", "desktop"]],
  ];
  let h = "<h1>Library reference</h1>\n<p class=\"lead\">Every part of the built-in library is written in Plain, so you can read how it works: <code>plain lib stack</code> prints it, and <code>plain lib stack --copy</code> puts a copy next to your program to change. Load a part with <code>use \"stack\"</code> (or all the data structures with <code>use \"dsa\"</code>).</p>\n";
  for (const [group, names] of parts) {
    h += '<h2 id="library-' + githubSlug(group) + '">' + esc(group) + "</h2>\n";
    for (const name of names) {
      const file = path.join(root, "lib", name + ".plain");
      if (!fs.existsSync(file)) continue;
      const lines = fs.readFileSync(file, "utf8").split("\n");
      const doc = [];
      for (const l of lines) { if (!l.startsWith("#")) break; doc.push(l.replace(/^# ?/, "")); }
      h += '<h3 id="library-' + name + '"><code>use "' + name + '"</code></h3>\n';
      h += '<pre class="libdoc"><code>' + esc(doc.join("\n").trim()) + "</code></pre>\n";
      h += '<p class="muted">Read all of it: <code>plain lib ' + name + '</code>, or <a href="' + REPO + "/blob/main/lib/" + name + '.plain">lib/' + name + ".plain</a> on GitHub.</p>\n";
    }
  }
  return h;
}

function homePage() {
  const card = (slug) => { const p = PAGES[slug]; return '<a class="card" href="' + hrefOf(slug) + '"><b>' + esc(p.title) + "</b><span>" + esc(p.blurb || "") + "</span></a>"; };
  const hello = 'set name to "Asha"\nsay "Hello, {name}!"\n\nrepeat 3 times\n    say "Hip hip hooray!"\nend\n';
  return '<div class="hero"><h1>Plain documentation</h1><p class="lead">Plain is a programming language that reads like English, made for learning to program and for seeing how data structures and algorithms really work. Everything you need to learn it, and to build with it, is here.</p>' +
    '<pre class="lang-plain"><code>' + highlightPlain(hello.trim()) + "</code></pre>" + tryButton(hello) + "</div>\n" +
    '<h2 id="index-for-children">For children</h2><p>Start with the friendly guide, then follow the lessons with pictures. A grown-up can help with the first few.</p><div class="cards kids-cards">' + card("kids") + card("lessons") + "</div>\n" +
    '<h2 id="index-for-adults">For adults learning to program</h2><p>The same lessons work for every age. Then the language in full, and Plain\'s tools for understanding algorithms: watch your code run, count its work, see how it grows.</p><div class="cards">' + card("core") + card("lessons") + card("language") + card("learning") + card("practice") + "</div>\n" +
    '<h2 id="index-building">Building with Plain</h2><p>Make web sites and programs with a window, and use classes, tasks, networking and packages.</p><div class="cards">' + card("apps") + card("advanced") + card("library") + card("overview") + "</div>\n" +
    '<h2 id="index-developing">Working on Plain itself</h2><p>How the compiler and virtual machine work, how to add built-in actions, lessons and problems, and what comes next.</p><div class="cards">' + card("developer") + card("roadmap") + "</div>\n" +
    '<h2 id="index-pdf">To print or read offline</h2><p>All of this as PDF files: <a href="' + REPO + '/raw/main/docs/pdf/Plain-documentation.pdf">the complete documentation</a> and <a href="' + REPO + '/raw/main/docs/pdf/Plain-for-kids.pdf">Plain for kids</a> (in bigger type).</p>\n';
}

// ------------------------------------------------------------------ the page around the content
function shell(slug, content) {
  const p = PAGES[slug];
  const toc = [...content.matchAll(/<h2 id="([^"]+)">([\s\S]*?)<\/h2>/g)].map((m) => '<li><a href="#' + m[1] + '">' + m[2].replace(/<[^>]+>/g, "") + "</a></li>").join("");
  const nav = NAV.map((g) => '<div class="group"><div class="gname">' + esc(g.group) + "</div><ul>" +
    g.items.map((s) => '<li><a href="' + hrefOf(s) + '"' + (s === slug ? ' aria-current="page"' : "") + ">" + esc(PAGES[s].title) + "</a></li>").join("") + "</ul></div>").join("");
  const at = ORDER.indexOf(slug), prev = ORDER[at - 1], next = ORDER[at + 1];
  const pager = '<nav class="pager" aria-label="Previous and next">' + (prev ? '<a class="prev" href="' + hrefOf(prev) + '"><span>Previous</span>' + esc(PAGES[prev].title) + "</a>" : "<span></span>") +
    (next ? '<a class="next" href="' + hrefOf(next) + '"><span>Next</span>' + esc(PAGES[next].title) + "</a>" : "<span></span>") + "</nav>";
  const source = p.file ? '<a href="' + REPO + "/blob/main/" + p.file + '">Change this page on GitHub</a>' : "";
  const title = slug === "index" ? "Plain documentation" : p.title + " - Plain documentation";
  return '<!doctype html>\n<html lang="en">\n<head>\n<meta charset="utf-8">\n<meta name="viewport" content="width=device-width, initial-scale=1">\n' +
    "<title>" + esc(title) + '</title>\n<meta name="description" content="' + esc(p.blurb || "Learn the Plain programming language, and build with it.") + '">\n' +
    '<link rel="stylesheet" href="site.css">\n</head>\n<body' + (p.kids ? ' class="kids"' : "") + ">\n" +
    '<a class="skip" href="#content">Skip to the page</a>\n' +
    '<header class="top"><a class="brand" href="../">Plain</a>' +
    '<nav class="tabs" aria-label="Site"><a href="../">Playground</a><a href="./" aria-current="page">Documentation</a></nav>' +
    '<span class="ver">version ' + esc(version) + '</span><a class="gh" href="' + REPO + '">GitHub</a>' +
    '<button class="menu" aria-expanded="false" aria-controls="side">Menu</button></header>\n' +
    '<div class="layout">\n<aside id="side"><div class="search"><label for="q">Search the documentation</label><input id="q" type="search" placeholder="Search, like: for each" autocomplete="off"><div id="results" role="listbox" hidden></div></div>' + nav + "</aside>\n" +
    '<main id="content">\n' + content + "\n" + pager + '<p class="foot">' + source + "</p>\n</main>\n" +
    (toc ? '<nav class="toc" aria-label="On this page"><div class="gname">On this page</div><ul>' + toc + "</ul></nav>\n" : "") +
    '</div>\n<script src="site.js"></script>\n</body>\n</html>\n';
}

// ------------------------------------------------------------------ build
const pages = {};
pages.index = homePage();
for (const g of GUIDES) {
  let md = fs.readFileSync(path.join(root, g.file), "utf8");
  pages[g.slug] = convert(md, { slug: g.slug, link: makeLinker(g.file), afterCode })
    // a link that shows a file name (right on GitHub) shows the page's title here
    .replace(/<a href="([a-z]+)\.html([^"]*)">(?:docs\/)?[A-Za-z]+\.md<\/a>/g, (m, slug, rest) => PAGES[slug] ? '<a href="' + slug + ".html" + rest + '">' + esc(PAGES[slug].title) + "</a>" : m);
}
pages.lessons = lessonsPage();
pages.practice = practicePage();
pages.library = libraryPage();

fs.mkdirSync(out, { recursive: true });
const index = [];
let problems = 0;
for (const slug of ORDER) {
  const html = shell(slug, pages[slug]);
  fs.writeFileSync(path.join(out, (slug === "index" ? "index" : slug) + ".html"), html);
  // search: one entry for each section (an h2 or h3 and the text after it)
  const parts = pages[slug].split(/(?=<h[123] id=")/);
  for (const part of parts) {
    const m = part.match(/^<h[123] id="([^"]+)">([\s\S]*?)<\/h[123]>/);
    const heading = m ? m[2].replace(/<[^>]+>/g, "").trim() : PAGES[slug].title;
    const text = part.replace(/^<h[123][^>]*>[\s\S]*?<\/h[123]>/, "").replace(/<(script|style)[\s\S]*?<\/\1>/g, "").replace(/<[^>]+>/g, " ")
      .replace(/&amp;/g, "&").replace(/&lt;/g, "<").replace(/&gt;/g, ">").replace(/&quot;/g, '"').replace(/&#39;/g, "'").replace(/&#9654;|&#9733;/g, "").replace(/\s+/g, " ").trim();
    if (!text && !m) continue;
    index.push({ p: PAGES[slug].title, u: (slug === "index" ? "./" : slug + ".html") + (m ? "#" + m[1] : ""), h: heading, t: text.slice(0, 600) });
  }
  // every link inside the site must lead somewhere
  for (const [, href] of html.matchAll(/href="([^"]+)"/g)) {
    if (/^(https?:|mailto:|\.\.\/)/.test(href) || href === "site.css") continue;
    const [file, hash] = href.split("#");
    const target = file === "" ? html : file === "./" ? shell("index", pages.index) : fs.existsSync(path.join(out, file)) ? fs.readFileSync(path.join(out, file), "utf8") : (ORDER.includes(file.replace(".html", "")) ? shell(file.replace(".html", ""), pages[file.replace(".html", "")]) : null);
    if (target === null) { console.error(slug + ": link to a missing page: " + href); problems++; continue; }
    if (hash && !target.includes('id="' + hash + '"')) { console.error(slug + ": link to a missing place: " + href); problems++; }
  }
}
// a script rather than JSON, so that search also works from a folder opened without a web server
fs.writeFileSync(path.join(out, "search-index.js"), "window.PLAIN_SEARCH = " + JSON.stringify(index).replace(/<\//g, "<\\/") + ";\n");
fs.copyFileSync(path.join(__dirname, "docs-site", "site.css"), path.join(out, "site.css"));
fs.copyFileSync(path.join(__dirname, "docs-site", "site.js"), path.join(out, "site.js"));
console.log("wrote " + ORDER.length + " pages and " + index.length + " search entries to " + path.relative(process.cwd(), out) + (problems ? " (" + problems + " broken links)" : ""));
if (problems) process.exitCode = 1;
