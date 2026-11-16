// Plain - the learning tools: visualize, count (and growth, compare, practice).
// Included by main.cpp after report() is defined.
#pragma once
#include <chrono>

// Run a compiled program under an observer. Returns false when the program stopped with an error.
struct WatchedRun {
    Program prog;
    Observer ob;
    std::string errorMsg;
    int errorLine = 0;
    std::string errorFile;
};

static std::string htmlEscape(const std::string& s) {
    std::string o;
    for (char c : s) {
        if (c == '<') o += "&lt;";
        else if (c == '>') o += "&gt;";
        else if (c == '&') o += "&amp;";
        else if (c == '"') o += "&quot;";
        else o += c;
    }
    return o;
}

// What "# watch:" comment lines ask for:   # watch: xs, total   or   # watch: xs as bars, grid as table
static const char* const WATCH_VIEWS[] = {"bars", "boxes", "grid", "table", "tree", "chain", "graph", "text"};
struct WatchList {
    std::vector<std::string> names;
    std::vector<std::pair<std::string, std::string>> views;  // name -> how to draw it
    std::vector<std::string> problems;
};
static WatchList watchNames(const std::string& src) {
    WatchList w;
    size_t at = 0;
    int lineNo = 0;
    while (at < src.size()) {
        size_t end = src.find('\n', at);
        if (end == std::string::npos) end = src.size();
        std::string line = src.substr(at, end - at);
        at = end + 1;
        ++lineNo;
        size_t hash = line.find('#');
        if (hash == std::string::npos) continue;
        std::string c = line.substr(hash + 1);
        size_t a = c.find_first_not_of(" \t");
        if (a == std::string::npos || c.compare(a, 6, "watch:") != 0) continue;
        std::string entry;
        for (char ch : c.substr(a + 6) + ",") {
            if (ch != ',') { entry += ch; continue; }
            std::vector<std::string> words;
            std::string cur;
            for (char e : entry + " ") {
                if (e == ' ' || e == '\t') { if (!cur.empty()) words.push_back(cur); cur.clear(); }
                else cur += e;
            }
            entry.clear();
            if (words.size() == 3 && words[1] == "as") {
                bool known = false;
                for (const char* v : WATCH_VIEWS) known = known || words[2] == v;
                w.names.push_back(words[0]);
                if (known) w.views.emplace_back(words[0], words[2]);
                else {
                    std::string all;
                    for (const char* v : WATCH_VIEWS) all += (all.empty() ? "" : ", ") + std::string(v);
                    w.problems.push_back("Line " + std::to_string(lineNo) + ": I can't draw '" + words[0] + "' as '" + words[2] + "'. I can draw a value as: " + all + ".");
                }
            } else {
                for (const std::string& x : words) w.names.push_back(x);  // "# watch: xs total"
            }
        }
    }
    return w;
}

static std::string replaceFirst(std::string text, const std::string& what, const std::string& with) {
    size_t at = text.find(what);
    if (at != std::string::npos) text.replace(at, what.size(), with);
    return text;
}

