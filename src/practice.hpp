// Plain - "plain practice": classic problems checked against hidden tests.
//
// A problem is a Plain file in lib/problems: a map called __problem (statement, tests,
// hints, explanation) and a working solution called __reference, between the lines
//   # --- solution ---   and   # --- end solution ---
// so the reference is real code that "plain practice --selftest" runs against every test.
#pragma once
#include <map>
#include <sstream>

struct ProblemInfo {
    std::string id, title, topic, action, params, statement, complexity, explanation, mode, solutionText;
    int level = 1, order = 0;
    struct Test { Value args, expect; std::string note; };
    std::vector<Test> examples, hidden;
    std::vector<std::string> hints;
};

static Value* mapGet(const Value& m, const char* key) { return isMap(m) ? asMap(m)->find(mkstr(key)) : nullptr; }
static std::string mapStr(const Value& m, const char* key) {
    Value* v = mapGet(m, key);
    return v && isStr(*v) ? asStr(*v) : "";
}

static Value deepCopy(const Value& v) {
    if (isList(v)) {
        std::vector<Value> items;
        for (const Value& x : asList(v)->items) items.push_back(deepCopy(x));
        return mklist(std::move(items));
    }
    if (isMap(v)) {
        Map* m = new Map;
        Value out = Value::obj(m);
        for (const auto& e : asMap(v)->entries) m->set(e.first, deepCopy(e.second));
        return out;
    }
    return v;
}

static std::string clip(const std::string& s, size_t n = 78) { return s.size() > n ? s.substr(0, n - 3) + "..." : s; }

static std::string wrapText(const std::string& text, size_t width, const std::string& prefix) {
    std::string out, line;
    std::istringstream paragraphs(text);
    std::string para;
    bool first = true;
    while (std::getline(paragraphs, para)) {
        if (!first) { out += prefix + "\n"; }
        first = false;
        line.clear();
        std::istringstream words(para);
        std::string w;
        while (words >> w) {
            if (!line.empty() && line.size() + 1 + w.size() + prefix.size() > width) { out += prefix + line + "\n"; line.clear(); }
            line += (line.empty() ? "" : " ") + w;
        }
        out += prefix + line + "\n";
    }
    return out;
}

// Load one problem into a program. 'vm' must belong to 'prog'.
static bool loadProblem(Program& prog, VM& vm, const std::string& id, ProblemInfo& p) {
    const char* text = packedFile("problems/" + id);
    if (!text) return false;
    std::string src = text;
    Compiler c(prog, src, "<lib>/problems/" + id + ".plain");
    Value m = c.compileMain();
    vm.run(m);
    auto it = prog.gslot.find("__problem");
    if (it == prog.gslot.end() || !isMap(prog.gvals[(size_t)it->second])) return false;
    Value d = prog.gvals[(size_t)it->second];
    p.id = id;
    p.title = mapStr(d, "title");
    p.topic = mapStr(d, "topic");
    p.action = mapStr(d, "function");
    p.params = mapStr(d, "params");
    p.statement = mapStr(d, "statement");
    p.complexity = mapStr(d, "complexity");
    p.explanation = mapStr(d, "explanation");
    p.mode = mapStr(d, "mode");
    if (Value* v = mapGet(d, "level")) p.level = (int)v->i;
    if (Value* v = mapGet(d, "order")) p.order = (int)v->i;
    auto readTests = [&](const char* key, std::vector<ProblemInfo::Test>& out) {
        Value* v = mapGet(d, key);
        if (!v || !isList(*v)) return;
        for (const Value& t : asList(*v)->items) {
            ProblemInfo::Test x;
            if (Value* a = mapGet(t, "args")) x.args = *a;
            if (Value* e = mapGet(t, "expect")) x.expect = *e;
            x.note = mapStr(t, "note");
            out.push_back(std::move(x));
        }
    };
    readTests("examples", p.examples);
    readTests("hidden", p.hidden);
    if (Value* h = mapGet(d, "hints"))
        if (isList(*h))
            for (const Value& x : asList(*h)->items) p.hints.push_back(fmt(x));
    // the reference solution's own text, shown by --solution
    size_t a = src.find("# --- solution ---\n"), b = src.find("# --- end solution ---");
    if (a != std::string::npos && b != std::string::npos && b > a) {
        p.solutionText = src.substr(a + 19, b - a - 19);
        size_t at;
        while ((at = p.solutionText.find("__reference")) != std::string::npos) p.solutionText.replace(at, 11, p.action);
    }
    return true;
}

