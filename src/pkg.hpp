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
            if (found.empty()) fail("I don't know a package called '" + t + "'. Give a folder, a git address or user/repo, or add it to your registry file.");
            Spec r = parseSpec(found);
            if (s.ref.empty()) s.ref = r.ref;
            return r.ref.empty() ? Spec{r.local, r.where, s.ref} : r;
        }
    }
    s.where = t;
    return s;
}

inline std::string specText(const Spec& s) { return s.local ? s.where : s.where + (s.ref.empty() ? "" : "#" + s.ref); }

// The registry is a JSON map of package name -> address (or {"spec": address}).
// It is the file named by PLAIN_REGISTRY (a path or an http/https address), or ~/.plain/registry.json.
inline std::string registryLookup(const std::string& name) {
    std::string where = getenv("PLAIN_REGISTRY") ? getenv("PLAIN_REGISTRY") : plainHome() + "/registry.json";
    std::string text;
    if (where.compare(0, 7, "http://") == 0 || where.compare(0, 8, "https://") == 0) {
        std::string err;
        if (runProcess({"curl", "-sSfL", "--max-time", "30", "--", where}, "", text, err) != 0) return "";
    } else if (!readFile(where, text)) {
        return "";
    }
    try {
        Value v = jsonParse(text);
        if (!isMap(v)) return "";
        Value* e = asMap(v)->find(mkstr(name));
        if (!e) return "";
        if (isStr(*e)) return asStr(*e);
        if (isMap(*e)) {
            Value* sp = asMap(*e)->find(mkstr("spec"));
            if (sp && isStr(*sp)) return asStr(*sp);
        }
    } catch (PlainError&) {
    }
    return "";
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
        asMap(newLock)->set(mkstr(name), entry);
        printf("Installed %s (%s)\n", name.c_str(), specText(spec).c_str());
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
    if (c == "init" || c == "install" || c == "add" || c == "update" || c == "remove" || c == "uninstall" || c == "list" || c == "packages") {
        fprintf(stderr, "The package manager is not available in this build of Plain (the Windows build and the web playground).\n");
        return 2;
    }
    return -1;
}
#endif

}  // namespace plain