// One program run under the recorder.
struct Recording {
    std::unique_ptr<WatchedRun> run;
    std::string file, src, json;
    bool neverStarted = false;  // a mistake in how it is written: already reported
};
static Recording recordRun(const std::string& file, const std::string& src, size_t maxSteps, uint64_t budget, bool intoLib) {
    Recording R;
    R.file = file;
    R.src = src;
    R.run = std::make_unique<WatchedRun>();
    WatchedRun& run = *R.run;
    setUp(run.prog);
    VM vm(run.prog);
    run.ob.trace = true;
    run.ob.capture = true;
    run.ob.showLibrary = intoLib;
    run.ob.maxSteps = maxSteps;
    run.ob.maxInstr = budget;
    vm.obs = &run.ob;
    vm.args = {};
    try {
        Compiler compiler(run.prog, src, file);
        Value mainFn = compiler.compileMain();
        vm.run(mainFn);
        run.ob.finish(vm);
    } catch (const PlainError& e) {
        if (run.ob.steps.empty() && !run.ob.pending && e.line && run.ob.outputChunks.empty() && e.file.empty()) {
            report(e, file, src, &run.prog);
            R.neverStarted = true;
            return R;
        }
        run.errorMsg = e.msg;
        run.errorLine = e.line;
        run.errorFile = e.file;
    }
    std::vector<std::pair<std::string, std::string>> sources;
    std::vector<std::string> names = run.ob.files;
    if (names.empty()) names.push_back(file);
    for (const std::string& n : names) {
        std::string text;
        if (n == file) text = src;
        else if (const char* lib = libSource(n)) text = lib;
        else
            for (const auto& s : run.prog.sources)
                if (s.first == n) text = s.second;
        sources.emplace_back(n, text);
    }
    run.ob.files = names;
    WatchList w = watchNames(src);
    for (const std::string& p : w.problems) fprintf(stderr, "%s: %s\n", file.c_str(), p.c_str());
    std::string json = run.ob.traceJson(sources, w.names, run.errorMsg, run.errorLine, w.views);
    R.json.reserve(json.size());
    for (size_t i = 0; i < json.size(); ++i) {  // never end the page's <script> early
        if (json[i] == '<' && i + 1 < json.size() && json[i + 1] == '/') R.json += "<\\";  // the '/' follows next
        else R.json += json[i];
    }
    return R;
}
// Report the problem a recorded run stopped with (if any). Gives the exit code.
static int reportRecording(const Recording& R) {
    if (R.run->errorMsg.empty()) return 0;
    PlainError e;
    e.msg = R.run->errorMsg;
    e.line = R.run->errorLine;
    e.file = R.run->errorFile;
    report(e, R.file, R.src, &R.run->prog);
    return 1;
}
static bool writePage(const std::string& out, const std::string& page) {
    FILE* f = fopen(out.c_str(), "wb");
    if (!f) { fprintf(stderr, "I couldn't write to '%s'.\n", out.c_str()); return false; }
    fwrite(page.data(), 1, page.size(), f);
    fclose(f);
    return true;
}
static std::string pageName(const std::string& file) {
    size_t slash = file.find_last_of("/\\");
    std::string base = file.substr(slash == std::string::npos ? 0 : slash + 1);
    size_t dot = base.find_last_of('.');
    return dot == std::string::npos ? base : base.substr(0, dot);
}

// Two recorded runs in one page: two players next to each other, stepped together.
static std::string sideBySidePage(const std::string& tmpl, const Recording& a, const Recording& b) {
    auto pageJs = [&](const Recording& r) {
        std::string page = replaceFirst(tmpl, "/*__PLAIN_DATA__*/null", r.json), js;
        Observer::jsonString(js, page);
        std::string safe;  // the page sits inside a <script>: hide every "</"
        for (size_t i = 0; i < js.size(); ++i) {
            if (js[i] == '<' && i + 1 < js.size() && js[i + 1] == '/') safe += "<\\";  // the '/' follows next
            else safe += js[i];
        }
        return safe;
    };
    std::string titleA = pageName(a.file), titleB = pageName(b.file);
    std::string t;
    t += "<!doctype html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
         "<title>Plain - side by side</title><style>"
         ":root{--bg:#f6f7f9;--card:#fff;--ink:#1d2330;--muted:#5d6675;--line:#d9dde4;--accent:#2f6fde}"
         "@media (prefers-color-scheme:dark){:root{--bg:#14171c;--card:#1d2128;--ink:#e6e9ee;--muted:#9aa3b2;--line:#323844;--accent:#6ea0ff}}"
         "*{box-sizing:border-box}body{margin:0;font:15px/1.4 system-ui,sans-serif;background:var(--bg);color:var(--ink)}"
         "header{position:sticky;top:0;z-index:2;display:flex;flex-wrap:wrap;gap:8px;align-items:center;padding:10px 16px;background:var(--card);border-bottom:1px solid var(--line)}"
         "header b{margin-right:8px}button{font:inherit;padding:6px 12px;border:1px solid var(--line);border-radius:8px;background:var(--card);color:var(--ink);cursor:pointer}"
         "button:hover{border-color:var(--accent)}#at{color:var(--muted);margin-left:auto}"
         "main{display:grid;grid-template-columns:1fr 1fr;gap:12px;padding:12px}@media (max-width:900px){main{grid-template-columns:1fr}}"
         "section{background:var(--card);border:1px solid var(--line);border-radius:10px;overflow:hidden}"
         "section h2{margin:0;padding:8px 12px;font-size:15px;border-bottom:1px solid var(--line)}"
         "iframe{width:100%;height:calc(100vh - 120px);min-height:520px;border:0;display:block}</style></head><body>"
         "<header><b>Side by side</b><button id=\"first\">&#9198; Start</button><button id=\"prev\">&#9664; Back</button>"
         "<button id=\"play\">&#9654; Play</button><button id=\"next\">Step &#9654;</button><button id=\"last\">End &#9197;</button>"
         "<span id=\"at\"></span></header><main>";
    t += "<section><h2>" + htmlEscape(titleA) + "</h2><iframe id=\"a\" title=\"" + htmlEscape(titleA) + "\"></iframe></section>";
    t += "<section><h2>" + htmlEscape(titleB) + "</h2><iframe id=\"b\" title=\"" + htmlEscape(titleB) + "\"></iframe></section></main>";
    t += "<script>const PAGES=[" + pageJs(a) + "," + pageJs(b) + "];\n";
    t += R"JS(
const frames = [document.getElementById("a"), document.getElementById("b")];
const total = [0, 0];
let step = 0, timer = null;
frames.forEach((f, k) => { f.srcdoc = PAGES[k]; });
window.addEventListener("message", (e) => {
  const k = frames.findIndex((f) => f.contentWindow === e.source);
  if (k < 0 || !e.data || e.data.plainPlayerReady === undefined) return;
  total[k] = e.data.plainPlayerReady;
  go(step);
});
function longest() { return Math.max(total[0], total[1], 1); }
function go(i) {
  step = Math.max(0, Math.min(longest() - 1, i));
  frames.forEach((f, k) => { if (total[k]) f.contentWindow.postMessage({ plainPlayer: "go", i: Math.min(step, total[k] - 1) }, "*"); });
  const parts = total.map((n, k) => (k ? "right " : "left ") + Math.min(step + 1, n) + " of " + n);
  document.getElementById("at").textContent = "step " + (step + 1) + "  ·  " + parts.join(", ");
  document.getElementById("play").innerHTML = timer ? "&#10074;&#10074; Pause" : "&#9654; Play";
}
function stop() { if (timer) { clearInterval(timer); timer = null; } }
document.getElementById("first").onclick = () => { stop(); go(0); };
document.getElementById("prev").onclick = () => { stop(); go(step - 1); };
document.getElementById("next").onclick = () => { stop(); go(step + 1); };
document.getElementById("last").onclick = () => { stop(); go(longest() - 1); };
document.getElementById("play").onclick = () => {
  if (timer) { stop(); go(step); return; }
  if (step >= longest() - 1) step = 0;
  timer = setInterval(() => { if (step >= longest() - 1) { stop(); go(step); return; } go(step + 1); }, 450);
  go(step);
};
document.addEventListener("keydown", (e) => {
  if (e.key === "ArrowRight") { stop(); go(step + 1); }
  else if (e.key === "ArrowLeft") { stop(); go(step - 1); }
});
</script></body></html>
)JS";
    return t;
}

