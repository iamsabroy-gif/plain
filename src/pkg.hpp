// Plain - the package manager.
//
// A project describes itself in plain.json:
//   { "name": "shop", "version": "1.0.0", "main": "main.plain",
//     "dependencies": { "greeter": "someone/plain-greeter#v1.2.0", "tools": "../tools" } }
// 'plain install' puts every dependency (and what they depend on) into ./plain_modules,
// and writes plain.lock so the next install gets exactly the same code.
// In a program:  use "greeter"
#pragma once
#ifndef PLAIN_WASM
#include <filesystem>
#endif

#include "builtins.hpp"

namespace plain {
#ifndef PLAIN_WASM
namespace pkgfs = std::filesystem;
#endif

#ifdef PLAIN_POSIX

struct Spec {
    bool local = false;
    std::string where;  // a git address or a folder
    std::string ref;    // branch, tag or commit for git
};

inline bool validName(const std::string& n) {
    if (n.empty() || n.size() > 100 || n[0] == '.' || n[0] == '-') return false;
    for (char c : n)
        if (!(isalnum((unsigned char)c) || c == '_' || c == '-' || c == '.')) return false;
    return n.find("..") == std::string::npos;
}

inline bool looksLocal(const std::string& s) {
    return s.compare(0, 2, "./") == 0 || s.compare(0, 3, "../") == 0 || s[0] == '/' || (s.compare(0, 5, "file:") == 0 && s.compare(0, 7, "file://") != 0) || s == "." || s == "..";
}

inline std::string registryLookup(const std::string& name);

inline Spec parseSpec(const std::string& text) {
    Spec s;
    std::string t = text;
    if (t.empty()) fail("A package address can't be empty.");
    if (t[0] == '-') fail("'" + t + "' isn't a package address.");
    if (looksLocal(t)) {
        s.local = true;
        s.where = t.compare(0, 5, "file:") == 0 ? t.substr(5) : t;
        return s;
    }
    size_t hash = t.find('#');
    if (hash != std::string::npos) {
        s.ref = t.substr(hash + 1);
        t.resize(hash);
        if (s.ref.empty() || s.ref[0] == '-') fail("'" + s.ref + "' isn't a valid version after the '#'.");
    }
    if (t.find("ext::") != std::string::npos) fail("That kind of address isn't allowed.");
    if (t.find("://") == std::string::npos && t.compare(0, 4, "git@") != 0) {
        if (t.compare(0, 11, "github.com/") == 0) t = "https://" + t;
        else if (std::count(t.begin(), t.end(), '/') == 1) t = "https://github.com/" + t;
        else {
            std::string found = registryLookup(t);
            if (found.empty()) fail("I don't know a package called '" + t + "'. Look for one with: plain search " + t + "  (or give a folder, a git address or user/repo).");
            Spec r = parseSpec(found);
            if (s.ref.empty()) s.ref = r.ref;
            return r.ref.empty() ? Spec{r.local, r.where, s.ref} : r;
        }
    }
    s.where = t;
    return s;
}

inline std::string specText(const Spec& s) { return s.local ? s.where : s.where + (s.ref.empty() ? "" : "#" + s.ref); }

// ------------------------------------------------------------ versions
// A version is "1.2.3" (a leading "v" is fine). A range picks the newest tagged version
// that fits: "^1.2" (1.2 or newer, below 2), "~1.2.3" (below 1.3), "1.x", "*",
// ">=1.0 <2.0" (both must hold), "^1 || ^2" (either).
struct Ver {
    long n[3] = {0, 0, 0};
    int parts = 0;     // how many numbers were written ("1.2" has 2)
    bool ok = false;
};
inline Ver parseVer(std::string s, bool allowWild = false) {
    Ver v;
    if (!s.empty() && (s[0] == 'v' || s[0] == 'V')) s.erase(0, 1);
    size_t i = 0;
    while (v.parts < 3) {
        if (i < s.size() && allowWild && (s[i] == 'x' || s[i] == 'X' || s[i] == '*')) { ++i; break; }
        if (i >= s.size() || !isdigit((unsigned char)s[i])) return v;
        long x = 0;
        while (i < s.size() && isdigit((unsigned char)s[i])) x = x * 10 + (s[i++] - '0');
        v.n[v.parts++] = x;
        if (i < s.size() && s[i] == '.') ++i;
        else break;
    }
    v.ok = i == s.size();  // anything left over (like "-beta") is not a plain release
    return v;
}
inline int cmpVer(const Ver& a, const Ver& b) {
    for (int k = 0; k < 3; ++k)
        if (a.n[k] != b.n[k]) return a.n[k] < b.n[k] ? -1 : 1;
    return 0;
}
inline bool isRange(const std::string& r) {
    if (r.empty()) return false;
    if (strchr("^~<>=*", r[0]) || r.find("||") != std::string::npos || r.find(' ') != std::string::npos) return true;
    return isdigit((unsigned char)r[0]) && parseVer(r, true).ok;  // "1.2", "1.x" (but not "v1.2.0" or "main")
}
// Does version v fit one comparator like "^1.2", ">=2", "1.x" or "1.2.3"?
inline bool fitsOne(const Ver& v, std::string c) {
    std::string op;
    while (!c.empty() && strchr("^~<>=", c[0])) { op += c[0]; c.erase(0, 1); }
    if (c.empty() || c == "*" || c == "x") return op.empty() || op == "=" || op == ">=";
    Ver b = parseVer(c, true);
    if (!b.ok && b.parts == 0) fail("'" + op + c + "' isn't a version I understand. Try something like ^1.2 or >=1.0 <2.0.");
    int k = cmpVer(v, b);
    if (op == ">") return k > 0;
    if (op == ">=") return k >= 0;
    if (op == "<") return k < 0;
    if (op == "<=") return k <= 0;
    // Upper bound for ^, ~ and partial versions like "1.2" (which means 1.2.anything).
    Ver hi = b;
    int bump;
    if (op == "^") {
        bump = 0;
        while (bump < b.parts - 1 && b.n[bump] == 0) ++bump;  // ^0.2 stays below 0.3
    } else if (op == "~") {
        bump = b.parts > 1 ? 1 : 0;
    } else {
        if (b.parts == 3) return k == 0;  // an exact version
        bump = b.parts - 1;
    }
    hi.n[bump] += 1;
    for (int j = bump + 1; j < 3; ++j) hi.n[j] = 0;
    return k >= 0 && cmpVer(v, hi) < 0;
}
inline bool fitsRange(const Ver& v, const std::string& range) {
    size_t start = 0;
    for (;;) {  // alternatives split by "||"; inside one, every comparator must hold
        size_t bar = range.find("||", start);
        std::string alt = range.substr(start, bar == std::string::npos ? std::string::npos : bar - start);
        bool all = true, any = false;
        std::string word;
        std::vector<std::string> words;
        for (char ch : alt + " ") {
            if (ch == ' ') { if (!word.empty()) words.push_back(word); word.clear(); }
            else word += ch;
        }
        // ">= 1.0" written with a space: join the operator to its version
        for (size_t i = 0; i + 1 < words.size(); ++i)
            if (strspn(words[i].c_str(), "^~<>=") == words[i].size()) { words[i] += words[i + 1]; words.erase(words.begin() + (long)i + 1); }
        for (const std::string& w : words) { any = true; if (!fitsOne(v, w)) { all = false; break; } }
        if (any && all) return true;
        if (bar == std::string::npos) return false;
        start = bar + 2;
    }
}
// The newest tag of a git repository that fits the range, like "v1.4.2".
inline std::string resolveRange(const std::string& where, const std::string& range) {
    std::string out, err;
    int code = runProcess({"git", "-c", "protocol.ext.allow=never", "ls-remote", "--tags", "--refs", "--", where}, "", out, err);
    if (code == 127) fail("Installing from a git address needs the 'git' program, and I couldn't find it.");
    if (code != 0) fail("I couldn't look up the versions of '" + where + "':\n" + err);
    std::string best;
    Ver bestV;
    size_t i = 0;
    while (i < out.size()) {
        size_t nl = out.find('\n', i);
        std::string line = out.substr(i, nl == std::string::npos ? std::string::npos : nl - i);
        i = nl == std::string::npos ? out.size() : nl + 1;
        size_t at = line.find("refs/tags/");
        if (at == std::string::npos) continue;
        std::string tag = line.substr(at + 10);
        Ver v = parseVer(tag);
        if (!v.ok || !fitsRange(v, range)) continue;
        if (best.empty() || cmpVer(v, bestV) > 0) { best = tag; bestV = v; }
    }
    if (best.empty()) fail("'" + where + "' has no tagged version that fits '" + range + "'.");
    return best;
}

// ------------------------------------------------------------ registry
// The registry is a JSON map of package name -> address (or {"spec": address, "description": ...}).
// Plain looks in the file named by PLAIN_REGISTRY (a path or an http/https address), or
// ~/.plain/registry.json if there is one, and then in the shared index everyone can add to.
inline const char* sharedRegistry() {
    const char* over = getenv("PLAIN_SHARED_REGISTRY");  // tests and mirrors; "off" turns it off
    return over ? over : "https://raw.githubusercontent.com/iamsabroy-gif/plain/main/registry/index.json";
}
inline Value loadRegistry(const std::string& where) {
    std::string text;
    if (where.empty() || where == "off") return Value();
    if (where.compare(0, 7, "http://") == 0 || where.compare(0, 8, "https://") == 0) {
        std::string err;
        if (runProcess({"curl", "-sSfL", "--max-time", "30", "--", where}, "", text, err) != 0) return Value();
    } else if (!readFile(where, text)) {
        return Value();
    }
    try {
        Value v = jsonParse(text);
        return isMap(v) ? v : Value();
    } catch (PlainError&) {
        return Value();
    }
}
inline std::vector<std::string> registryPlaces() {
    std::vector<std::string> places;
    if (getenv("PLAIN_REGISTRY")) places.push_back(getenv("PLAIN_REGISTRY"));
    else places.push_back(plainHome() + "/registry.json");
    places.push_back(sharedRegistry());
    return places;
}
inline std::string entrySpec(const Value& e) {
    if (isStr(e)) return asStr(e);
    if (isMap(e)) {
        Value* sp = asMap(e)->find(mkstr("spec"));
        if (sp && isStr(*sp)) return asStr(*sp);
    }
    return "";
}
inline std::string registryLookup(const std::string& name) {
    for (const std::string& where : registryPlaces()) {
        Value reg = loadRegistry(where);
        if (!isMap(reg)) continue;
        Value* e = asMap(reg)->find(mkstr(name));
        if (e && !entrySpec(*e).empty()) return entrySpec(*e);
    }
    return "";
}

// plain search [words]: the packages in the registries whose name or description mentions the words.
inline int pkgSearch(const std::vector<std::string>& args) {
    std::string words;
    for (size_t i = 1; i < args.size(); ++i) words += (words.empty() ? "" : " ") + args[i];
    std::string low = words;
    for (char& c : low) c = (char)tolower((unsigned char)c);
    int found = 0;
    std::unordered_set<std::string> seen;
    for (const std::string& where : registryPlaces()) {
        Value reg = loadRegistry(where);
        if (!isMap(reg)) continue;
        for (const auto& e : asMap(reg)->entries) {
            std::string name = fmt(e.first);
            if (!seen.insert(name).second) continue;
            std::string desc;
            if (isMap(e.second)) {
                Value* d = asMap(e.second)->find(mkstr("description"));
                if (d && isStr(*d)) desc = asStr(*d);
            }
            std::string hay = name + " " + desc;
            for (char& c : hay) c = (char)tolower((unsigned char)c);
            if (!low.empty() && hay.find(low) == std::string::npos) continue;
            printf("%-20s %s\n", name.c_str(), desc.empty() ? entrySpec(e.second).c_str() : desc.c_str());
            ++found;
        }
    }
    if (found == 0) printf("No packages found%s. Anyone can add one: see registry/README.md in the Plain repository.\n",
                           words.empty() ? "" : (" for '" + words + "'").c_str());
    return 0;
}

inline Value readJsonFile(const std::string& path, bool& exists) {
    std::string text;
    exists = readFile(path, text);
    if (!exists) return Value::obj(new Map);
    try {
        Value v = jsonParse(text);
        if (!isMap(v)) fail(path + " must contain a JSON object.");
        return v;
    } catch (PlainError& e) {
        fail("I couldn't read " + path + ": " + e.msg);
    }
}
inline void writeJsonFile(const std::string& path, const Value& v) {
    std::string out;
    toJson(v, out, 0, 2, 0);
    out += "\n";
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) fail("I couldn't write " + path + ".");
    fwrite(out.data(), 1, out.size(), f);
    fclose(f);
}
inline Map* subMap(Map* m, const char* key) {
    Value* v = m->find(mkstr(key));
    if (v && isMap(*v)) return asMap(*v);
    Value nm = Value::obj(new Map);
    m->set(mkstr(key), nm);
    return asMap(*m->find(mkstr(key)));
}

