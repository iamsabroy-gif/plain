// Plain's small Markdown converter, shared by tools/make-pdf.js (the PDFs) and tools/build-docs.js
// (the documentation web site). It handles the part of Markdown the docs use: headings,
// paragraphs, bullet and numbered lists, tables, quotes, fenced code (Plain is coloured), **bold**,
// *italic*, `code` and links. Each caller decides where links go.
"use strict";

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
    const href = ctx.link(target.replace(/&amp;/g, "&"), ctx);
    return href ? hold('<a href="' + href + '">') + label + hold("</a>") : label;
  });
  text = text.replace(/\*\*([^*]+)\*\*/g, "<strong>$1</strong>");
  text = text.replace(/(^|[^*\w])\*([^*\s][^*]*?)\*(?!\w)/g, "$1<em>$2</em>");
  return text.replace(/\u0000(\d+)\u0000/g, (m, i) => holes[+i]);
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

// ctx: { slug: the document's id (headings get ids "slug-heading"),
//        link(target, ctx): the href for a Markdown link target, or null for plain text,
//        afterCode(lang, code): optional extra HTML after each fenced code block }
function convert(markdown, ctx) {
  const doc = { slug: ctx.slug };
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
      html.push("<pre" + cls + "><code>" + (lang.startsWith("plain") ? highlightPlain(code) : esc(code)) + "</code></pre>" + (ctx.afterCode ? ctx.afterCode(lang, code) : ""));
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

module.exports = { KEYWORDS, esc, githubSlug, inline, highlightPlain, convert };