// plain visualize program.plain [other.plain] [-o page.html] [--max-steps N] [--into-library]
static int visualizeCommand(const std::vector<std::string>& args) {
    std::string out, inlineSrc;
    std::vector<std::string> files;
    bool haveInline = false, jsonOnly = false;
    size_t maxSteps = 6000;
    bool intoLib = false;
    uint64_t budget = 300000000;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-e" && i + 1 < args.size()) { inlineSrc = args[++i] + "\n"; haveInline = true; }
        else if (args[i] == "--json") jsonOnly = true;
        else if (args[i] == "-o" && i + 1 < args.size()) out = args[++i];
        else if (args[i] == "--budget" && i + 1 < args.size()) budget = (uint64_t)std::max(1LL, atoll(args[++i].c_str()));
        else if (args[i] == "--max-steps" && i + 1 < args.size()) maxSteps = (size_t)std::max(1, atoi(args[++i].c_str()));
        else if (args[i] == "--into-library") intoLib = true;
        else files.push_back(args[i]);
    }
    if (files.size() > 2 || (haveInline && !files.empty())) {
        fprintf(stderr, "Give one program to watch, or two to watch side by side: plain visualize a.plain b.plain\n");
        return 2;
    }
    std::vector<std::string> srcs;
    if (haveInline) {
        files = {"program.plain"};
        srcs = {inlineSrc};
    } else {
        if (files.empty()) { fprintf(stderr, "Tell me which program to draw, like: plain visualize program.plain\n"); return 2; }
        for (const std::string& f : files) {
            std::string src;
            if (!readFile(f, src)) { fprintf(stderr, "I couldn't open the file '%s'.\n", f.c_str()); return 2; }
            srcs.push_back(src);
        }
    }
    const char* tmpl = packedFile("viz/player.html");
    if (!tmpl) { fprintf(stderr, "This copy of Plain has no player inside it.\n"); return 3; }

    if (files.size() == 2) {
        if (jsonOnly) { fprintf(stderr, "--json takes one program.\n"); return 2; }
        Recording a = recordRun(files[0], srcs[0], maxSteps, budget, intoLib);
        if (a.neverStarted) return 1;
        Recording b = recordRun(files[1], srcs[1], maxSteps, budget, intoLib);
        if (b.neverStarted) return 1;
        if (out.empty()) out = pageName(files[0]) + "-and-" + pageName(files[1]) + ".html";
        if (!writePage(out, sideBySidePage(tmpl, a, b))) return 2;
        printf("Recorded %zu and %zu steps. Open %s in a browser to step through both together.\n", a.run->ob.steps.size(),
               b.run->ob.steps.size(), out.c_str());
        int ca = reportRecording(a), cb = reportRecording(b);
        return ca || cb;
    }

    const std::string& file = files[0];
    Recording R = recordRun(file, srcs[0], maxSteps, budget, intoLib);
    if (R.neverStarted) return 1;
    if (jsonOnly) {  // for the web playground: the trace itself, which its own copy of the player draws
        fwrite(R.json.data(), 1, R.json.size(), stdout);
        fflush(stdout);
        return reportRecording(R);
    }
    if (out.empty()) out = pageName(file) + ".html";
    if (!writePage(out, replaceFirst(tmpl, "/*__PLAIN_DATA__*/null", R.json))) return 2;
    printf("Recorded %zu step%s of %s. Open %s in a browser to watch it.\n", R.run->ob.steps.size(), R.run->ob.steps.size() == 1 ? "" : "s",
           file.c_str(), out.c_str());
    if (R.run->ob.truncated) printf("(It was longer than %zu steps, so the recording stops there. Try a smaller input, or --max-steps.)\n", maxSteps);
    return reportRecording(R);
}