static std::vector<std::string> problemIds() {
    std::vector<std::string> ids;
    for (const LibFile* f = LIB_FILES; f->name; ++f)
        if (strncmp(f->name, "problems/", 9) == 0) ids.push_back(f->name + 9);
    return ids;
}

static std::vector<ProblemInfo> loadAllProblems() {
    std::vector<ProblemInfo> all;
    for (const std::string& id : problemIds()) {
        Program prog;
        setUp(prog);
        VM vm(prog);
        ProblemInfo p;
        try {
            if (loadProblem(prog, vm, id, p)) all.push_back(std::move(p));
        } catch (const PlainError& e) {
            fprintf(stderr, "Problem '%s' has a mistake: %s\n", id.c_str(), e.msg.c_str());
        }
    }
    std::sort(all.begin(), all.end(), [](const ProblemInfo& a, const ProblemInfo& b) { return a.order < b.order; });
    return all;
}

// ---- progress: a small file in the current folder
struct Progress { int hints = 0; bool solved = false; };
static std::map<std::string, Progress> readProgress() {
    std::map<std::string, Progress> m;
    std::string text;
    if (!readFile(".plain-practice", text)) return m;
    std::istringstream in(text);
    std::string id;
    int hints, solved;
    while (in >> id >> hints >> solved) m[id] = {hints, solved != 0};
    return m;
}
static void writeProgress(const std::map<std::string, Progress>& m) {
    std::string out;
    for (const auto& e : m) out += e.first + " " + std::to_string(e.second.hints) + " " + (e.second.solved ? "1" : "0") + "\n";
    FILE* f = fopen(".plain-practice", "wb");
    if (!f) return;
    fwrite(out.data(), 1, out.size(), f);
    fclose(f);
}

static std::string callText(const ProblemInfo& p, const Value& args) {
    std::string s = p.action + "(";
    bool first = true;
    if (isList(args))
        for (const Value& a : asList(args)->items) { s += (first ? "" : ", ") + fmt(a, true); first = false; }
    return s + ")";
}

struct TestRun {
    bool passed = false, tooSlow = false;
    std::string got, error;
    uint64_t instr = 0;
};
static TestRun runTest(VM& vm, Observer& ob, const Value& fn, const ProblemInfo& p, const ProblemInfo::Test& t, uint64_t budget) {
    TestRun r;
    Value args = deepCopy(t.args);
    std::vector<Value> argv = asList(args)->items;
    ob.instr = ob.compares = ob.swaps = ob.writes = ob.calls = 0;
    ob.maxInstr = budget;
    ob.lastWrites.clear();
    vm.frames.clear();
    vm.handlers.clear();
    vm.openUps.clear();
    vm.spTop = vm.stack;
    try {
        Value got = vm.call(fn, argv);
        if (p.mode == "changes") got = argv.empty() ? got : argv[0];
        r.got = fmt(got, true);
        r.passed = equals(got, t.expect);
    } catch (const PlainError& e) {
        r.error = e.msg;
        r.tooSlow = e.fatal;
    }
    r.instr = ob.instr;
    return r;
}

static void showProblem(const ProblemInfo& p) {
    printf("\n%s   (%s, level %d)\n\n", p.title.c_str(), p.topic.c_str(), p.level);
    printf("%s", wrapText(p.statement, 78, "  ").c_str());
    printf("\n  Write an action:  define %s with %s\n\n  Examples:\n", p.action.c_str(), p.params.c_str());
    for (const auto& e : p.examples)
        printf("    %s  should give  %s\n", clip(callText(p, e.args), 60).c_str(), clip(fmt(e.expect, true), 40).c_str());
}

static std::string starterText(const ProblemInfo& p) {
    std::string s = "# " + p.title + "  -  " + p.topic + ", level " + std::to_string(p.level) + "\n#\n";
    s += wrapText(p.statement, 76, "# ");
    s += "#\n# Examples:\n";
    for (const auto& e : p.examples) s += "#   " + clip(callText(p, e.args), 60) + "  should give  " + clip(fmt(e.expect, true), 40) + "\n";
    s += "#\n# Check your solution with:   plain practice " + p.id + "\n# Stuck?                      plain practice " + p.id + " --hint\n\n";
    s += "define " + p.action + " with " + p.params + "\n    # your code here\n    give back nothing\nend\n";
    return s;
}

