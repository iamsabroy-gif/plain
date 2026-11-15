// Plain - a programming language that reads like English.
//
// Build:  c++ -O2 -std=c++17 -o plain src/main.cpp      (or just: make)
// Run:    plain program.plain
#include <filesystem>

#include "pkg.hpp"

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#define PLAIN_ISATTY(fd) _isatty(fd)
#else
#include <sys/stat.h>
#include <unistd.h>
#define PLAIN_ISATTY(fd) isatty(fd)
#endif
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

using namespace plain;

static const char* VERSION = "2.0.0";
static const char MAGIC[8] = {'P', 'L', 'A', 'I', 'N', 'A', 'P', 'P'};

// The text of one line of a source file, so an error can show where it happened.
static std::string sourceLine(const std::string& text, int line) {
    size_t at = 0;
    for (int l = 1; l < line; ++l) {
        at = text.find('\n', at);
        if (at == std::string::npos) return "";
        ++at;
    }
    size_t end = text.find('\n', at);
    std::string s = text.substr(at, end == std::string::npos ? std::string::npos : end - at);
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) s.pop_back();
    size_t first = s.find_first_not_of(" \t");
    return first == std::string::npos ? "" : s.substr(first);
}

static void report(const PlainError& e, const std::string& mainFile, const std::string& mainSrc = "",
                   const Program* prog = nullptr) {
    fflush(stdout);
    std::string where;
    if (e.line && !e.file.empty() && e.file != mainFile) where = "In " + e.file + ", line " + std::to_string(e.line) + ": ";
    else if (e.line) where = "Line " + std::to_string(e.line) + ": ";
    fprintf(stderr, "\nOops! %s%s\n", where.c_str(), e.msg.c_str());
    if (!e.line) return;
    std::string text;
    if (e.file.empty() || e.file == mainFile) text = mainSrc;
    else if (prog)
        for (const auto& s : prog->sources)
            if (s.first == e.file) text = s.second;
    std::string shown = sourceLine(text, e.line);
    if (!shown.empty()) fprintf(stderr, "  %4d | %s\n", e.line, shown.c_str());
}

static std::string selfPath(const char* argv0) {
#if defined(__APPLE__)
    char buf[4096];
    uint32_t size = sizeof buf;
    if (_NSGetExecutablePath(buf, &size) == 0) return buf;
#elif defined(_WIN32)
    char buf[4096];
    DWORD n = GetModuleFileNameA(nullptr, buf, sizeof buf);
    if (n > 0 && n < sizeof buf) return std::string(buf, n);
#else
    char buf[4096];
    ssize_t n = readlink("/proc/self/exe", buf, sizeof buf - 1);
    if (n > 0) return std::string(buf, (size_t)n);
#endif
    return argv0;
}

static void putU32(std::string& out, uint32_t v) { out.append(reinterpret_cast<const char*>(&v), 4); }
static uint32_t getU32(const std::string& s, size_t at) { uint32_t v; memcpy(&v, s.data() + at, 4); return v; }

// A program made by "plain build" is this same executable with the source
// files attached at the end. Returns them (main file first) if present.
static bool readPayload(const std::string& exe, std::vector<std::pair<std::string, std::string>>& files, size_t* payloadStart = nullptr) {
    if (exe.size() < 20 || memcmp(exe.data() + exe.size() - 8, MAGIC, 8) != 0) return false;
    uint64_t size;
    memcpy(&size, exe.data() + exe.size() - 16, 8);
    uint32_t count = getU32(exe, exe.size() - 20);
    if (size + 20 > exe.size()) return false;
    size_t at = exe.size() - 20 - (size_t)size;
    if (payloadStart) *payloadStart = at;
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t n = getU32(exe, at);
        std::string path = exe.substr(at + 4, n);
        at += 4 + n;
        n = getU32(exe, at);
        files.emplace_back(path, exe.substr(at + 4, n));
        at += 4 + n;
    }
    return true;
}

static void explainTokens(const std::string& src) {
    printf("=== STAGE 1: TOKENS (the text split into words and symbols) ===\n");
    std::string row;
    for (const Token& t : tokenize(src)) {
        if (t.k == Token::NL || t.k == Token::End) {
            if (!row.empty()) printf("%s\n", row.c_str());
            row.clear();
            continue;
        }
        const char* kind = t.k == Token::Num ? "NUM" : t.k == Token::Str ? "TEXT" : t.k == Token::Word ? "NAME" : t.k == Token::Kw ? "WORD" : "SYM";
        row += std::string(row.empty() ? "  " : "  ") + kind + ":" + (t.k == Token::Str ? quote(t.text) : t.text);
    }
}