static std::string withCommas(uint64_t n) {
    std::string s = std::to_string(n), out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (i && (s.size() - i) % 3 == 0) out += ',';
        out += s[i];
    }
    return out;
}

// plain count program.plain: run it, then say how much work it did.
static int countCommand(const std::vector<std::string>& args) {
    std::string file, src;
    bool haveInline = false;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-e" && i + 1 < args.size()) { src = args[++i] + "\n"; haveInline = true; file = "program.plain"; }
        else if (!haveInline) file = args[i];
    }
    if (file.empty()) { fprintf(stderr, "Tell me which program to count, like: plain count program.plain\n"); return 2; }
    if (!haveInline && !readFile(file, src)) { fprintf(stderr, "I couldn't open the file '%s'.\n", file.c_str()); return 2; }
    auto run = std::make_unique<WatchedRun>();
    setUp(run->prog);
    VM vm(run->prog);
    run->ob.maxInstr = 4000000000ULL;
    vm.obs = &run->ob;
    int code = 0;
    try {
        Compiler compiler(run->prog, src, file);
        Value mainFn = compiler.compileMain();
        vm.run(mainFn);
    } catch (const PlainError& e) {
        report(e, file, src, &run->prog);
        code = 1;
    }
    fflush(stdout);
    const Observer& o = run->ob;
    printf("\nWork done by %s%s\n", file.c_str(), code ? " (until it stopped)" : "");
    printf("  comparisons   %14s   (every <, >, is, is at most ... that ran)\n", withCommas(o.compares).c_str());
    printf("  swaps         %14s   (two list items exchanging places)\n", withCommas(o.swaps).c_str());
    printf("  list writes   %14s   (times a list item was set to a new value)\n", withCommas(o.writes).c_str());
    printf("  calls         %14s   (times an action started)\n", withCommas(o.calls).c_str());
    printf("  instructions  %14s   (steps of the virtual machine)\n", withCommas(o.instr).c_str());
    std::vector<std::pair<std::string, uint64_t>> by(o.callsByName.begin(), o.callsByName.end());
    std::sort(by.begin(), by.end(), [](auto& a, auto& b) { return a.second != b.second ? a.second > b.second : a.first < b.first; });
    if (!by.empty()) {
        printf("  most called:");
        for (size_t i = 0; i < by.size() && i < 6; ++i) printf("%s %s x%s", i ? "," : "", by[i].first.c_str(), withCommas(by[i].second).c_str());
        printf("\n");
    }
    printf("  (the built-in sort() is one step to Plain, so its own comparisons are not counted: write the sort yourself to study it)\n");
    return code;
}

// ------------------------------------------------------------------ growth and compare
struct Measure {
    bool ok = false, tooSlow = false;
    uint64_t cmp = 0, swaps = 0, writes = 0, calls = 0, instr = 0;
    double ms = 0;
    std::string error;
    Value result, input;
};

