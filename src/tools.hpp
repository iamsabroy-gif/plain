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

// Names listed in comment lines like:   # watch: xs, total
static std::vector<std::string> watchNames(const std::string& src) {
    std::vector<std::string> out;
    size_t at = 0;
    while (at < src.size()) {
        size_t end = src.find('\n', at);
        if (end == std::string::npos) end = src.size();
        std::string line = src.substr(at, end - at);
        at = end + 1;
        size_t hash = line.find('#');
        if (hash == std::string::npos) continue;
        std::string c = line.substr(hash + 1);
        size_t a = c.find_first_not_of(" \t");
        if (a == std::string::npos || c.compare(a, 6, "watch:") != 0) continue;
        std::string names = c.substr(a + 6), cur;
        for (char ch : names + ",") {
            if (ch == ',' || ch == ' ' || ch == '\t') {
                if (!cur.empty()) out.push_back(cur);
                cur.clear();
            } else {
                cur += ch;
            }
        }
    }
    return out;
}

static std::string replaceFirst(std::string text, const std::string& what, const std::string& with) {
    size_t at = text.find(what);
    if (at != std::string::npos) text.replace(at, what.size(), with);
    return text;
}

// plain visualize program.plain [-o page.html] [--max-steps N] [--into-library]
static int visualizeCommand(const std::vector<std::string>& args) {
    std::string file, out;
    size_t maxSteps = 6000;
    bool intoLib = false;
    uint64_t budget = 300000000;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-o" && i + 1 < args.size()) out = args[++i];
        else if (args[i] == "--budget" && i + 1 < args.size()) budget = (uint64_t)std::max(1LL, atoll(args[++i].c_str()));
        else if (args[i] == "--max-steps" && i + 1 < args.size()) maxSteps = (size_t)std::max(1, atoi(args[++i].c_str()));
        else if (args[i] == "--into-library") intoLib = true;
        else file = args[i];
    }
    if (file.empty()) { fprintf(stderr, "Tell me which program to draw, like: plain visualize program.plain\n"); return 2; }
    std::string src;
    if (!readFile(file, src)) { fprintf(stderr, "I couldn't open the file '%s'.\n", file.c_str()); return 2; }
    if (out.empty()) {
        size_t slash = file.find_last_of("/\\"), dot = file.find_last_of('.');
        std::string base = file.substr(slash == std::string::npos ? 0 : slash + 1);
        dot = base.find_last_of('.');
        out = (dot == std::string::npos ? base : base.substr(0, dot)) + ".html";
    }
    const char* tmpl = packedFile("viz/player.html");
    if (!tmpl) { fprintf(stderr, "This copy of Plain has no player inside it.\n"); return 3; }

    auto run = std::make_unique<WatchedRun>();
    setUp(run->prog);
    VM vm(run->prog);
    run->ob.trace = true;
    run->ob.capture = true;
    run->ob.showLibrary = intoLib;
    run->ob.maxSteps = maxSteps;
    run->ob.maxInstr = budget;
    vm.obs = &run->ob;
    vm.args = {};
    try {
        Compiler compiler(run->prog, src, file);
        Value mainFn = compiler.compileMain();
        vm.run(mainFn);
        run->ob.finish(vm);
    } catch (const PlainError& e) {
        if (run->ob.steps.empty() && !run->ob.pending && e.line && run->ob.outputChunks.empty() && e.file.empty()) {
            report(e, file, src, &run->prog);  // it never started: a mistake in how the program is written
            return 1;
        }
        run->errorMsg = e.msg;
        run->errorLine = e.line;
        run->errorFile = e.file;
    }
    std::vector<std::pair<std::string, std::string>> sources;
    std::vector<std::string> names = run->ob.files;
    if (names.empty()) names.push_back(file);
    for (const std::string& n : names) {
        std::string text;
        if (n == file) text = src;
        else if (const char* lib = libSource(n)) text = lib;
        else
            for (const auto& s : run->prog.sources)
                if (s.first == n) text = s.second;
        sources.emplace_back(n, text);
    }
    run->ob.files = names;
    std::string json = run->ob.traceJson(sources, watchNames(src), run->errorMsg, run->errorLine);
    std::string safe;
    safe.reserve(json.size());
    for (size_t i = 0; i < json.size(); ++i) {
        if (json[i] == '<' && i + 1 < json.size() && json[i + 1] == '/') safe += "<\\/";
        else safe += json[i];
    }
    if (safe.find("\xE2\x80\xA8") != std::string::npos) {}  // (U+2028 is fine inside a JSON string in modern browsers)
    std::string page = replaceFirst(tmpl, "/*__PLAIN_DATA__*/null", safe);
    FILE* f = fopen(out.c_str(), "wb");
    if (!f) { fprintf(stderr, "I couldn't write to '%s'.\n", out.c_str()); return 2; }
    fwrite(page.data(), 1, page.size(), f);
    fclose(f);
    printf("Recorded %zu step%s of %s. Open %s in a browser to watch it.\n", run->ob.steps.size(), run->ob.steps.size() == 1 ? "" : "s",
           file.c_str(), out.c_str());
    if (run->ob.truncated) printf("(It was longer than %zu steps, so the recording stops there. Try a smaller input, or --max-steps.)\n", maxSteps);
    if (!run->errorMsg.empty()) {
        PlainError e;
        e.msg = run->errorMsg;
        e.line = run->errorLine;
        e.file = run->errorFile;
        report(e, file, src, &run->prog);
        return 1;
    }
    return 0;
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
    std::string file;
    for (size_t i = 1; i < args.size(); ++i) file = args[i];
    if (file.empty()) { fprintf(stderr, "Tell me which program to count, like: plain count program.plain\n"); return 2; }
    std::string src;
    if (!readFile(file, src)) { fprintf(stderr, "I couldn't open the file '%s'.\n", file.c_str()); return 2; }
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
