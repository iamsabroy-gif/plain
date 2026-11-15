#!/usr/bin/env node
// Builds the documentation as PDF files:
//   docs/pdf/Plain-documentation.pdf   everything: overview, kids' guide, language, advanced, learning, developer, roadmap
//   docs/pdf/Plain-for-kids.pdf        the kids' guide alone, in bigger type
//
//   node tools/make-pdf.js
//
// It needs Node and Playwright's Chromium (the same one the browser tests use); nothing else.
// The Markdown is converted by the small converter below, which handles the part of Markdown the docs use:
// headings, paragraphs, bullet and numbered lists, tables, quotes, fenced code, **bold**, *italic*, `code`, links.
"use strict";
const fs = require("fs");
const path = require("path");

const root = path.join(__dirname, "..");
const outDir = path.join(root, "docs", "pdf");

const DOCS = [
  { file: "README.md", slug: "overview", title: "Overview" },
  { file: "docs/KIDS.md", slug: "kids", title: "Plain for kids" },
  { file: "docs/CORE.md", slug: "core", title: "The beginner core" },
  { file: "docs/LANGUAGE.md", slug: "language", title: "The language" },
  { file: "docs/ADVANCED.md", slug: "advanced", title: "Advanced features" },
  { file: "docs/LEARNING.md", slug: "learning", title: "Learning data structures and algorithms" },
  { file: "docs/DEVELOPER.md", slug: "developer", title: "Developer guide" },
  { file: "docs/ROADMAP.md", slug: "roadmap", title: "Roadmap" },
];
const SITE = "https://github.com/iamsabroy-gif/plain/blob/main/";
const SLUG_OF_FILE = {};
for (const d of DOCS) SLUG_OF_FILE[path.basename(d.file).toLowerCase()] = d.slug;

const KEYWORDS = new Set(("set to say show print ask into add remove from increase decrease by if then otherwise end repeat times while for each in define " +
  "with give back stop skip is not and or greater less than at least most equal contains plus minus multiplied divided modulo length of item " +
  "true false nothing action gives class extends new me parent try on error fail use call").split(" "));

const esc = (s) => s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
const githubSlug = (text) => text.toLowerCase().replace(/<[^>]+>/g, "").replace(/[^\p{L}\p{N}\s_-]/gu, "").trim().replace(/\s+/g, "-");