// The data an action is tried on, for size n. The same n always gives the same data.
static Value makeInput(const std::string& kind, int64_t n) {
    if (kind == "number") return Value::integer(n);
    if (kind == "text") {
        std::string s;
        for (int64_t i = 0; i < n; ++i) s += (char)('a' + i % 26);
        return mkstr(s);
    }
    std::vector<Value> items;
    items.reserve((size_t)n);
    uint64_t x = 88172645463325252ULL ^ (uint64_t)n * 0x9E3779B97F4A7C15ULL;
    for (int64_t i = 0; i < n; ++i) {
        x ^= x << 13; x ^= x >> 7; x ^= x << 17;
        items.push_back(Value::integer((int64_t)(x % (uint64_t)(n * 10 + 10)) + 1));
    }
    if (kind == "sorted") std::sort(items.begin(), items.end(), [](const Value& a, const Value& b) { return a.i < b.i; });
    else if (kind == "reversed") std::sort(items.begin(), items.end(), [](const Value& a, const Value& b) { return a.i > b.i; });
    return mklist(std::move(items));
}

static Measure measureOne(VM& vm, Observer& ob, const Value& fn, const std::string& kind, int64_t n, uint64_t budget) {
    Measure m;
    m.input = makeInput(kind, n);
    ob.instr = ob.compares = ob.swaps = ob.writes = ob.calls = 0;
    ob.callsByName.clear();
    ob.lastWrites.clear();
    ob.maxInstr = budget;
    vm.frames.clear();
    vm.handlers.clear();
    vm.openUps.clear();
    vm.spTop = vm.stack;
    auto t0 = std::chrono::steady_clock::now();
    try {
        m.result = vm.call(fn, {m.input});
        m.ok = true;
    } catch (const PlainError& e) {
        m.error = e.msg;
        m.tooSlow = e.fatal;
    }
    m.ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    m.cmp = ob.compares; m.swaps = ob.swaps; m.writes = ob.writes; m.calls = ob.calls; m.instr = ob.instr;
    return m;
}

static uint64_t metricOf(const Measure& m, const std::string& metric) {
    if (metric == "comparisons") return m.cmp;
    if (metric == "swaps") return m.swaps;
    if (metric == "writes") return m.writes;
    if (metric == "calls") return m.calls;
    return m.instr;
}

// Which family of curves do these (size, work) points follow? Fit each in log space.
static std::string classifyGrowth(const std::vector<double>& n, const std::vector<double>& y, double* scaleOut = nullptr) {
    if (n.size() < 3) return "";
    struct Model { const char* name; double (*f)(double); };
    static const Model models[] = {
        {"O(1)", [](double) { return 0.0; }},
        {"O(log n)", [](double x) { return std::log(std::log2(x) + 1.0); }},
        {"O(n)", [](double x) { return std::log(x); }},
        {"O(n log n)", [](double x) { return std::log(x * (std::log2(x) + 1.0)); }},
        {"O(n^2)", [](double x) { return 2 * std::log(x); }},
        {"O(n^3)", [](double x) { return 3 * std::log(x); }},
        {"O(2^n)", [](double x) { return x * std::log(2.0); }},
    };
    const char* best = "";
    double bestErr = 1e300;
    double bestMean = 0;
    for (const Model& m : models) {
        double wsum = 0, mean = 0;
        std::vector<double> d;
        for (size_t i = 0; i < n.size(); ++i) {
            double w = (double)(i + 1);
            d.push_back(std::log(std::max(y[i], 1.0)) - m.f(n[i]));
            mean += w * d.back();
            wsum += w;
        }
        mean /= wsum;
        double err = 0;
        for (size_t i = 0; i < n.size(); ++i) err += (double)(i + 1) * (d[i] - mean) * (d[i] - mean);
        err = std::sqrt(err / wsum);
        if (err < bestErr - 0.03) { bestErr = err; best = m.name; bestMean = mean; }  // ties go to the simpler curve
    }
    if (scaleOut) *scaleOut = std::exp(bestMean);
    return best;
}

struct Series {
    std::string name;
    std::vector<Measure> runs;  // per size
    std::vector<bool> estimated;
    std::vector<double> value;  // the plotted metric (estimates filled in)
    std::string growth;
    double scale = 0;
    std::string verdict;
};

static std::vector<int64_t> parseSizes(const std::string& text) {
    std::vector<int64_t> out;
    std::string cur;
    for (char c : text + ",") {
        if (c == ',') {
            if (!cur.empty()) out.push_back(std::max<int64_t>(1, atoll(cur.c_str())));
            cur.clear();
        } else if (isdigit((unsigned char)c)) {
            cur += c;
        }
    }
    return out;
}

static std::string nameOfInput(const std::string& k) {
    return k == "list" ? "random list" : k == "sorted" ? "sorted list" : k == "reversed" ? "reversed list" : k == "number" ? "number" : "text";
}