static void setUp(Program& prog) {
    registerBuiltins(prog);
}

// Leave the program. Background tasks that are still running end with it.
static int finish(int code) {
    fflush(stdout);
    fflush(stderr);
    if (tasksStarted()) _Exit(code);
    return code;
}

static int runProgram(const std::string& src, const std::string& file, const std::vector<std::string>& args,
                      bool explain, bool checkOnly, const std::vector<std::pair<std::string, std::string>>* embedded = nullptr) {
    Program prog;
    setUp(prog);
    if (embedded)
        for (const auto& f : *embedded) {
            if (f.first == "\x01resolved") {
                // lines of: importing file <TAB> name used <TAB> file it resolved to
                size_t at = 0;
                while (at < f.second.size()) {
                    size_t end = f.second.find('\n', at);
                    if (end == std::string::npos) end = f.second.size();
                    std::string line = f.second.substr(at, end - at);
                    at = end + 1;
                    size_t t1 = line.find('\t'), t2 = t1 == std::string::npos ? t1 : line.find('\t', t1 + 1);
                    if (t2 != std::string::npos) prog.resolved[line.substr(0, t1) + "\n" + line.substr(t1 + 1, t2 - t1 - 1)] = line.substr(t2 + 1);
                }
            } else {
                prog.embedded[f.first] = f.second;
            }
        }
    VM vm(prog);
    vm.args = args;
    try {
        if (explain) explainTokens(src);
        Compiler compiler(prog, src, file);
        Value mainFn = compiler.compileMain();
        if (checkOnly) {
            printf("No problems found in %s.\n", file.c_str());
            return 0;
        }
        if (explain) {
            printf("\n=== STAGE 2: BYTECODE (the instructions the compiler produced) ===\n");
            disassemble(prog, *static_cast<Closure*>(mainFn.o)->fn);
            for (const Value& f : prog.funcs) disassemble(prog, *static_cast<Func*>(f.o));
            printf("\n=== STAGE 3: RUNNING (the virtual machine carries out the instructions) ===\n");
        }
        vm.run(mainFn);
        fflush(stdout);
        return 0;
    } catch (const PlainError& e) {
        report(e, file, src, &prog);
        return 1;
    }
}

static int build(const char* argv0, const std::string& file, std::string out) {
    std::string src, exe;
    if (!readFile(file, src)) { fprintf(stderr, "I couldn't open the file '%s'.\n", file.c_str()); return 2; }
    Program prog;
    setUp(prog);
    try {
        Compiler compiler(prog, src, file);
        compiler.compileMain();  // checks the program and finds every file it uses
    } catch (const PlainError& e) {
        report(e, file, src, &prog);
        return 1;
    }
    std::string self = selfPath(argv0);
    if (!readFile(self, exe)) { fprintf(stderr, "I couldn't read my own program file (%s).\n", self.c_str()); return 2; }
    std::vector<std::pair<std::string, std::string>> old;
    size_t start = 0;
    if (readPayload(exe, old, &start)) exe.resize(start);
    if (out.empty()) {
        size_t slash = file.find_last_of("/\\"), dot = file.find_last_of('.');
        out = file.substr(0, dot != std::string::npos && (slash == std::string::npos || dot > slash) ? dot : file.size());
#ifdef _WIN32
        out += ".exe";
#endif
        if (out == file) out += ".app";
    }
    std::string payload;
    std::vector<std::pair<std::string, std::string>> files = {{file, src}};
    files.insert(files.end(), prog.sources.begin(), prog.sources.end());
    std::string resolvedText;
    for (const auto& r : prog.resolved) {
        size_t nl = r.first.find('\n');
        resolvedText += r.first.substr(0, nl) + "\t" + r.first.substr(nl + 1) + "\t" + r.second + "\n";
    }
    files.emplace_back("\x01resolved", resolvedText);
    for (const auto& f : files) {
        putU32(payload, (uint32_t)f.first.size());
        payload += f.first;
        putU32(payload, (uint32_t)f.second.size());
        payload += f.second;
    }
    uint64_t size = payload.size();
    putU32(payload, (uint32_t)files.size());
    payload.append(reinterpret_cast<const char*>(&size), 8);
    payload.append(MAGIC, 8);
    FILE* f = fopen(out.c_str(), "wb");
    if (!f) { fprintf(stderr, "I couldn't write to '%s'.\n", out.c_str()); return 2; }
    fwrite(exe.data(), 1, exe.size(), f);
    fwrite(payload.data(), 1, payload.size(), f);
    fclose(f);
#ifndef _WIN32
    chmod(out.c_str(), 0755);
#endif
    printf("Built %s (%zu file%s inside). Run it with: %s%s\n", out.c_str(), files.size() - 1, files.size() == 2 ? "" : "s",
           out.find('/') == std::string::npos ? "./" : "", out.c_str());
    return 0;
}