struct Installer {
    std::string root;  // where packages go
    Value lock;        // the lock file as it was
    Value newLock = Value::obj(new Map);
    bool useLock = true;
    std::unordered_map<std::string, std::string> done;  // name -> spec installed in this run
    int installed = 0;

    // Install one package; returns the name it was installed under.
    std::string install(const std::string& specStr, std::string name, bool top) {
        Spec spec = parseSpec(specStr);
        std::string pinned;
        if (useLock && !name.empty()) {
            Value* e = asMap(lock)->find(mkstr(name));
            if (e && isMap(*e)) {
                Value* sp = asMap(*e)->find(mkstr("spec"));
                Value* cm = asMap(*e)->find(mkstr("commit"));
                if (sp && isStr(*sp) && asStr(*sp) == specText(spec) && cm && isStr(*cm)) pinned = asStr(*cm);
            }
        }
        pkgfs::path tmp = pkgfs::path(root) / (".installing-" + std::to_string((long)getpid()));
        std::error_code ec;
        pkgfs::remove_all(tmp, ec);
        pkgfs::create_directories(root, ec);
        std::string commit = "local";
        std::string chosenTag;  // the version a range picked
        if (spec.local) {
            pkgfs::path src = pkgfs::absolute(spec.where, ec).lexically_normal();
            if (!pkgfs::is_directory(src, ec)) fail("'" + spec.where + "' isn't a folder I can install from.");
            pkgfs::create_directories(tmp, ec);
            for (const auto& e : pkgfs::directory_iterator(src, ec)) {
                std::string fname = e.path().filename().string();
                if (fname == "plain_modules" || fname == ".git" || fname == "plain.lock") continue;
                pkgfs::copy(e.path(), tmp / fname, pkgfs::copy_options::recursive | pkgfs::copy_options::copy_symlinks, ec);
                if (ec) fail("I couldn't copy " + e.path().string() + ": " + ec.message());
            }
            if (name.empty()) name = src.filename().string();
        } else {
            std::vector<std::string> argv = {"git", "-c", "protocol.ext.allow=never", "clone", "--quiet"};
            std::string ref = pinned.empty() ? spec.ref : "";
            if (!ref.empty() && isRange(ref)) {
                ref = resolveRange(spec.where, ref);
                chosenTag = ref;
            }
            if (pinned.empty()) {
                argv.push_back("--depth");
                argv.push_back("1");
                if (!ref.empty()) { argv.push_back("--branch"); argv.push_back(ref); }
            }
            argv.push_back("--");
            argv.push_back(spec.where);
            argv.push_back(tmp.string());
            std::string out, err;
            int code = runProcess(argv, "", out, err);
            if (code == 127) fail("Installing from a git address needs the 'git' program, and I couldn't find it.");
            if (code != 0) {
                pkgfs::remove_all(tmp, ec);
                fail("I couldn't download '" + spec.where + "':\n" + err);
            }
            if (!pinned.empty()) {
                code = runProcess({"git", "-C", tmp.string(), "checkout", "--quiet", pinned}, "", out, err);
                if (code != 0) {
                    pkgfs::remove_all(tmp, ec);
                    fail("The saved version " + pinned + " of '" + spec.where + "' isn't available any more:\n" + err);
                }
            }
            out.clear();
            runProcess({"git", "-C", tmp.string(), "rev-parse", "HEAD"}, "", out, err);
            while (!out.empty() && isspace((unsigned char)out.back())) out.pop_back();
            if (!out.empty()) commit = out;
            pkgfs::remove_all(tmp / ".git", ec);
            if (name.empty()) {
                std::string base = spec.where;
                while (!base.empty() && base.back() == '/') base.pop_back();
                name = base.substr(base.find_last_of("/:") + 1);
                if (name.size() > 4 && name.compare(name.size() - 4, 4, ".git") == 0) name.resize(name.size() - 4);
            }
        }
        // the package may name itself
        bool hasManifest;
        Value manifest = readJsonFile((tmp / "plain.json").string(), hasManifest);
        if (hasManifest && !top) {
            // dependencies keep the name they were asked for
        } else if (hasManifest) {
            Value* nm = asMap(manifest)->find(mkstr("name"));
            if (nm && isStr(*nm) && validName(asStr(*nm)) && specStr.find("--as") == std::string::npos && name.empty()) name = asStr(*nm);
        }
        if (!validName(name)) {
            pkgfs::remove_all(tmp, ec);
            fail("'" + name + "' isn't a usable package name. Use letters, digits, - and _ (add --as name to choose one).");
        }
        auto prior = done.find(name);
        if (prior != done.end()) {
            pkgfs::remove_all(tmp, ec);
            if (prior->second != specText(spec))
                fprintf(stderr, "Warning: '%s' is needed from two different places (%s and %s); keeping the first.\n", name.c_str(), prior->second.c_str(), specText(spec).c_str());
            return name;
        }
        pkgfs::path dest = pkgfs::path(root) / name;
        pkgfs::remove_all(dest, ec);
        pkgfs::rename(tmp, dest, ec);
        if (ec) {
            pkgfs::remove_all(tmp, ec);
            fail("I couldn't put the package into " + dest.string() + ": " + ec.message());
        }
        done[name] = specText(spec);
        ++installed;
        Value entry = Value::obj(new Map);
        asMap(entry)->set(mkstr("spec"), mkstr(specText(spec)));
        asMap(entry)->set(mkstr("commit"), mkstr(commit));
        if (!chosenTag.empty()) asMap(entry)->set(mkstr("version"), mkstr(chosenTag));
        asMap(newLock)->set(mkstr(name), entry);
        printf("Installed %s (%s%s)\n", name.c_str(), specText(spec).c_str(), chosenTag.empty() ? "" : (" -> " + chosenTag).c_str());
        // packages it needs
        Value deps = hasManifest ? (asMap(manifest)->find(mkstr("dependencies")) ? *asMap(manifest)->find(mkstr("dependencies")) : Value()) : Value();
        if (isMap(deps))
            for (const auto& e : asMap(deps)->entries) {
                if (!isStr(e.second)) continue;
                std::string depName = fmt(e.first);
                if (!validName(depName)) fail("The package '" + name + "' asks for '" + depName + "', which isn't a usable name.");
                if (done.count(depName) || pkgfs::exists(pkgfs::path(root) / depName)) {
                    if (!done.count(depName)) done[depName] = asStr(e.second);
                    continue;
                }
                // a dependency's local folder is relative to the package that asks for it
                std::string depSpec = asStr(e.second);
                if (looksLocal(depSpec) && !spec.local) fail("The package '" + name + "' wants the local folder '" + depSpec + "', which only works inside a project.");
                install(depSpec, depName, false);
            }
        return name;
    }
};