// Load a program quietly and find the actions to test.
struct Loaded {
    std::unique_ptr<WatchedRun> run;
    std::unique_ptr<VM> vm;
    std::string src, file;
};
static bool loadForTesting(const std::string& file, const std::vector<std::string>& names, Loaded& L, std::vector<Value>& fns) {
    L.file = file;
    if (!readFile(file, L.src)) { fprintf(stderr, "I couldn't open the file '%s'.\n", file.c_str()); return false; }
    L.run = std::make_unique<WatchedRun>();
    setUp(L.run->prog);
    L.vm = std::make_unique<VM>(L.run->prog);
    L.run->ob.capture = true;
    L.run->ob.maxInstr = 400000000;
    L.vm->obs = &L.run->ob;
    try {
        Compiler compiler(L.run->prog, L.src, file);
        Value mainFn = compiler.compileMain();
        L.vm->run(mainFn);  // the program's own lines run first (what it says is not shown)
    } catch (const PlainError& e) {
        report(e, file, L.src, &L.run->prog);
        return false;
    }
    Program& prog = L.run->prog;
    for (const std::string& name : names) {
        auto it = prog.gslot.find(name);
        Value v = it == prog.gslot.end() ? Value::undef() : prog.gvals[(size_t)it->second];
        if (!isKind(v, Kind::Closure) || static_cast<Closure*>(v.o)->fn->nparams != 1) {
            std::string avail;
            for (size_t i = 0; i < prog.gnames.size(); ++i)
                if (prog.gdeclared[i] && isKind(prog.gvals[i], Kind::Closure) && static_cast<Closure*>(prog.gvals[i].o)->fn->nparams == 1)
                    avail += (avail.empty() ? "" : ", ") + prog.gnames[i];
            fprintf(stderr, "I couldn't find an action called '%s' that takes one value in %s.%s\n", name.c_str(), file.c_str(),
                    avail.empty() ? " (Define it with: define name with xs)" : (" Actions I can test: " + avail + ".").c_str());
            return false;
        }
        fns.push_back(v);
    }
    return true;
}

static void printBar(double v, double maxV, int width = 34) {
    int n = maxV <= 0 ? 0 : (int)std::round(v / maxV * width);
    if (v > 0 && n == 0) n = 1;
    for (int i = 0; i < n; ++i) fputs("\xE2\x96\x88", stdout);
}