// Run the problem's tests against a Plain file. Returns 0 when everything passes.
static int checkSolution(const ProblemInfo& p, const std::string& file, std::map<std::string, Progress>& progress) {
    std::string src;
    if (!readFile(file, src)) { fprintf(stderr, "I couldn't open '%s'.\n", file.c_str()); return 2; }
    auto run = std::make_unique<WatchedRun>();
    setUp(run->prog);
    VM vm(run->prog);
    ProblemInfo again;
    try { loadProblem(run->prog, vm, p.id, again); } catch (const PlainError&) {}
    run->ob.capture = true;
    run->ob.maxInstr = 100000000;
    vm.obs = &run->ob;
    try {
        Compiler compiler(run->prog, src, file);
        Value mainFn = compiler.compileMain();
        vm.run(mainFn);
    } catch (const PlainError& e) {
        printf("\nI couldn't run %s yet:\n", file.c_str());
        fflush(stdout);
        report(e, file, src, &run->prog);
        return 1;
    }
    auto it = run->prog.gslot.find(p.action);
    Value fn = it == run->prog.gslot.end() ? Value::undef() : run->prog.gvals[(size_t)it->second];
    int want = (int)(p.examples.empty() ? 0 : asList(p.examples[0].args)->items.size());
    if (!isKind(fn, Kind::Closure)) {
        printf("\nI couldn't find an action called '%s' in %s.\nIt should start with:  define %s with %s\n", p.action.c_str(), file.c_str(), p.action.c_str(), p.params.c_str());
        return 1;
    }
    if (static_cast<Closure*>(fn.o)->fn->nparams != want) {
        printf("\n'%s' should take %d value(s) (%s), but yours takes %d.\n", p.action.c_str(), want, p.params.c_str(), static_cast<Closure*>(fn.o)->fn->nparams);
        return 1;
    }
    printf("\nChecking %s against %zu examples and %zu hidden tests\n\n", p.action.c_str(), p.examples.size(), p.hidden.size());
    int failed = 0;
    size_t ex = 0;
    uint64_t yours = 0;
    auto describeProblem = [&](const TestRun& r) {
        if (r.tooSlow) return std::string("it ran far too long (is there a loop that never ends, or is it too slow?)");
        return "it stopped with a problem: " + r.error;
    };
    bool timedOut = false;
    const uint64_t TEST_BUDGET = 120000000;
    for (const auto& t : p.examples) {
        TestRun r = runTest(vm, run->ob, fn, p, t, TEST_BUDGET);
        yours += r.instr;
        ++ex;
        if (r.passed) { printf("  \xE2\x9C\x93 example %zu  %s  gave  %s\n", ex, clip(callText(p, t.args), 44).c_str(), clip(r.got, 24).c_str()); continue; }
        ++failed;
        printf("  \xE2\x9C\x97 example %zu  %s\n", ex, clip(callText(p, t.args), 66).c_str());
        if (!r.error.empty()) printf("      %s\n", describeProblem(r).c_str());
        else printf("      expected  %s\n      got       %s\n", clip(fmt(t.expect, true), 62).c_str(), clip(r.got, 62).c_str());
        if (r.tooSlow) { timedOut = true; break; }
    }
    int hiddenFailed = 0, shown = 0;
    size_t idx = 0;
    for (const auto& t : p.hidden) {
        if (timedOut) break;
        TestRun r = runTest(vm, run->ob, fn, p, t, TEST_BUDGET);
        yours += r.instr;
        ++idx;
        if (r.passed) continue;
        ++hiddenFailed;
        if (shown++ < 3) {
            printf("  \xE2\x9C\x97 hidden test %zu of %zu failed", idx, p.hidden.size());
            if (!t.note.empty()) printf("  (it checks: %s)", t.note.c_str());
            printf("\n");
            if (!r.error.empty()) printf("      %s\n", describeProblem(r).c_str());
        }
        if (r.tooSlow) timedOut = true;
    }
    if (timedOut) {
        printf("\n  I stopped checking after a test ran for more than %s steps.\n  Is there a loop that never ends? If it is just slow, look for a way to do less work (see --hint).\n", withCommas(TEST_BUDGET).c_str());
        printf("\nTry  plain visualize %s  to watch it run, or  plain practice %s --hint\n", file.c_str(), p.id.c_str());
        return 1;
    }
    printf("  %s hidden tests: %zu of %zu passed\n", hiddenFailed ? "\xE2\x9C\x97" : "\xE2\x9C\x93", p.hidden.size() - (size_t)hiddenFailed, p.hidden.size());
    failed += hiddenFailed;
    if (failed) {
        printf("\n%d test%s failed. Try  plain visualize %s  to watch it run, or  plain practice %s --hint\n", failed, failed == 1 ? "" : "s", file.c_str(), p.id.c_str());
        return 1;
    }
    // the reference, for comparison of the work done
    uint64_t ref = 0;
    auto rit = run->prog.gslot.find("__reference");
    if (rit != run->prog.gslot.end()) {
        Value rf = run->prog.gvals[(size_t)rit->second];
        for (const auto* set : {&p.examples, &p.hidden})
            for (const auto& t : *set) ref += runTest(vm, run->ob, rf, p, t, 2000000000ULL).instr;
    }
    printf("\nAll tests passed. Well done!\n");
    printf("  Work done on all the tests: yours %s steps", withCommas(yours).c_str());
    if (ref) printf(", the reference solution %s steps", withCommas(ref).c_str());
    printf("\n");
    if (ref && yours > ref * 6)
        printf("  Yours is correct but does much more work than it needs to. Try  plain practice %s --solution  to see a faster way,\n  or  plain growth %s %s  to see how your work grows.\n",
               p.id.c_str(), file.c_str(), p.action.c_str());
    else if (!p.complexity.empty())
        printf("  A good solution is %s.\n", p.complexity.c_str());
    progress[p.id].solved = true;
    return 0;
}