inline int pkgInit(const std::vector<std::string>& args) {
    if (pkgfs::exists("plain.json")) {
        fprintf(stderr, "plain.json already exists here.\n");
        return 1;
    }
    std::error_code ec;
    std::string name = args.size() > 1 ? args[1] : pkgfs::current_path(ec).filename().string();
    if (!validName(name)) name = "my-project";
    Value m = Value::obj(new Map);
    asMap(m)->set(mkstr("name"), mkstr(name));
    asMap(m)->set(mkstr("version"), mkstr("0.1.0"));
    asMap(m)->set(mkstr("main"), mkstr("main.plain"));
    asMap(m)->set(mkstr("dependencies"), Value::obj(new Map));
    writeJsonFile("plain.json", m);
    printf("Created plain.json for '%s'.\n", name.c_str());
    return 0;
}

inline int pkgInstall(const std::vector<std::string>& args, bool update) {
    std::string spec, name;
    bool global = false;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--as" && i + 1 < args.size()) name = args[++i];
        else if (args[i] == "--global" || args[i] == "-g") global = true;
        else if (spec.empty()) spec = args[i];
        else fail("I didn't expect '" + args[i] + "' here.");
    }
    Installer in;
    in.root = global ? plainHome() + "/modules" : "plain_modules";
    if (global && plainHome().empty()) fail("I couldn't work out where your home folder is.");
    bool hasLock = false, hasManifest = false;
    std::string lockPath = global ? plainHome() + "/plain.lock" : "plain.lock";
    in.lock = readJsonFile(lockPath, hasLock);
    in.useLock = !update;
    Value manifest = readJsonFile("plain.json", hasManifest);

    if (spec.empty() || (update && !spec.empty() && !looksLocal(spec) && spec.find('/') == std::string::npos && hasManifest)) {
        // install what plain.json lists (update NAME: only that one)
        if (!hasManifest) fail("There is no plain.json here. Run 'plain init' to make one, or give an address: plain install user/repo");
        Value* deps = asMap(manifest)->find(mkstr("dependencies"));
        std::string only = update ? spec : "";
        int count = 0;
        if (deps && isMap(*deps))
            for (const auto& e : asMap(*deps)->entries) {
                std::string dn = fmt(e.first);
                if (!only.empty() && dn != only) continue;
                if (!isStr(e.second)) fail("The dependency '" + dn + "' in plain.json must be given as text, like \"user/repo\".");
                if (!validName(dn)) fail("'" + dn + "' in plain.json isn't a usable package name.");
                in.install(asStr(e.second), dn, true);
                ++count;
            }
        if (count == 0) printf("plain.json lists no dependencies%s.\n", only.empty() ? "" : (" called " + only).c_str());
    } else {
        std::string got = in.install(spec, name, true);
        if (!global) {
            if (!hasManifest) {
                asMap(manifest)->set(mkstr("name"), mkstr("my-project"));
                asMap(manifest)->set(mkstr("version"), mkstr("0.1.0"));
            }
            Map* deps = subMap(asMap(manifest), "dependencies");
            deps->set(mkstr(got), mkstr(in.done[got]));
            writeJsonFile("plain.json", manifest);
        }
    }
    // keep older lock entries that this run didn't touch
    for (const auto& e : asMap(in.lock)->entries)
        if (!asMap(in.newLock)->find(e.first) && pkgfs::exists(pkgfs::path(in.root) / fmt(e.first))) asMap(in.newLock)->set(e.first, e.second);
    if (in.installed > 0 || hasLock) writeJsonFile(lockPath, in.newLock);
    printf("%d package%s installed.\n", in.installed, in.installed == 1 ? "" : "s");
    return 0;
}

