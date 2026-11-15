// Plain - finding the file that 'use "name"' refers to (a file next to the
// program, or an installed package).
#pragma once
#include <filesystem>
#include <unordered_map>

#include "json.hpp"
#include "libfiles.hpp"

namespace plain {

// The built-in library (stack, queue, graph, ...) lives inside the plain command; its files have paths like "<lib>/stack.plain".
inline const char* libSource(const std::string& path) {
    static const std::string prefix = "<lib>/";
    if (path.compare(0, prefix.size(), prefix) != 0) return nullptr;
    std::string name = path.substr(prefix.size());
    if (name.size() > 6 && name.compare(name.size() - 6, 6, ".plain") == 0) name.resize(name.size() - 6);
    for (const LibFile* f = LIB_FILES; f->name; ++f)
        if (name == f->name) return f->text;
    return nullptr;
}

// A packed file by its name, such as "viz/player.html" or "problems/two-sum" (null if there is none).
inline const char* packedFile(const std::string& name) {
    for (const LibFile* f = LIB_FILES; f->name; ++f)
        if (name == f->name) return f->text;
    return nullptr;
}

inline std::string plainHome() {
    const char* h = getenv("PLAIN_HOME");
    if (h && *h) return h;
    const char* home = getenv("HOME");
    if (!home) home = getenv("USERPROFILE");
    return home ? std::string(home) + "/.plain" : "";
}

inline std::string dirOf(const std::string& file) {
    size_t slash = file.find_last_of("/\\");
    return slash == std::string::npos ? "" : file.substr(0, slash + 1);
}

inline bool fileExists(const std::string& path) {
    std::error_code ec;
    return std::filesystem::is_regular_file(path, ec);
}

inline std::string withExtension(const std::string& name) {
    size_t slash = name.find_last_of("/\\");
    size_t dot = name.find_last_of('.');
    bool hasExt = dot != std::string::npos && (slash == std::string::npos || dot > slash);
    return hasExt ? name : name + ".plain";
}

// The 'main' file named in a package's plain.json (empty if none).
inline std::string manifestMain(const std::string& dir) {
    std::string text;
    if (!readFile(dir + "plain.json", text)) return "";
    try {
        Value v = jsonParse(text);
        if (isMap(v)) {
            Value* m = asMap(v)->find(mkstr("main"));
            if (m && isStr(*m)) return asStr(*m);
        }
    } catch (PlainError&) {
    }
    return "";
}

// Returns the path of the module, or "" when nothing matches. 'embedded' is
// set for programs made by 'plain build', which carry their files with them.
inline std::string resolveModule(const std::string& importer, const std::string& name,
                                 const std::unordered_map<std::string, std::string>* embedded) {
    auto exists = [&](const std::string& p) { return libSource(p) || (embedded ? embedded->count(p) > 0 : fileExists(p)); };
    std::string dir = dirOf(importer);
    std::string direct = dir + withExtension(name);
    if (exists(direct)) return direct;
    if (name.empty() || name[0] == '.' || name[0] == '/' || name[0] == '\\') return "";

    size_t slash = name.find_first_of("/\\");
    std::string pkg = name.substr(0, slash);
    std::string rest = slash == std::string::npos ? "" : name.substr(slash + 1);

    std::vector<std::string> roots;
    std::string up = dir;
    for (int level = 0; level < 12; ++level) {
        roots.push_back(up + "plain_modules/");
        up += "../";
    }
    if (!embedded) {
        std::string home = plainHome();
        if (!home.empty()) roots.push_back(home + "/modules/");
    }
    for (const std::string& root : roots) {
        std::string base = root + pkg + "/";
        if (!rest.empty()) {
            std::string p = base + withExtension(rest);
            if (exists(p)) return p;
            continue;
        }
        std::vector<std::string> entries;
        if (!embedded) {
            std::string m = manifestMain(base);
            if (!m.empty()) entries.push_back(base + withExtension(m));
        }
        entries.push_back(base + "main.plain");
        entries.push_back(base + pkg + ".plain");
        entries.push_back(base + "index.plain");
        for (const std::string& p : entries)
            if (exists(p)) return p;
    }
    if (rest.empty() && libSource("<lib>/" + pkg + ".plain")) return "<lib>/" + pkg + ".plain";  // the built-in library
    return "";
}

}  // namespace plain
