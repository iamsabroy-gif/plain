// A program as a flowchart: every decision, loop and step as a box, joined by arrows.
// Used by the playground (the Flowchart button, and next to "Watch it run", where the box being
// run lights up). Works in the browser and in Node (tests/flowchart_test.js).
//
//   PlainFlow.parse(code)   -> { main: [items], actions: [{title, start, end, body, line}] }
//   PlainFlow.svg(code)     -> { svg: "<svg ...>", boxes: [{id, lines: [[from, to]], kind, text}] }
//
// It reads the program line by line, as Plain does: a block opens on an `if`, `repeat`, `while`,
// `for`, `define`, `class` or `try` line and closes on `end`. Half-typed programs are fine:
// anything still open is closed at the end, and a stray `end` is ignored.
"use strict";
(function (root, factory) {
  if (typeof module === "object" && module.exports) module.exports = factory(require("./syntax.js"));
  else root.PlainFlow = factory(root.PlainSyntax);
})(this, function (SX) {
  // ------------------------------------------------------------------ reading the program
  // The line without its comment (strings stay, so labels show what the program says).
  function withoutComment(line) {
    if (/^\s*note:/i.test(line)) return "";
    for (let i = 0; i < line.length; i++) {
      if (line[i] === "#") return line.slice(0, i);
      if (line[i] === '"') {
        i++;
        while (i < line.length && line[i] !== '"') i += line[i] === "\\" ? 2 : 1;
      }
    }
    return line;
  }
  const depthOf = (code) => (code.match(/[([{]/g) || []).length - (code.match(/[)\]}]/g) || []).length;

  // Statements: one per line, or several lines when brackets are still open (a long list).
  function statements(code) {
    const lines = code.replace(/\r/g, "").split("\n");
    const out = [];
    for (let i = 0; i < lines.length; i++) {
      let text = withoutComment(lines[i]).trim();
      if (!text) continue;
      let last = i, depth = depthOf(SX.codeOf(lines[i]));
      while (depth > 0 && last + 1 < lines.length) {
        last++;
        const more = withoutComment(lines[last]).trim();
        text += (more ? " " + more : "");
        depth += depthOf(SX.codeOf(lines[last]));
      }
      const bare = SX.codeOf(text).trim();
      out.push({ text, bare, word: (bare.match(/^[A-Za-z_]+/) || [""])[0].toLowerCase(), line: i + 1, last: last + 1 });
      i = last;
    }
    return out;
  }

  function parse(code) {
    const st = statements(code);
    let at = 0;
    const actions = [];
    const isEnd = (s) => s.word === "end" && /^end\s*$/i.test(s.bare);
    const isOtherwise = (s) => s.word === "otherwise";
    const isOnError = (s) => /^on\s+error\b/i.test(s.bare);

    // Statements up to (not including) the end / otherwise / on error that closes this block.
    function block() {
      const items = [];
      while (at < st.length) {
        const s = st[at];
        if (isEnd(s) || isOtherwise(s) || isOnError(s)) break;
        at++;
        const item = statement(s);
        if (item) items.push(item);
      }
      return items;
    }
    // The `end` of the block that opened on line `opened` (if it is there): its line, or 0.
    function closing() {
      if (at < st.length && isEnd(st[at])) return st[at++].line;
      return 0;
    }
    function action(title, startLabel, s, body, endLine, params) {
      actions.push({ title, start: startLabel, line: s.line, body, endLine, params });
    }

    function statement(s) {
      const w = s.word, t = s.text;
      if (w === "if") {
        const branches = [{ cond: t.replace(/^if\s+/i, "").replace(/\s+then\s*$/i, ""), line: s.line, last: s.last, body: block() }];
        let other = null;
        while (at < st.length && isOtherwise(st[at])) {
          const o = st[at++];
          const m = o.text.match(/^otherwise\s+if\s+(.*?)(\s+then)?\s*$/i);
          if (m) branches.push({ cond: m[1], line: o.line, last: o.last, body: block() });
          else { other = { line: o.line, body: block() }; break; }
        }
        return { k: "if", line: s.line, branches, other, endLine: closing() };
      }
      if (w === "repeat" || w === "while" || w === "for") {
        const body = block();
        return { k: "loop", kind: w === "for" && /^for\s+each\b/i.test(t) ? "each" : w, text: t, line: s.line, last: s.last, body, endLine: closing() };
      }
      if (w === "define") {
        const m = t.match(/^define\s+([A-Za-z_\u0080-￿][\w\u0080-￿]*)\s*(?:with\s+(.*))?$/i);
        const name = m ? m[1] : "(action)", params = m && m[2] ? m[2].replace(/\s+and\s+/gi, ", ") : "";
        const body = block();
        action("define " + name + (params ? " with " + params : ""), name + "(" + params + ")", s, body, closing(), params);
        return null;
      }
      if (w === "class") {
        const cls = (t.match(/^class\s+([A-Za-z_\u0080-￿][\w\u0080-￿]*)/i) || [0, "Class"])[1];
        while (at < st.length && !isEnd(st[at])) {
          const m = st[at++];
          const mm = m.text.match(/^(define\s+([A-Za-z_\u0080-￿][\w\u0080-￿]*)|init)\s*(?:with\s+(.*))?$/i);
          if (!mm) continue;
          const name = mm[2] || "init", params = mm[3] ? mm[3].replace(/\s+and\s+/gi, ", ") : "";
          const body = block();
          action(cls + "'s " + name + (params ? " with " + params : ""), cls + "'s " + name + "(" + params + ")", m, body, closing(), params);
        }
        closing();
        return null;
      }
      if (w === "try" && /^try\s*$/i.test(s.bare)) {
        const body = block();
        let handler = null, handlerText = "on error", handlerLine = 0;
        if (at < st.length && isOnError(st[at])) {
          const h = st[at++];
          handlerText = h.text; handlerLine = h.line;
          handler = block();
        }
        return { k: "try", line: s.line, body, handler: handler || [], handlerText, handlerLine, endLine: closing() };
      }
      if (w === "give" && /^give\s+back\b/i.test(s.bare)) return { k: "jump", kind: "give", text: t, line: s.line, last: s.last };
      if (w === "stop" && /^stop\s*$/i.test(s.bare)) return { k: "jump", kind: "stop", text: "stop", line: s.line, last: s.last };
      if (w === "skip" && /^skip\s*$/i.test(s.bare)) return { k: "jump", kind: "skip", text: "skip", line: s.line, last: s.last };
      if (w === "fail" && /^fail\s+with\b/i.test(s.bare)) return { k: "jump", kind: "fail", text: t, line: s.line, last: s.last };
      // an unnamed action written over several lines: one box (its inside is not drawn)
      if (SX.opensBlock(s.bare)) {
        block();
        const endLine = closing();
        return { k: "do", io: null, text: t + " … end", line: s.line, last: endLine || s.last };
      }
      let io = null;
      if (/^(say|show|print)\b/i.test(s.bare)) io = "out";
      else if (/^ask\b/i.test(s.bare)) io = "in";
      else if (/^call\s/i.test(s.bare) || /^[A-Za-z_\u0080-￿][\w\u0080-￿]*\s*(\(|'s\s+[A-Za-z_]\w*\s*\()/.test(s.bare)) io = "call";
      return { k: "do", io, text: t, line: s.line, last: s.last };
    }

    const main = [];
    while (at < st.length) {
      main.push(...block());
      if (at < st.length) at++;   // a stray end / otherwise / on error at the top: skip it
    }
    return { main, actions };
  }

  // ------------------------------------------------------------------ drawing
  const CW = 7.2;          // width of one character of the labels (12px monospace)
  const MAXCH = 34;        // longer labels are shortened (the whole text is in the tooltip)
  const H = 34, GAP = 24, SIDE = 30;
  const esc = (t) => String(t).replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/"/g, "&quot;");
  const short = (t) => (t.length > MAXCH ? t.slice(0, MAXCH - 1) + "…" : t);
  const textW = (t) => Math.max(40, short(t).length * CW);

  // Each layout gives back {w, h, cx (x of its way in and out), ends (does the flow go on below?), draw(x, y, out)}.
  function seq(items, ctx) {
    const parts = items.map((it) => layoutOf(it, ctx));
    if (!parts.length) return { w: 0, h: 0, cx: 0, ends: true, empty: true, draw() {} };
    const cx = Math.max(...parts.map((p) => p.cx));
    const w = Math.max(...parts.map((p) => cx - p.cx + p.w));
    let h = 0;
    parts.forEach((p, i) => { h += p.h + (i ? GAP : 0); });
    let ends = true;
    for (const p of parts) if (!p.ends) { ends = false; }
    // the flow only goes on below if the last part lets it (an earlier stop / give back makes the rest unreachable)
    ends = parts[parts.length - 1].ends;
    return {
      w, h, cx, ends,
      draw(x, y, out) {
        let yy = y;
        parts.forEach((p, i) => {
          if (i) {
            if (parts[i - 1].ends) out.edge([[x + cx, yy - GAP], [x + cx, yy]]);
          }
          p.draw(x + cx - p.cx, yy, out);
          yy += p.h + GAP;
        });
      },
    };
  }

  function box(kind, label, lines, opts) {
    opts = opts || {};
    const w = textW(label) + (kind === "io" ? 36 : kind === "call" ? 34 : kind === "term" ? 30 : 24);
    const h = opts.h || H;
    return {
      w, h, cx: w / 2, ends: opts.ends !== false,
      draw(x, y, out) { out.node(kind, label, lines, x, y, w, h, opts); },
    };
  }

  function layoutOf(it, ctx) {
    if (it.k === "do") {
      const kind = it.io === "out" || it.io === "in" ? "io" : it.io === "call" ? "call" : "step";
      return box(kind, it.text, [[it.line, it.last]], { io: it.io });
    }
    if (it.k === "jump") {
      const label = it.kind === "stop" ? "stop: leave the loop" : it.kind === "skip" ? "skip: next round" : it.text;
      return box(it.kind === "give" || it.kind === "fail" ? "term" : "jump", label, [[it.line, it.last]], { ends: false, jump: it.kind });
    }
    if (it.k === "loop") return loopLayout(it, ctx);
    if (it.k === "if") return ifLayout(it.branches, it.other, it.endLine, ctx);
    if (it.k === "try") return tryLayout(it, ctx);
    return box("step", "?", [[it.line || 0, it.line || 0]]);
  }

  // A decision: a diamond; "yes" goes down, "no" goes right (into the next decision, or the otherwise).
  function ifLayout(branches, other, endLine, ctx) {
    const b = branches[0];
    const dw = textW(b.cond + "?") + 44, dh = 50;
    const yes = seq(b.body, ctx);
    const no = branches.length > 1 ? ifLayout(branches.slice(1), other, 0, ctx) : other ? seq(other.body, ctx) : null;
    const yesW = yes.empty ? 0 : yes.w, noW = no && !no.empty ? no.w : 0;
    const left = Math.max(dw / 2, yes.empty ? 0 : yes.cx) + 4;
    const yesRight = Math.max(dw / 2, yes.empty ? 0 : yesW - yes.cx);
    const noX = left + yesRight + SIDE;                       // where the "no" column starts (relative)
    const noCx = no && !no.empty ? no.cx : 0;
    const w = noX + Math.max(noW, 20) + 4;
    const bodyH = Math.max(yes.empty ? 0 : yes.h, no && !no.empty ? no.h : 0);
    const h = dh + GAP + bodyH + GAP;
    const yesEnds = yes.empty || yes.ends, noEnds = !no || no.empty || no.ends;
    const lines = [[b.line, b.last]];
    if (endLine) lines.push([endLine, endLine]);
    // the "otherwise" line belongs to the last question (Plain jumps from there past the other branch)
    if (branches.length === 1 && other && other.line) lines.push([other.line, other.line]);
    return {
      w, h, cx: left, ends: yesEnds || noEnds,
      draw(x, y, out) {
        const ax = x + left;
        out.node("decision", b.cond + "?", lines, ax - dw / 2, y, dw, dh, { full: "if " + b.cond });
        const top = y + dh + GAP, merge = y + h - 6;
        // yes: straight down
        if (!yes.empty) { out.edge([[ax, y + dh], [ax, top]], "yes"); yes.draw(ax - yes.cx, top, out); if (yes.ends) out.edge([[ax, top + yes.h], [ax, merge]], null, true); }
        else out.edge([[ax, y + dh], [ax, merge]], "yes", true);
        // no: to the right, then down
        const nx = x + noX + noCx;
        if (no && !no.empty) {
          out.edge([[ax + dw / 2, y + dh / 2], [nx, y + dh / 2], [nx, top]], "no");
          no.draw(x + noX, top, out);
          if (no.ends) out.edge([[nx, top + no.h], [nx, merge], [ax, merge]], null, true);
        } else {
          out.edge([[ax + dw / 2, y + dh / 2], [nx + 10, y + dh / 2], [nx + 10, merge], [ax, merge]], "no", true);
        }
        out.edge([[ax, merge], [ax, y + h]], null, true);
      },
    };
  }

  // A loop: a hexagon that asks "another round?"; the body below, an arrow back up, and "done" out to the right.
  function loopLayout(it, ctx) {
    const hw = textW(it.text) + 36, hh = 38;
    const body = seq(it.body, ctx);
    const left = Math.max(hw / 2, body.empty ? 0 : body.cx) + SIDE;
    const right = Math.max(hw / 2, body.empty ? 0 : body.w - body.cx) + SIDE;
    const h = hh + GAP + (body.empty ? 0 : body.h) + GAP + 14;
    const lines = [[it.line, it.last]];
    if (it.endLine) lines.push([it.endLine, it.endLine]);
    return {
      w: left + right, h, cx: left, ends: true,
      draw(x, y, out) {
        const ax = x + left, top = y + hh + GAP, bottom = top + (body.empty ? 0 : body.h);
        out.node("loop", it.text, lines, ax - hw / 2, y, hw, hh, { kind: it.kind });
        if (!body.empty) {
          out.edge([[ax, y + hh], [ax, top]], it.kind === "while" ? "yes" : null);
          body.draw(ax - body.cx, top, out);
        }
        // round again
        if (body.empty || body.ends) out.edge([[ax, bottom], [ax, bottom + 10], [x + 8, bottom + 10], [x + 8, y + hh / 2], [ax - hw / 2, y + hh / 2]], null, false, "again");
        // done
        out.edge([[ax + hw / 2, y + hh / 2], [x + left + right - 8, y + hh / 2], [x + left + right - 8, y + h - 2], [ax, y + h - 2], [ax, y + h]], it.kind === "while" ? "no" : "done", true);
      },
    };
  }

  // try: the steps, and to the side what happens if one of them fails.
  function tryLayout(it, ctx) {
    const head = box("step", "try", [[it.line, it.line]], { kind: "try" });
    const body = seq(it.body, ctx);
    const handlerHead = box("io", it.handlerText, [[it.handlerLine, it.handlerLine]], { io: "err" });
    const handler = seq(it.handler, ctx);
    const left = Math.max(head.w / 2, body.empty ? 0 : body.cx) + 4;
    const right = Math.max(head.w / 2, body.empty ? 0 : body.w - body.cx);
    const hx = left + right + SIDE;
    const hcx = Math.max(handlerHead.cx, handler.empty ? 0 : handler.cx);
    const hw = Math.max(hcx + handlerHead.w / 2, handler.empty ? 0 : hcx - handler.cx + handler.w);
    const leftH = H + GAP + (body.empty ? 0 : body.h);
    const rightH = H + GAP + H + (handler.empty ? 0 : GAP + handler.h);
    const h = Math.max(leftH, rightH) + GAP;
    const lines = [[it.line, it.line]];
    if (it.endLine) lines.push([it.endLine, it.endLine]);
    return {
      w: hx + hw + 4, h, cx: left, ends: true,
      draw(x, y, out) {
        const ax = x + left, merge = y + h - 6;
        out.node("step", "try", lines, ax - head.w / 2, y, head.w, H, { kind: "try" });
        const top = y + H + GAP;
        if (!body.empty) { out.edge([[ax, y + H], [ax, top]]); body.draw(ax - body.cx, top, out); if (body.ends) out.edge([[ax, top + body.h], [ax, merge]], null, true); }
        else out.edge([[ax, y + H], [ax, merge]], null, true);
        const hcxAbs = x + hx + hcx;
        out.edge([[ax + head.w / 2, y + H / 2], [hcxAbs, y + H / 2], [hcxAbs, top]], "if a step fails", false, "fail");
        handlerHead.draw(hcxAbs - handlerHead.cx, top, out);
        let hy = top + H;
        if (!handler.empty) { out.edge([[hcxAbs, hy], [hcxAbs, hy + GAP]]); handler.draw(hcxAbs - handler.cx, hy + GAP, out); hy += GAP + handler.h; }
        if (handler.empty || handler.ends) out.edge([[hcxAbs, hy], [hcxAbs, merge], [ax, merge]], null, true);
        out.edge([[ax, merge], [ax, y + h]], null, true);
      },
    };
  }

  // One chart: a start pill, the steps, an end pill (unless every way ends in give back / stop).
  function chart(title, startLabel, endLabel, items, endLines, ctx) {
    const start = box("term", startLabel, [], { start: true });
    const body = seq(items, ctx);
    const end = box("term", endLabel, endLines, { end: true });
    const parts = [start].concat(body.empty ? [] : [body]).concat(body.empty || body.ends ? [end] : []);
    const cx = Math.max(...parts.map((p) => p.cx)) + 16;
    const w = Math.max(...parts.map((p) => cx - p.cx + p.w)) + 16;
    let h = 26;
    parts.forEach((p, i) => { h += p.h + (i ? GAP : 0); });
    return {
      w, h: h + 16,
      draw(x, y, out) {
        out.title(title, x + 4, y + 16);
        let yy = y + 26;
        parts.forEach((p, i) => {
          if (i) out.edge([[x + cx, yy - GAP], [x + cx, yy]]);
          p.draw(x + cx - p.cx, yy, out);
          yy += p.h + GAP;
        });
      },
    };
  }

  function svg(code) {
    const prog = parse(code);
    const lastLine = code.replace(/\r/g, "").split("\n").length;
    const charts = [chart("Main program", "Start", "End", prog.main, [], {})];
    for (const a of prog.actions) charts.push(chart(a.title, a.start, a.title.startsWith("define") || a.title.includes("'s ") ? "end of " + a.start.replace(/\(.*$/, "") : "end", a.body, a.endLine ? [[a.endLine, a.endLine]] : [], {}));
    const width = Math.ceil(Math.max(...charts.map((c) => c.w)) + 8);
    let height = 0;
    charts.forEach((c) => { height += c.h + 14; });
    const parts = [], edges = [], labels = [], boxes = [];
    let id = 0;
    const out = {
      node(kind, label, lines, x, y, w, h, opts) {
        const n = "fc" + id++;
        const full = (opts && opts.full) || label;
        boxes.push({ id: n, lines, kind, text: full, x, y, w, h });
        const cls = "fc-node fc-" + kind + (opts && opts.io ? " fc-io-" + opts.io : "") + (opts && opts.jump ? " fc-jump-" + opts.jump : "") + (opts && opts.start ? " fc-start" : "") + (opts && opts.end ? " fc-end" : "");
        let shape;
        const r = (v) => Math.round(v * 10) / 10;
        if (kind === "decision") shape = '<polygon points="' + [[x + w / 2, y], [x + w, y + h / 2], [x + w / 2, y + h], [x, y + h / 2]].map((p) => r(p[0]) + "," + r(p[1])).join(" ") + '"/>';
        else if (kind === "loop") shape = '<polygon points="' + [[x + 14, y], [x + w - 14, y], [x + w, y + h / 2], [x + w - 14, y + h], [x + 14, y + h], [x, y + h / 2]].map((p) => r(p[0]) + "," + r(p[1])).join(" ") + '"/>';
        else if (kind === "io") shape = '<polygon points="' + [[x + 12, y], [x + w, y], [x + w - 12, y + h], [x, y + h]].map((p) => r(p[0]) + "," + r(p[1])).join(" ") + '"/>';
        else if (kind === "term") shape = '<rect x="' + r(x) + '" y="' + r(y) + '" width="' + r(w) + '" height="' + h + '" rx="' + h / 2 + '"/>';
        else if (kind === "jump") shape = '<rect x="' + r(x) + '" y="' + r(y) + '" width="' + r(w) + '" height="' + h + '" rx="' + h / 2 + '" stroke-dasharray="5 3"/>';
        else if (kind === "call") shape = '<rect x="' + r(x) + '" y="' + r(y) + '" width="' + r(w) + '" height="' + h + '" rx="3"/><path class="fc-bars" d="M' + r(x + 8) + " " + r(y) + "V" + r(y + h) + "M" + r(x + w - 8) + " " + r(y) + "V" + r(y + h) + '"/>';
        else shape = '<rect x="' + r(x) + '" y="' + r(y) + '" width="' + r(w) + '" height="' + h + '" rx="6"/>';
        const lineAttr = lines.map((l) => l[0] + "-" + l[1]).join(" ");
        parts.push('<g class="' + cls + '" id="' + n + '" data-lines="' + lineAttr + '"' + (lines.length ? ' tabindex="0" role="button"' : "") + ">" +
          "<title>" + esc(full) + (lines.length ? " (line " + lines[0][0] + ")" : "") + "</title>" + shape +
          '<text x="' + r(x + w / 2) + '" y="' + r(y + h / 2 + 4) + '" text-anchor="middle">' + esc(short(label)) + "</text>" +
          '<text class="fc-count" x="' + r(x + w + 2) + '" y="' + r(y + 2) + '"></text></g>');
      },
      edge(points, label, noArrow, kind) {
        const d = points.map((p, i) => (i ? "L" : "M") + Math.round(p[0] * 10) / 10 + " " + Math.round(p[1] * 10) / 10).join(" ");
        edges.push('<path class="fc-edge' + (kind ? " fc-" + kind : "") + '" d="' + d + '"' + (noArrow ? "" : ' marker-end="url(#fc-arrow)"') + "/>");
        if (label) {
          const a = points[0], b = points[1];
          const lx = a[0] === b[0] ? a[0] + 5 : a[0] + 6, ly = a[0] === b[0] ? a[1] + 13 : a[1] - 5;
          labels.push('<text class="fc-label" x="' + Math.round(lx) + '" y="' + Math.round(ly) + '">' + esc(label) + "</text>");
        }
      },
      title(t, x, y) { parts.push('<text class="fc-title" x="' + Math.round(x) + '" y="' + Math.round(y) + '">' + esc(t) + "</text>"); },
    };
    let y = 4;
    for (const c of charts) { c.draw(4, y, out); y += c.h + 14; }
    const svgText = '<svg xmlns="http://www.w3.org/2000/svg" class="flowchart" width="' + width + '" height="' + Math.ceil(height) + '" viewBox="0 0 ' + width + " " + Math.ceil(height) + '" role="img" aria-label="Flowchart of the program">' +
      '<defs><marker id="fc-arrow" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto-start-reverse"><path d="M0 0L10 5L0 10z"/></marker></defs>' +
      edges.join("") + parts.join("") + labels.join("") + "</svg>";
    return { svg: svgText, boxes, width, height: Math.ceil(height), lastLine, actions: prog.actions.length };
  }

  // Which box a line of the program belongs to (the smallest range that holds it), or null.
  function boxForLine(boxes, line) {
    let best = null, size = Infinity;
    for (const b of boxes) for (const [a, z] of b.lines) if (line >= a && line <= z && z - a < size) { best = b; size = z - a; }
    return best;
  }

  return { parse, svg, boxForLine, statements };
});
