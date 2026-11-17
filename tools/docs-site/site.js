// The documentation site: the menu on phones, search across every page, and "On this page".
"use strict";
(function () {
  const menu = document.querySelector(".menu");
  menu.addEventListener("click", () => {
    const open = document.body.classList.toggle("menu-open");
    menu.setAttribute("aria-expanded", String(open));
  });
  document.querySelectorAll("aside a").forEach((a) => a.addEventListener("click", () => document.body.classList.remove("menu-open")));

  // ---- search: search-index.js sets PLAIN_SEARCH, one entry per section {p: page, u: address, h: heading, t: text}.
  // It is loaded the first time someone searches.
  const q = document.getElementById("q"), box = document.getElementById("results");
  let entries = null, loading = null, sel = -1;
  function load() {
    if (entries) return Promise.resolve(entries);
    if (!loading) loading = new Promise((resolve) => {
      const s = document.createElement("script");
      s.src = "search-index.js";
      s.onload = () => resolve((entries = window.PLAIN_SEARCH || []));
      s.onerror = () => resolve((entries = []));
      document.head.append(s);
    });
    return loading;
  }
  const escHtml = (s) => s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
  function mark(text, words) {
    let html = escHtml(text);
    for (const w of words) html = html.replace(new RegExp("(" + w.replace(/[.*+?^${}()|[\]\\]/g, "\\$&") + ")", "gi"), "<mark>$1</mark>");
    return html;
  }
  function snippet(text, words) {
    const low = text.toLowerCase();
    let at = Math.max(0, low.indexOf(words[0]) - 60);
    const s = (at > 0 ? "…" : "") + text.slice(at, at + 170) + (at + 170 < text.length ? "…" : "");
    return s;
  }
  async function find() {
    const words = q.value.toLowerCase().split(/\s+/).filter(Boolean);
    if (!words.length) { box.hidden = true; return; }
    await load();
    const scored = [];
    for (const e of entries) {
      const h = e.h.toLowerCase(), t = e.t.toLowerCase(), p = e.p.toLowerCase();
      if (!words.every((w) => h.includes(w) || t.includes(w) || p.includes(w))) continue;
      let score = 0;
      for (const w of words) score += (h.includes(w) ? 10 : 0) + (p.includes(w) ? 3 : 0) + Math.min(5, t.split(w).length - 1);
      if (h.includes(words.join(" "))) score += 15;
      if (t.includes(words.join(" "))) score += 6;
      scored.push([score, e]);
    }
    scored.sort((a, b) => b[0] - a[0]);
    box.innerHTML = scored.length ? scored.slice(0, 12).map(([, e]) => '<a href="' + e.u + '" role="option"><b>' + mark(e.h, words) + "</b><small>" + escHtml(e.p) + "</small>" + mark(snippet(e.t, words), words) + "</a>").join("")
      : '<div class="none">Nothing found. Try fewer or other words.</div>';
    box.hidden = false;
    sel = -1;
  }
  q.addEventListener("input", find);
  q.addEventListener("focus", () => { load(); if (q.value) find(); });
  q.addEventListener("keydown", (e) => {
    const items = box.querySelectorAll("a");
    if (e.key === "ArrowDown" || e.key === "ArrowUp") {
      e.preventDefault();
      if (!items.length) return;
      sel = (sel + (e.key === "ArrowDown" ? 1 : items.length - 1)) % items.length;
      items.forEach((a, i) => a.classList.toggle("sel", i === sel));
      items[sel].scrollIntoView({ block: "nearest" });
    } else if (e.key === "Enter" && items.length) {
      e.preventDefault();
      location.href = items[Math.max(0, sel)].getAttribute("href");
      box.hidden = true;
    } else if (e.key === "Escape") { box.hidden = true; q.blur(); }
  });
  document.addEventListener("click", (e) => { if (!e.target.closest(".search")) box.hidden = true; });
  document.addEventListener("keydown", (e) => {
    if (e.key === "/" && document.activeElement !== q && !/INPUT|TEXTAREA/.test(document.activeElement.tagName)) { e.preventDefault(); q.focus(); }
  });

  // ---- "On this page": light up the section being read
  const links = [...document.querySelectorAll(".toc a")];
  if (links.length && "IntersectionObserver" in window) {
    const byId = new Map(links.map((a) => [a.getAttribute("href").slice(1), a]));
    const seen = new Set();
    const io = new IntersectionObserver((list) => {
      list.forEach((en) => (en.isIntersecting ? seen.add(en.target.id) : seen.delete(en.target.id)));
      const first = [...byId.keys()].find((id) => seen.has(id));
      if (first) links.forEach((a) => a.classList.toggle("here", a === byId.get(first)));
    }, { rootMargin: "-60px 0px -60% 0px" });
    byId.forEach((_, id) => { const h = document.getElementById(id); if (h) io.observe(h); });
  }
})();