// plain practice [problem] [--hint] [--solution] [--show] [--file name.plain] [--selftest]
static int practiceCommand(const std::vector<std::string>& args) {
    std::string id, file;
    bool hint = false, solution = false, show = false, selftest = false, giveUp = false, json = false;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--hint") hint = true;
        else if (args[i] == "--solution") solution = true;
        else if (args[i] == "--show") show = true;
        else if (args[i] == "--selftest") selftest = true;
        else if (args[i] == "--give-up") giveUp = true;
        else if (args[i] == "--json") json = true;
        else if (args[i] == "--file" && i + 1 < args.size()) file = args[++i];
        else id = args[i];
    }
    std::vector<ProblemInfo> all = loadAllProblems();
    if (json) {
        // The problems for the documentation site: what to do and the examples. Never the hidden
        // tests, hints or solutions, so publishing the list spoils nothing.
        std::string o = "{\"problems\":[";
        for (size_t i = 0; i < all.size(); ++i) {
            const ProblemInfo& p = all[i];
            if (i) o += ",";
            o += "{\"id\":";
            Observer::jsonString(o, p.id);
            for (const auto& kv : std::vector<std::pair<const char*, const std::string*>>{
                     {"title", &p.title}, {"topic", &p.topic}, {"action", &p.action}, {"params", &p.params},
                     {"statement", &p.statement}, {"complexity", &p.complexity}}) {
                o += std::string(",\"") + kv.first + "\":";
                Observer::jsonString(o, *kv.second);
            }
            o += ",\"level\":" + std::to_string(p.level) + ",\"hidden_tests\":" + std::to_string(p.hidden.size()) +
                 ",\"hints\":" + std::to_string(p.hints.size()) + ",\"examples\":[";
            for (size_t k = 0; k < p.examples.size(); ++k) {
                if (k) o += ",";
                o += "{\"call\":";
                Observer::jsonString(o, callText(p, p.examples[k].args));
                o += ",\"gives\":";
                Observer::jsonString(o, fmt(p.examples[k].expect, true));
                o += "}";
            }
            o += "]}";
        }
        printf("%s]}\n", o.c_str());
        return 0;
    }
    if (selftest) {
        int bad = 0;
        size_t tests = 0;
        for (const ProblemInfo& p : all) {
            Program prog;
            setUp(prog);
            VM vm(prog);
            ProblemInfo q;
            loadProblem(prog, vm, p.id, q);
            Observer ob;
            ob.capture = true;
            vm.obs = &ob;
            Value rf = prog.gvals[(size_t)prog.gslot["__reference"]];
            if (q.solutionText.empty()) { printf("%s: no solution text between the markers\n", p.id.c_str()); ++bad; }
            if (q.hints.size() < 2 || q.explanation.empty() || q.examples.empty() || q.hidden.size() < 4) { printf("%s: needs hints, an explanation, examples and hidden tests\n", p.id.c_str()); ++bad; }
            for (const auto* set : {&q.examples, &q.hidden})
                for (const auto& t : *set) {
                    ++tests;
                    TestRun r = runTest(vm, ob, rf, q, t, 2000000000ULL);
                    if (!r.passed) {
                        ++bad;
                        printf("%s: the reference solution fails %s: expected %s, got %s %s\n", p.id.c_str(), clip(callText(q, t.args), 50).c_str(),
                               clip(fmt(t.expect, true), 30).c_str(), clip(r.got, 40).c_str(), clip(r.error, 80).c_str());
                    }
                }
        }
        printf("%zu problems, %zu tests: %s\n", all.size(), tests, bad ? "PROBLEMS FOUND" : "every reference solution passes");
        return bad ? 1 : 0;
    }
    std::map<std::string, Progress> progress = readProgress();
    if (id.empty()) {
        printf("\nPractice problems. Start one with:  plain practice two-sum\n\n");
        std::string lastTopic;
        for (const ProblemInfo& p : all) {
            if (p.topic != lastTopic) { printf("%s%s\n", lastTopic.empty() ? "" : "\n", p.topic.c_str()); lastTopic = p.topic; }
            printf("  %-24s %-34s level %d %s\n", p.id.c_str(), p.title.c_str(), p.level, progress[p.id].solved ? " \xE2\x9C\x93 solved" : "");
        }
        printf("\n");
        return 0;
    }
    const ProblemInfo* found = nullptr;
    for (const ProblemInfo& p : all)
        if (p.id == id) found = &p;
    if (!found) {
        std::vector<std::string> names;
        for (const ProblemInfo& p : all) names.push_back(p.id);
        std::string c = closest(id, names);
        fprintf(stderr, "There is no problem called '%s'.%s See them all with: plain practice\n", id.c_str(), c.empty() ? "" : (" Did you mean '" + c + "'?").c_str());
        return 2;
    }
    const ProblemInfo& p = *found;
    Progress& pr = progress[p.id];
    if (show) { showProblem(p); return 0; }
    if (hint) {
        if (pr.hints >= (int)p.hints.size()) {
            printf("\nThat was the last hint (%zu of %zu). To see a reference solution with an explanation:  plain practice %s --solution\n", p.hints.size(), p.hints.size(), p.id.c_str());
            return 0;
        }
        printf("\nHint %d of %zu:\n%s", pr.hints + 1, p.hints.size(), wrapText(p.hints[(size_t)pr.hints], 78, "  ").c_str());
        ++pr.hints;
        printf("\n%s\n", pr.hints < (int)p.hints.size() ? ("Another hint:  plain practice " + p.id + " --hint").c_str()
                                                       : ("That was the last hint. Next:  plain practice " + p.id + " --solution").c_str());
        writeProgress(progress);
        return 0;
    }
    if (solution) {
        if (!pr.solved && pr.hints < (int)p.hints.size() && !giveUp) {
            printf("\nTry the hints first (you have seen %d of %zu):  plain practice %s --hint\nOr see the solution anyway:  plain practice %s --solution --give-up\n",
                   pr.hints, p.hints.size(), p.id.c_str(), p.id.c_str());
            return 0;
        }
        printf("\n%s - a reference solution\n\n%s\n", p.title.c_str(), p.solutionText.c_str());
        printf("How it works\n%s", wrapText(p.explanation, 78, "  ").c_str());
        if (!p.complexity.empty()) printf("\n  %s\n", p.complexity.c_str());
        printf("\nSee it run:  copy it into a file and use  plain visualize file.plain\n");
        return 0;
    }
    std::string path = file.empty() ? p.id + ".plain" : file;
    if (!fileExists(path)) {
        if (!file.empty()) { fprintf(stderr, "I couldn't find '%s'.\n", path.c_str()); return 2; }
        FILE* f = fopen(path.c_str(), "wb");
        if (!f) { fprintf(stderr, "I couldn't write '%s'.\n", path.c_str()); return 2; }
        std::string text = starterText(p);
        fwrite(text.data(), 1, text.size(), f);
        fclose(f);
        showProblem(p);
        printf("\nI made %s for you. Write your solution in it, then check it with:\n  plain practice %s\n", path.c_str(), p.id.c_str());
        return 0;
    }
    int code = checkSolution(p, path, progress);
    writeProgress(progress);
    return code;
}