// plain growth program.plain action [action ...] [--input list|sorted|reversed|number|text] [--sizes 10,100,1000,10000]
//                                                [--measure instructions|comparisons|swaps|writes|calls] [--html chart.html] [--budget N]
static int growthCommand(const std::vector<std::string>& args) {
    std::string file, kind = "list", metric = "instructions", html;
    std::vector<std::string> names;
    std::vector<int64_t> sizes = {10, 100, 1000, 10000};
    uint64_t budget = 200000000;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--input" && i + 1 < args.size()) kind = args[++i];
        else if (args[i] == "--sizes" && i + 1 < args.size()) sizes = parseSizes(args[++i]);
        else if (args[i] == "--measure" && i + 1 < args.size()) metric = args[++i];
        else if (args[i] == "--html" && i + 1 < args.size()) html = args[++i];
        else if (args[i] == "--budget" && i + 1 < args.size()) budget = (uint64_t)std::max(1000LL, atoll(args[++i].c_str()));
        else if (file.empty()) file = args[i];
        else names.push_back(args[i]);
    }
    if (file.empty() || names.empty()) {
        fprintf(stderr, "Tell me the program and the action to try, like: plain growth sorting.plain bubble_sort merge_sort\n");
        return 2;
    }
    if (kind != "list" && kind != "sorted" && kind != "reversed" && kind != "number" && kind != "text") {
        fprintf(stderr, "--input can be list, sorted, reversed, number or text.\n");
        return 2;
    }
    if (metric != "instructions" && metric != "comparisons" && metric != "swaps" && metric != "writes" && metric != "calls") {
        fprintf(stderr, "--measure can be instructions, comparisons, swaps, writes or calls.\n");
        return 2;
    }
    if (sizes.size() < 2) { fprintf(stderr, "Give at least two sizes, like --sizes 10,100,1000\n"); return 2; }
    Loaded L;
    std::vector<Value> fns;
    if (!loadForTesting(file, names, L, fns)) return 1;

    std::vector<Series> all;
    for (size_t a = 0; a < names.size(); ++a) {
        Series s;
        s.name = names[a];
        bool stopped = false;
        for (int64_t n : sizes) {
            Measure m;
            if (!stopped) {
                m = measureOne(*L.vm, L.run->ob, fns[a], kind, n, budget);
                if (!m.ok && !m.tooSlow) {
                    PlainError e;
                    e.msg = m.error;
                    fprintf(stderr, "\n'%s' stopped with a problem when n = %lld: %s\n", names[a].c_str(), (long long)n, m.error.c_str());
                    return 1;
                }
                if (m.tooSlow) stopped = true;
            }
            s.runs.push_back(m);
        }
        // fill in what was too slow to run, from the curve of the sizes that did run
        std::vector<double> ns, ys;
        for (size_t i = 0; i < sizes.size(); ++i) {
            if (s.runs[i].ok) { ns.push_back((double)sizes[i]); ys.push_back((double)metricOf(s.runs[i], metric)); }
        }
        for (size_t i = 0; i < sizes.size(); ++i) {
            bool est = !s.runs[i].ok;
            double v = 0;
            if (!est) v = (double)metricOf(s.runs[i], metric);
            else if (ns.size() >= 2) {
                double k = std::log(std::max(ys.back(), 1.0) / std::max(ys[ys.size() - 2], 1.0)) / std::log(ns.back() / ns[ns.size() - 2]);
                v = ys.back() * std::pow((double)sizes[i] / ns.back(), std::max(0.0, k));
            } else {
                est = true;
                v = 0;
            }
            s.estimated.push_back(est);
            s.value.push_back(v);
        }
        s.growth = classifyGrowth(ns, ys, &s.scale);
        if (s.growth.empty()) s.verdict = "not enough sizes ran to tell how it grows.";
        else {
            double ratio = ys.back() / std::max(ys[ys.size() - 2], 1.0), bigger = ns.back() / ns[ns.size() - 2];
            char buf[256];
            snprintf(buf, sizeof buf, "grows like %s: %.0fx more data meant about %.0fx more work.", s.growth.c_str(), bigger, ratio);
            s.verdict = buf;
        }
        all.push_back(std::move(s));
    }

    printf("\nHow the work grows with the size of the input (%s input, counting %s)\n", nameOfInput(kind).c_str(), metric.c_str());
    for (const Series& s : all) {
        printf("\n  %s\n", s.name.c_str());
        printf("  %10s  %14s %14s %12s %16s  %8s  %8s\n", "n", "comparisons", "swaps", "calls", "instructions", "x bigger", "time");
        double maxV = 0;
        for (double v : s.value) maxV = std::max(maxV, v);
        for (size_t i = 0; i < sizes.size(); ++i) {
            const Measure& m = s.runs[i];
            std::string ratio;
            if (i > 0 && s.value[i - 1] > 0 && s.value[i] > 0) {
                char b[32];
                double r = s.value[i] / s.value[i - 1];
                snprintf(b, sizeof b, r < 10 ? "%.1fx" : "%.0fx", r);
                ratio = b;
            }
            if (m.ok) {
                char t[32];
                snprintf(t, sizeof t, "%.1f ms", m.ms);
                printf("  %10s  %14s %14s %12s %16s  %8s  %8s  ", withCommas((uint64_t)sizes[i]).c_str(), withCommas(m.cmp).c_str(),
                       withCommas(m.swaps).c_str(), withCommas(m.calls).c_str(), withCommas(m.instr).c_str(), ratio.c_str(), t);
            } else {
                printf("  %10s  %s ~%s %s  ", withCommas((uint64_t)sizes[i]).c_str(), "too slow to run:", withCommas((uint64_t)s.value[i]).c_str(),
                       (metric + " (estimated)").c_str());
            }
            printBar(s.value[i], maxV);
            printf("\n");
        }
        printf("  -> %s\n", s.verdict.c_str());
    }
    bool anySkipped = false;
    for (const Series& s : all)
        for (const Measure& m : s.runs)
            if (!m.ok) anySkipped = true;
    if (anySkipped) printf("\n(Sizes marked too slow would take more than %s steps here. Allow more with --budget.)\n", withCommas(budget).c_str());
    if (!html.empty()) {
        const char* tmpl = packedFile("viz/growth.html");
        std::string js = "{\"file\":";
        Observer::jsonString(js, file);
        js += ",\"metric\":";
        Observer::jsonString(js, metric);
        js += ",\"input\":";
        Observer::jsonString(js, nameOfInput(kind));
        js += ",\"sizes\":[";
        for (size_t i = 0; i < sizes.size(); ++i) js += (i ? "," : "") + std::to_string(sizes[i]);
        js += "],\"series\":[";
        for (size_t a = 0; a < all.size(); ++a) {
            if (a) js += ",";
            js += "{\"name\":";
            Observer::jsonString(js, all[a].name);
            js += ",\"verdict\":";
            Observer::jsonString(js, all[a].verdict);
            if (!all[a].growth.empty()) {
                char b[64];
                snprintf(b, sizeof b, "%.6g", all[a].scale);
                js += ",\"fit\":{\"name\":";
                Observer::jsonString(js, all[a].growth);
                js += std::string(",\"a\":") + b + "}";
            }
            js += ",\"points\":[";
            for (size_t i = 0; i < sizes.size(); ++i) {
                char b[64];
                snprintf(b, sizeof b, "%.0f", all[a].value[i]);
                js += std::string(i ? "," : "") + "{\"n\":" + std::to_string(sizes[i]) + ",\"v\":" + b + ",\"est\":" + (all[a].estimated[i] ? "true" : "false") + "}";
            }
            js += "]}";
        }
        js += "]}";
        std::string page = replaceFirst(tmpl, "/*__PLAIN_DATA__*/null", js);
        FILE* f = fopen(html.c_str(), "wb");
        if (!f) { fprintf(stderr, "I couldn't write to '%s'.\n", html.c_str()); return 2; }
        fwrite(page.data(), 1, page.size(), f);
        fclose(f);
        printf("\nChart written to %s - open it in a browser to see the curves bend.\n", html.c_str());
    } else {
        printf("\nAdd  --html chart.html  to draw these curves.\n");
    }
    return 0;
}