// ---------------------------------------------------------------- inline
function inline(text, ctx) {
  const holes = [];
  const hold = (html) => { holes.push(html); return "\u0000" + (holes.length - 1) + "\u0000"; };
  // `code` first, so nothing inside it is touched
  text = text.replace(/`([^`]+)`/g, (m, code) => hold("<code>" + esc(code) + "</code>"));
  text = esc(text);
  // [text](target)
  text = text.replace(/\[([^\]]+)\]\(([^)\s]+)\)/g, (m, label, target) => {
    const href = linkTarget(target.replace(/&amp;/g, "&"), ctx);
    return href ? hold('<a href="' + href + '">') + label + hold("</a>") : label;
  });
  text = text.replace(/\*\*([^*]+)\*\*/g, "<strong>$1</strong>");
  text = text.replace(/(^|[^*\w])\*([^*\s][^*]*?)\*(?!\w)/g, "$1<em>$2</em>");
  return text.replace(/\u0000(\d+)\u0000/g, (m, i) => holes[+i]);
}
function linkTarget(target, ctx) {
  if (/^https?:\/\//.test(target) || target.startsWith("mailto:")) return target;
  const m = target.match(/^(?:\.\.\/|\.\/)?(?:docs\/)?([A-Za-z0-9_.-]+\.md)?(#.*)?$/);
  if (!m) return null;
  const file = m[1] ? m[1].toLowerCase() : null;
  const slug = file ? SLUG_OF_FILE[file] : ctx.slug;
  if (!slug) return null;
  // in a PDF that does not contain that document, point at the project's website instead
  if (ctx.only && slug !== ctx.only) {
    const d = DOCS.find((x) => x.slug === slug);
    return SITE + d.file + (m[2] || "");
  }
  return "#" + slug + (m[2] ? "-" + m[2].slice(1) : "");
}

// ----------------------------------------------------------------- blocks
function highlightPlain(code) {
  let out = "", i = 0;
  while (i < code.length) {
    const c = code[i];
    if (c === "#") {
      let j = code.indexOf("\n", i); if (j < 0) j = code.length;
      out += '<span class="c">' + esc(code.slice(i, j)) + "</span>"; i = j;
    } else if (c === '"') {
      let j = i + 1;
      while (j < code.length && code[j] !== '"' && code[j] !== "\n") j += code[j] === "\\" ? 2 : 1;
      j = Math.min(code.length, j + 1);
      out += '<span class="s">' + esc(code.slice(i, j)) + "</span>"; i = j;
    } else if (/[A-Za-z_]/.test(c)) {
      let j = i; while (j < code.length && /[A-Za-z0-9_]/.test(code[j])) j++;
      const w = code.slice(i, j);
      out += KEYWORDS.has(w.toLowerCase()) ? '<span class="k">' + w + "</span>" : esc(w); i = j;
    } else { out += esc(c); i++; }
  }
  return out;
}

function convert(markdown, doc, only) {
  const ctx = { slug: doc.slug, only: only || null };
  const lines = markdown.replace(/\r/g, "").split("\n");
  const html = [];
  const used = {};
  let i = 0;

  const isBlockStart = (l) => /^(#{1,6}\s|```|>|\s*([-*+]|\d+\.)\s|\|)/.test(l) || /^\s*$/.test(l);

  function parseList(indent) {
    const first = lines[i].match(/^(\s*)([-*+]|\d+\.)\s+(.*)$/);
    const ordered = /\d/.test(first[2]);
    const out = [ordered ? "<ol>" : "<ul>"];
    while (i < lines.length) {
      const m = lines[i].match(/^(\s*)([-*+]|\d+\.)\s+(.*)$/);
      if (!m || m[1].length < indent || (m[1].length === indent && /\d/.test(m[2]) !== ordered)) break;
      if (m[1].length > indent) break;
      let text = m[3];
      i++;
      let nested = "";
      for (;;) {
        if (i >= lines.length) break;
        const l = lines[i];
        if (/^\s*$/.test(l)) {
          // a blank line ends the item unless the next line is indented more (still this item)
          const nx = lines[i + 1] || "";
          if (/^\s{2,}\S/.test(nx) && nx.search(/\S/) > indent) { i++; continue; }
          break;
        }
        const nm = l.match(/^(\s*)([-*+]|\d+\.)\s+/);
        if (nm && nm[1].length > indent) { nested += parseList(nm[1].length); continue; }
        if (nm && nm[1].length <= indent) break;
        if (/^\s+\S/.test(l) && l.search(/\S/) > indent) { text += " " + l.trim(); i++; continue; }
        if (!isBlockStart(l)) { text += " " + l.trim(); i++; continue; }
        break;
      }
      out.push("<li>" + inline(text, ctx) + nested + "</li>");
    }
    out.push(ordered ? "</ol>" : "</ul>");
    return out.join("");
  }

  function splitRow(l) {
    l = l.trim().replace(/^\|/, "").replace(/\|$/, "");
    const cells = []; let cur = "";
    for (let k = 0; k < l.length; k++) {
      if (l[k] === "\\" && l[k + 1] === "|") { cur += "|"; k++; }
      else if (l[k] === "|") { cells.push(cur.trim()); cur = ""; }
      else cur += l[k];
    }
    cells.push(cur.trim());
    return cells;
  }

  while (i < lines.length) {
    const line = lines[i];
    let m;
    if (/^\s*$/.test(line)) { i++; continue; }
    if ((m = line.match(/^```([A-Za-z0-9_-]*)\s*$/))) {
      const lang = m[1]; const body = []; i++;
      while (i < lines.length && !lines[i].startsWith("```")) body.push(lines[i++]);
      i++;
      const code = body.join("\n");
      const cls = lang ? ' class="lang-' + lang.replace(/-.*/, "") + (lang.startsWith("plain-") ? " " + lang : "") + '"' : "";
      html.push("<pre" + cls + "><code>" + (lang.startsWith("plain") ? highlightPlain(code) : esc(code)) + "</code></pre>");
      continue;
    }
    if ((m = line.match(/^(#{1,6})\s+(.*?)\s*#*$/))) {
      const level = m[1].length;
      let id = githubSlug(m[2]);
      used[id] = (used[id] || 0) + 1;
      if (used[id] > 1) id += "-" + (used[id] - 1);
      html.push("<h" + level + ' id="' + doc.slug + "-" + id + '">' + inline(m[2], ctx) + "</h" + level + ">");
      i++; continue;
    }
    if (/^\s*([-*+]|\d+\.)\s+/.test(line)) { html.push(parseList(line.match(/^(\s*)/)[1].length)); continue; }
    if (line.startsWith("|") && i + 1 < lines.length && /^\|?\s*:?-{2,}/.test(lines[i + 1])) {
      const head = splitRow(line); i += 2;
      const rows = [];
      while (i < lines.length && lines[i].startsWith("|")) rows.push(splitRow(lines[i++]));
      html.push("<table><thead><tr>" + head.map((c) => "<th>" + inline(c, ctx) + "</th>").join("") + "</tr></thead><tbody>" +
        rows.map((r) => "<tr>" + r.map((c) => "<td>" + inline(c, ctx) + "</td>").join("") + "</tr>").join("") + "</tbody></table>");
      continue;
    }
    if (line.startsWith(">")) {
      const q = [];
      while (i < lines.length && lines[i].startsWith(">")) q.push(lines[i++].replace(/^>\s?/, ""));
      html.push("<blockquote>" + inline(q.join(" "), ctx) + "</blockquote>");
      continue;
    }
    if (/^---+\s*$/.test(line)) { html.push("<hr>"); i++; continue; }
    // a paragraph
    const para = [line.trim()]; i++;
    while (i < lines.length && !isBlockStart(lines[i])) para.push(lines[i++].trim());
    html.push("<p>" + inline(para.join(" "), ctx) + "</p>");
  }
  return html.join("\n");
}

// -------------------------------------------------------------------- pages
const version = (fs.readFileSync(path.join(root, "src", "main.cpp"), "utf8").match(/VERSION = "([^"]+)"/) || [0, "?"])[1];

const BASE_CSS = `
@page { size: A4; margin: 20mm 18mm 22mm 18mm; }
* { box-sizing: border-box; }
html { font-family: "Liberation Sans", "DejaVu Sans", Arial, sans-serif; color: #1c1c1a; }
body { margin: 0; font-size: 10.5pt; line-height: 1.5; }
code, pre { font-family: "DejaVu Sans Mono", "Liberation Mono", monospace; }
code { background: #eef0f6; padding: 0 3px; border-radius: 3px; font-size: .92em; }
pre { background: #f6f6f2; border: 1px solid #dcdcd4; border-radius: 6px; padding: 8px 11px; font-size: 8.8pt; line-height: 1.45; white-space: pre-wrap; word-break: break-word; page-break-inside: avoid; margin: 8px 0 12px; }
pre code { background: none; padding: 0; font-size: inherit; }
pre .k { color: #2748c4; font-weight: 700; } pre .s { color: #1a7f4b; } pre .c { color: #77776f; }
pre.lang-output { background: #fffbea; border-color: #ecd98a; }
pre.lang-output::before { content: "It prints"; display: block; font: 700 7.5pt "Liberation Sans", sans-serif; letter-spacing: .08em; text-transform: uppercase; color: #8a6d00; margin-bottom: 3px; }
pre.lang-input { background: #eef6ff; border-color: #b9d3f2; }
pre.lang-input::before { content: "You type"; display: block; font: 700 7.5pt "Liberation Sans", sans-serif; letter-spacing: .08em; text-transform: uppercase; color: #2b5d9a; margin-bottom: 3px; }
pre.plain-fails { border-left: 4px solid #d6393f; }
pre:has(+ pre.lang-output), pre.lang-input:has(+ pre) { break-after: avoid; }
pre.lang-output { break-before: avoid; }
h1, h2, h3, h4 { line-height: 1.25; page-break-after: avoid; }
h1 { font-size: 22pt; margin: 0 0 10px; padding-bottom: 6px; border-bottom: 3px solid #2f5bea; }
h2 { font-size: 15pt; margin: 20px 0 6px; padding-bottom: 3px; border-bottom: 1px solid #dcdcd4; }
h3 { font-size: 12pt; margin: 15px 0 4px; }
h4 { font-size: 10.5pt; margin: 12px 0 3px; }
p { margin: 6px 0 8px; }
ul, ol { margin: 6px 0 10px; padding-left: 22px; } li { margin: 2px 0; }
a { color: #2748c4; text-decoration: none; }
table { border-collapse: collapse; width: 100%; margin: 8px 0 14px; font-size: 9.2pt; page-break-inside: auto; }
tr { page-break-inside: avoid; }
th, td { border: 1px solid #dcdcd4; padding: 4px 7px; text-align: left; vertical-align: top; }
th { background: #eef0f6; }
blockquote { margin: 10px 0; padding: 7px 12px; background: #eef6ff; border-left: 4px solid #2f5bea; border-radius: 0 6px 6px 0; }
hr { border: 0; border-top: 1px solid #dcdcd4; margin: 14px 0; }
section.doc { page-break-before: always; }
.cover { height: 235mm; display: flex; flex-direction: column; justify-content: center; page-break-after: always; }
.cover .big { font-size: 54pt; font-weight: 800; letter-spacing: -.02em; line-height: 1; }
.cover .sub { font-size: 16pt; color: #55554f; margin: 10px 0 28px; max-width: 150mm; }
.cover .ver { font-size: 11pt; color: #77776f; }
.cover .bar { height: 8px; width: 90mm; background: #2f5bea; border-radius: 4px; margin-bottom: 26px; }
.toc { page-break-after: always; }
.toc h1 { page-break-before: auto; }
.toc ol { list-style: none; padding-left: 0; font-size: 12pt; } .toc li { margin: 7px 0; }
.toc .sec { padding-left: 18px; font-size: 9.5pt; color: #55554f; }
`;
const KIDS_CSS = `
html { font-family: "DejaVu Sans", "Liberation Sans", Arial, sans-serif; }
body { font-size: 13pt; line-height: 1.6; }
h1 { font-size: 30pt; color: #2f5bea; border-bottom: 5px solid #f2b01e; }
h2 { font-size: 19pt; color: #1f9d63; border-bottom: 3px dotted #b9dfc9; margin-top: 26px; }
h3 { font-size: 15pt; color: #d6393f; }
pre { font-size: 11.5pt; padding: 11px 14px; border-radius: 10px; border: 2px solid #cfd3e6; }
pre.lang-output { border-color: #ecd98a; } pre.lang-output::before, pre.lang-input::before { font-size: 9pt; }
code { font-size: .9em; background: #fff2c9; }
pre code { background: none; }
blockquote { background: #fff6dd; border-left-color: #f2b01e; font-size: 12pt; border-radius: 0 10px 10px 0; }
table { font-size: 11.5pt; } th { background: #e6f5ec; }
.cover .big { color: #2f5bea; font-size: 64pt; } .cover .bar { background: linear-gradient(90deg,#2f5bea,#1f9d63,#f2b01e,#d6393f); }
`;

// every in-document link must point at something that exists
function checkLinks(label, html) {
  const ids = new Set([...html.matchAll(/\sid="([^"]+)"/g)].map((m) => m[1]));
  const broken = [...new Set([...html.matchAll(/href="#([^"]+)"/g)].map((m) => m[1]))].filter((id) => !ids.has(id));
  if (broken.length) { console.error(label + ": broken links: " + broken.join(", ")); process.exitCode = 1; }
}

function page(title, body, extraCss) {
  const doc = "<!doctype html><html lang='en'><head><meta charset='utf-8'><title>" + esc(title) + "</title><style>" + BASE_CSS + (extraCss || "") + "</style></head><body>" + body + "</body></html>";
  checkLinks(title, doc);
  return doc;
}

function buildAll() {
  const sections = DOCS.map((d) => {
    const md = fs.readFileSync(path.join(root, d.file), "utf8");
    return { d, html: convert(md, d), md };
  });
  const toc = sections.map(({ d, md }) => {
    const subs = [...md.matchAll(/^##\s+(.*?)\s*$/gm)].map((x) => x[1]).filter((t) => !/^```/.test(t)).slice(0, 14);
    return '<li><a href="#' + d.slug + '">' + esc(d.title) + "</a>" +
      (subs.length ? '<div class="sec">' + subs.map((t) => '<a href="#' + d.slug + "-" + githubSlug(t) + '">' + inline(t, { slug: d.slug }).replace(/<\/?a[^>]*>/g, "") + "</a>").join(" &nbsp;&middot;&nbsp; ") + "</div>" : "") + "</li>";
  }).join("");
  const body =
    '<div class="cover"><div class="bar"></div><div class="big">Plain</div>' +
    '<div class="sub">A programming language that reads like English, made for learning to program and for seeing how data structures and algorithms really work.</div>' +
    '<div class="ver">Documentation for version ' + esc(version) + "</div></div>" +
    '<div class="toc"><h1>Contents</h1><ol>' + toc + "</ol></div>" +
    sections.map(({ d, html }) => '<section class="doc" id="' + d.slug + '">' + html + "</section>").join("\n");
  return page("Plain documentation", body);
}

function buildKids() {
  const d = DOCS.find((x) => x.slug === "kids");
  const html = convert(fs.readFileSync(path.join(root, d.file), "utf8"), d, "kids");
  const body = '<div class="cover"><div class="bar"></div><div class="big">Plain</div><div class="sub">for kids: tell the computer what to do, in words</div><div class="ver">Version ' + esc(version) + "</div></div>" +
    '<section class="doc" id="kids">' + html + "</section>";
  return page("Plain for kids", body, KIDS_CSS);
}

(async () => {
  let chromium;
  try { ({ chromium } = require("playwright")); }
  catch (e) { console.error("This needs Playwright (npm i playwright, then npx playwright install chromium)."); process.exit(1); }
  fs.mkdirSync(outDir, { recursive: true });
  const browser = await chromium.launch();
  const jobs = [
    ["Plain-documentation.pdf", buildAll(), "Plain " + version + " documentation"],
    ["Plain-for-kids.pdf", buildKids(), "Plain for kids"],
  ];
  for (const [name, html, label] of jobs) {
    const page = await browser.newPage();
    await page.setContent(html, { waitUntil: "load" });
    const file = path.join(outDir, name);
    await page.pdf({
      path: file, format: "A4", printBackground: true, preferCSSPageSize: true, outline: true, tagged: true,
      displayHeaderFooter: true, headerTemplate: "<span></span>",
      footerTemplate: '<div style="width:100%;font:8px Liberation Sans,Arial,sans-serif;color:#77776f;padding:0 18mm;display:flex;justify-content:space-between"><span>' + label + '</span><span>page <span class="pageNumber"></span> of <span class="totalPages"></span></span></div>',
      margin: { top: "20mm", bottom: "22mm", left: "18mm", right: "18mm" },
    });
    await page.close();
    console.log("wrote " + path.relative(root, file) + " (" + Math.round(fs.statSync(file).size / 1024) + " KB)");
  }
  await browser.close();
})();
