// How Plain code is coloured and how its blocks are counted. One file, used by the playground's
// editor (web/index.html), the documentation site and the PDFs (tools/markdown.js), so they agree.
// It reads words, not a parse tree: quick enough to run on every key press.
//
//   PlainSyntax.highlight(code)           HTML for a whole program (spans with classes t-kw, t-ins ...)
//   PlainSyntax.names(code)               the actions and classes the program defines
//   PlainSyntax.paintLine(line, names)    HTML for one line
//   PlainSyntax.opensBlock(line)          does this line open a block that needs an `end`?
//   PlainSyntax.unclosedBlocks(code)      blocks opened minus `end`s, over the whole program
//   PlainSyntax.indentsAfter(line)        should the next line be indented one more step?
//   PlainSyntax.matchingIndent(lines, i)  the indent of the line that opened the block line i ends
"use strict";
(function (root, factory) {
  if (typeof module === "object" && module.exports) module.exports = factory();
  else root.PlainSyntax = factory();
})(this, function () {
  const KW = new Set("if then otherwise end repeat times while for each in from to by stop skip give back try on error fail use call init class extends new action gives define with".split(" "));
  const INS = new Set("set say show print ask into add remove increase decrease".split(" "));
  const OPW = new Set("is not and or greater less than at least most equal contains plus minus multiplied divided modulo length of item".split(" "));
  const LIT = new Set(["true", "false", "nothing"]);
  const ME = new Set(["me", "parent"]);
  const ID = "[A-Za-z_\\u0080-\\uFFFF][A-Za-z0-9_\\u0080-\\uFFFF]*";
  const TOKEN = new RegExp("(\\d+(?:\\.\\d+)?(?:[eE][+-]?\\d+)?d?)|(" + ID + ")(\\s*\\()?|('s\\b)|([^A-Za-z0-9_\\u0080-\\uFFFF']+|')", "g");

  const esc = (t) => t.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
  const span = (cls, t) => '<span class="' + cls + '">' + esc(t) + "</span>";

  // The actions and classes a program defines (so that using them is coloured even without a "(").
  function names(code) {
    const fns = new Set(), classes = new Set();
    for (const m of code.matchAll(new RegExp("^\\s*define\\s+(" + ID + ")", "gim"))) fns.add(m[1]);
    for (const m of code.matchAll(new RegExp("^\\s*class\\s+(" + ID + ")", "gim"))) classes.add(m[1]);
    return { fns, classes };
  }
  const NONE = { fns: new Set(), classes: new Set() };

  // One piece of code (no strings or comments inside: those are found first).
  function paintCode(code, known) {
    known = known || NONE;
    let expect = null;  // after define: an action's name; after class, extends, new: a class's name
    return code.replace(TOKEN, (m, num, word, call, poss, other) => {
      if (num) { expect = null; return span("t-num", num); }
      if (poss) { expect = null; return span("t-op", poss); }
      if (other !== undefined) { if (/\S/.test(other)) expect = null; return esc(other); }
      const w = word.toLowerCase(), rest = call ? esc(call) : "";
      if (expect && !KW.has(w) && !INS.has(w) && !OPW.has(w) && !LIT.has(w) && !ME.has(w)) {
        const cls = expect === "fn" ? "t-def" : "t-cls";
        expect = null;
        return span(cls, word) + rest;
      }
      expect = w === "define" ? "fn" : (w === "class" || w === "extends" || w === "new") ? "cls" : null;
      if (KW.has(w)) return span("t-kw", word) + rest;
      if (INS.has(w)) return span("t-ins", word) + rest;
      if (OPW.has(w)) return span("t-op", word) + rest;
      if (LIT.has(w)) return span("t-lit", word) + rest;
      if (ME.has(w)) return span("t-me", word) + rest;
      if (known.classes.has(word)) return span("t-cls", word) + rest;
      if (known.fns.has(word) || call) return span("t-fn", word) + rest;
      return esc(word);
    });
  }

  // Text, with the {values} inside it coloured as code.
  function paintText(t, known) {
    let out = "", i = 0;
    while (i < t.length) {
      if (t[i] === "\\" && i + 1 < t.length) { out += esc(t.slice(i, i + 2)); i += 2; continue; }
      if (t[i] === "{" && /[A-Za-z_(\[0-9-]/.test(t[i + 1] || "")) {
        const close = t.indexOf("}", i);
        if (close > 0) { out += '</span><span class="t-hole">{' + paintCode(t.slice(i + 1, close), known) + '}</span><span class="t-str">'; i = close + 1; continue; }
      }
      out += esc(t[i]); i++;
    }
    return '<span class="t-str">' + out + "</span>";
  }

  function paintLine(line, known) {
    if (/^\s*note:/i.test(line)) return span("t-com", line);
    let out = "", i = 0, start = 0;
    while (i < line.length) {
      const c = line[i];
      if (c === "#") { out += paintCode(line.slice(start, i), known) + span("t-com", line.slice(i)); return out; }
      if (c === '"') {
        out += paintCode(line.slice(start, i), known);
        let j = i + 1;
        while (j < line.length && line[j] !== '"') j += line[j] === "\\" ? 2 : 1;
        out += paintText(line.slice(i, Math.min(j + 1, line.length)), known);
        i = start = Math.min(j + 1, line.length);
        continue;
      }
      i++;
    }
    return out + paintCode(line.slice(start), known);
  }

  function highlight(code) {
    const known = names(code);
    return code.split("\n").map((l) => paintLine(l, known)).join("\n");
  }

  // ------------------------------------------------------------ blocks
  // The line without its strings and comment, so words inside them are not mistaken for code.
  function codeOf(line) {
    if (/^\s*note:/i.test(line)) return "";
    let out = "", i = 0;
    while (i < line.length) {
      const c = line[i];
      if (c === "#") break;
      if (c === '"') {
        let j = i + 1;
        while (j < line.length && line[j] !== '"') j += line[j] === "\\" ? 2 : 1;
        out += '""';
        i = j + 1;
        continue;
      }
      out += c; i++;
    }
    return out;
  }
  // Does this line open a block that has to be closed with `end`?
  function opensBlock(line) {
    const code = codeOf(line);
    if (/^\s*(if|repeat|while|for|define|class)\b/i.test(code)) return true;
    if (/^\s*try\s*$/i.test(code)) return true;
    if (/^\s*init(\s+with\b.*)?\s*$/i.test(code)) return true;
    // an unnamed action written over several lines:  set f to action with x
    return /\baction(\s+with\b.*)?\s*$/i.test(code) && !/\bgives\b/i.test(code);
  }
  const closesBlock = (line) => /^\s*end\s*$/i.test(codeOf(line));
  // The next line goes one step further in after a block opens, and after otherwise / on error.
  const indentsAfter = (line) => opensBlock(line) || /^\s*(otherwise|on\s+error)\b/i.test(codeOf(line));

  function unclosedBlocks(code) {
    let open = 0;
    for (const line of code.split("\n")) {
      if (opensBlock(line)) open++;
      else if (closesBlock(line)) open--;
    }
    return open;
  }
  // The indent of the line that opened the block that line i belongs to (for end / otherwise / on error).
  function matchingIndent(lines, i) {
    let depth = 0;
    for (let k = i - 1; k >= 0; k--) {
      if (closesBlock(lines[k])) depth++;
      else if (opensBlock(lines[k])) {
        if (depth === 0) return lines[k].match(/^ */)[0].length;
        depth--;
      }
    }
    return -1;
  }

  return { names, paintLine, highlight, esc, codeOf, opensBlock, closesBlock, indentsAfter, unclosedBlocks, matchingIndent };
});