inline int pkgRemove(const std::vector<std::string>& args) {
    bool global = false;
    std::string name;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--global" || args[i] == "-g") global = true;
        else name = args[i];
    }
    if (!validName(name)) {
        fprintf(stderr, "Usage: plain remove <package name> [--global]\n");
        return 2;
    }
    std::string root = global ? plainHome() + "/modules" : "plain_modules";
    std::error_code ec;
    if (!pkgfs::is_directory(pkgfs::path(root) / name, ec)) {
        fprintf(stderr, "There is no installed package called '%s'.\n", name.c_str());
        return 1;
    }
    pkgfs::remove_all(pkgfs::path(root) / name, ec);
    if (!global) {
        bool has;
        Value manifest = readJsonFile("plain.json", has);
        if (has) {
            Value* deps = asMap(manifest)->find(mkstr("dependencies"));
            if (deps && isMap(*deps) && asMap(*deps)->remove(mkstr(name))) writeJsonFile("plain.json", manifest);
        }
        Value lock = readJsonFile("plain.lock", has);
        if (has && asMap(lock)->remove(mkstr(name))) writeJsonFile("plain.lock", lock);
    }
    printf("Removed %s\n", name.c_str());
    return 0;
}

inline int pkgList(const std::vector<std::string>& args) {
    bool global = args.size() > 1 && (args[1] == "--global" || args[1] == "-g");
    std::string root = global ? plainHome() + "/modules" : "plain_modules";
    std::vector<std::string> names;
    std::error_code ec;
    if (pkgfs::is_directory(root, ec))
        for (const auto& e : pkgfs::directory_iterator(root, ec))
            if (e.is_directory() && e.path().filename().string()[0] != '.') names.push_back(e.path().filename().string());
    std::sort(names.begin(), names.end());
    if (names.empty()) printf("No packages installed here yet. Add one with: plain install <folder, git address or user/repo>\n");
    bool has;
    Value lock = readJsonFile(global ? plainHome() + "/plain.lock" : "plain.lock", has);
    for (const std::string& n : names) {
        std::string version;
        bool hm;
        Value m = readJsonFile((pkgfs::path(root) / n / "plain.json").string(), hm);
        if (hm) {
            Value* v = asMap(m)->find(mkstr("version"));
            if (v) version = " " + fmt(*v);
        }
        std::string from;
        Value* e = asMap(lock)->find(mkstr(n));
        if (e && isMap(*e) && asMap(*e)->find(mkstr("spec"))) from = "  <- " + fmt(*asMap(*e)->find(mkstr("spec")));
        printf("%s%s%s\n", n.c_str(), version.c_str(), from.c_str());
    }
    return 0;
}

// Returns -1 when the command isn't a package command.
inline int packageCommand(const std::vector<std::string>& args) {
    const std::string& cmd = args[0];
    try {
        if (cmd == "init") return pkgInit(args);
        if (cmd == "install" || cmd == "add") return pkgInstall(args, false);
        if (cmd == "update") return pkgInstall(args, true);
        if (cmd == "remove" || cmd == "uninstall") return pkgRemove(args);
        if (cmd == "list" || cmd == "packages") return pkgList(args);
        if (cmd == "search") return pkgSearch(args);
    } catch (const PlainError& e) {
        fflush(stdout);
        fprintf(stderr, "Oops! %s\n", e.msg.c_str());
        return 1;
    }
    return -1;
}

#else
// Packages need git and a POSIX shell-free process launcher, which the Windows build doesn't have yet.
inline int packageCommand(const std::vector<std::string>& args) {
    const std::string& c = args[0];
    if (c == "init" || c == "install" || c == "add" || c == "update" || c == "remove" || c == "uninstall" || c == "list" || c == "packages" || c == "search") {
        fprintf(stderr, "The package manager is not available in this build of Plain (the Windows build and the web playground).\n");
        return 2;
    }
    return -1;
}
#endif

}  // namespace plain
