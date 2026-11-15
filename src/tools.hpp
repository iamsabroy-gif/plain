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