// plain compare program.plain action_a action_b [--size 300] [--input ...]
static int compareCommand(const std::vector<std::string>& args) {
    std::string file, kind = "list";
    std::vector<std::string> names;
    int64_t size = 300;
    uint64_t budget = 1000000000;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--input" && i + 1 < args.size()) kind = args[++i];
        else if (args[i] == "--size" && i + 1 < args.size()) size = std::max<int64_t>(1, atoll(args[++i].c_str()));
        else if (file.empty()) file = args[i];
        else names.push_back(args[i]);
    }
    if (file.empty() || names.size() < 2) {
        fprintf(stderr, "Tell me the program and two actions, like: plain compare sorting.plain bubble_sort merge_sort\n");
        return 2;
    }
    Loaded L;
    std::vector<Value> fns;
    if (!loadForTesting(file, names, L, fns)) return 1;
    std::vector<Measure> ms;
    for (size_t a = 0; a < names.size(); ++a) {
        Measure m = measureOne(*L.vm, L.run->ob, fns[a], kind, size, budget);
        if (!m.ok) {
            fprintf(stderr, "\n'%s' stopped with a problem: %s\n", names[a].c_str(), m.error.c_str());
            return 1;
        }
        ms.push_back(m);
    }
    printf("\nComparing on the same %s of %s items\n\n", nameOfInput(kind).c_str(), withCommas((uint64_t)size).c_str());
    printf("  %-14s", "");
    for (const std::string& n : names) printf(" %16s", n.c_str());
    printf("\n");
    struct Row { const char* label; uint64_t Measure::*field; };
    const Row rows[] = {{"comparisons", &Measure::cmp}, {"swaps", &Measure::swaps}, {"list writes", &Measure::writes},
                        {"calls", &Measure::calls}, {"instructions", &Measure::instr}};
    for (const Row& r : rows) {
        printf("  %-14s", r.label);
        for (const Measure& m : ms) printf(" %16s", withCommas(m.*(r.field)).c_str());
        printf("\n");
    }
    printf("\n  work (instructions)\n");
    double maxV = 0;
    for (const Measure& m : ms) maxV = std::max(maxV, (double)m.instr);
    for (size_t a = 0; a < names.size(); ++a) {
        printf("  %-14s ", names[a].c_str());
        printBar((double)ms[a].instr, maxV, 44);
        printf("\n");
    }
    // do they agree? a sort that changes the list in place gives back nothing, so compare the lists themselves
    bool same = true;
    for (size_t a = 1; a < ms.size(); ++a) {
        const Value& x = ms[0].result.tag == Value::Nothing ? ms[0].input : ms[0].result;
        const Value& y = ms[a].result.tag == Value::Nothing ? ms[a].input : ms[a].result;
        if (!equals(x, y)) same = false;
    }
    printf("\n  Same answer from all of them: %s\n", same ? "yes" : "NO - they disagree, so at least one is wrong");
    size_t best = 0, worst = 0;
    for (size_t a = 1; a < ms.size(); ++a) {
        if (ms[a].instr < ms[best].instr) best = a;
        if (ms[a].instr > ms[worst].instr) worst = a;
    }
    if (best != worst && ms[best].instr > 0)
        printf("  %s did %.1fx less work than %s on this data.\n", names[best].c_str(), (double)ms[worst].instr / (double)ms[best].instr, names[worst].c_str());
    printf("  (Try a bigger --size, or  plain growth  to see how each one grows.)\n");
    return same ? 0 : 1;
}