static int repl() {
    Program prog;
    setUp(prog);
    VM vm(prog);
    printf("Plain %s - type a line and press Enter. Type 'exit' to leave.\n", VERSION);
    std::string buffer, line;
    for (;;) {
        fputs(buffer.empty() ? "plain> " : "  ...> ", stdout);
        fflush(stdout);
        if (!std::getline(std::cin, line)) { printf("\n"); break; }
        if (buffer.empty() && (line == "exit" || line == "quit")) break;
        buffer += line + "\n";
        try {
            Compiler compiler(prog, buffer, "", true);
            Value mainFn = compiler.compileMain();
            buffer.clear();
            vm.run(mainFn);
        } catch (const PlainError& e) {
            if (e.incomplete && !line.empty()) continue;  // the block is still open: keep reading
            buffer.clear();
            fflush(stdout);
            fprintf(stderr, "Oops! %s\n", e.msg.c_str());
        }
        fflush(stdout);
    }
    return 0;
}

static void usage() {
    printf("Plain %s - a programming language that reads like English.\n\n"
           "Usage:\n"
           "  plain                         start an interactive session\n"
           "  plain program.plain [args]    run a program\n"
           "  plain check program.plain     look for mistakes without running\n"
           "  plain build program.plain [-o name]\n"
           "                                make a standalone program that runs without Plain installed\n"
           "  plain --explain program.plain show the tokens and bytecode, then run\n"
           "  plain -e \"say 1 + 2\"          run one line of code\n"
           "  plain init                    start a project (writes plain.json)\n"
           "  plain install [address]       add a package: folder, git address or user/repo[#version]\n"
           "                                (no address: install what plain.json lists)\n"
           "  plain update [name]           get newer versions, ignoring plain.lock\n"
           "  plain remove <name>           remove a package\n"
           "  plain list                    list installed packages\n"
           "  plain --version | --help\n",
           VERSION);
}

int main(int argc, char** argv) {
    static char outBuf[1 << 16];
    setvbuf(stdout, outBuf, PLAIN_ISATTY(1) ? _IOLBF : _IOFBF, sizeof outBuf);
#ifndef _WIN32
    signal(SIGPIPE, SIG_IGN);  // a closed network connection is an error to report, not a reason to die
#endif
    gil().lock();  // the main program holds the turn; background tasks take it when it waits
    try {
        // Am I a program made by "plain build"? Then run what is attached to me.
        std::string exe;
        std::vector<std::pair<std::string, std::string>> files;
        if (readFile(selfPath(argv[0]), exe) && readPayload(exe, files) && !files.empty()) {
            exe.clear();
            std::vector<std::string> args(argv + 1, argv + argc);
            return finish(runProgram(files[0].second, files[0].first, args, false, false, &files));
        }
        exe.clear();

        std::vector<std::string> args(argv + 1, argv + argc);
        if (args.empty()) return finish(repl());
        const std::string& cmd = args[0];
        if (cmd == "--help" || cmd == "-h" || cmd == "help") { usage(); return 0; }
        if (cmd == "--version" || cmd == "-v" || cmd == "version") { printf("Plain %s\n", VERSION); return 0; }
        if (cmd == "-e") {
            if (args.size() < 2) { usage(); return 2; }
            return finish(runProgram(args[1] + "\n", "", {args.begin() + 2, args.end()}, false, false));
        }
        {
            int r = packageCommand(args);
            if (r >= 0) return r;
        }
        if (cmd == "build") {
            std::string file, out;
            for (size_t i = 1; i < args.size(); ++i) {
                if (args[i] == "-o" && i + 1 < args.size()) out = args[++i];
                else file = args[i];
            }
            if (file.empty()) { usage(); return 2; }
            return build(argv[0], file, out);
        }
        bool explain = false, check = false;
        size_t at = 0;
        if (cmd == "--explain") { explain = true; at = 1; }
        else if (cmd == "check") { check = true; at = 1; }
        else if (cmd == "run") { at = 1; }
        if (at >= args.size()) { usage(); return 2; }
        std::string src;
        if (!readFile(args[at], src)) {
            fprintf(stderr, "I couldn't open the file '%s'.\n", args[at].c_str());
            return 2;
        }
        return finish(runProgram(src, args[at], {args.begin() + (long)at + 1, args.end()}, explain, check));
    } catch (const std::exception& e) {
        fflush(stdout);
        fprintf(stderr, "\nOops! Plain itself ran into a problem: %s\n", e.what());
        return 3;
    }
}
