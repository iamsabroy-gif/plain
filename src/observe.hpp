// Plain - watching a run: operation counts and step-by-step traces.
//
// The VM's main loop is compiled twice (see VM::executeT). In the normal copy
// there is no trace of any of this; in the watched copy it calls the hooks
// below. So a normal run pays nothing, and "plain count" / "plain visualize" /
// "plain practice" get their numbers from the very same bytecode that runs.
#pragma once
#include <array>
#include <unordered_map>

namespace plain {

struct Observer {
    // ---- what to do
    bool trace = false;          // record a step for every source line that runs
    bool capture = false;        // keep what the program says instead of printing it
    bool quietPrompts = false;   // with capture: leave out the questions that 'ask' shows (lesson checks)
    bool showLibrary = false;    // also step through the built-in library's own code
    uint64_t maxInstr = 0;       // stop the run after this many instructions (0 = no limit)
    size_t maxSteps = 6000;      // stop recording after this many steps

    // ---- counts (always kept)
    uint64_t instr = 0, compares = 0, swaps = 0, writes = 0, calls = 0;
    std::unordered_map<std::string, uint64_t> callsByName;

    // ---- the trace
    struct Step {
        int line = 0, depth = 0, file = 0, call = -1, outCount = 0;
        std::vector<std::pair<std::string, int>> globals;
        struct FrameView {
            std::string name;
            int line = 0;
            std::vector<std::pair<std::string, int>> vars;
        };
        std::vector<FrameView> frames;
        std::vector<std::pair<int, int64_t>> compared, written;
        std::vector<std::array<int64_t, 3>> swapped;
        int ret = -2;              // id of the returned value, -2 when this step is not a return
        std::string error;
    };
    struct CallNode {
        int parent = -1, start = 0, end = -1, ret = -1;
        std::string name;
        std::vector<int> args;
    };
    std::vector<Step> steps;
    std::vector<CallNode> callNodes;
    std::vector<std::string> outputChunks;
    std::vector<std::string> valueJson;           // interned values, referred to by index
    std::unordered_map<std::string, int> valueIndex;
    std::vector<std::string> files;               // source files seen in the trace
    bool truncated = false;

    // ---- bookkeeping while running
    std::unordered_map<const void*, int> ids;
    std::vector<int> callStack;                    // call node of each action in progress (-1: not shown)
    std::vector<std::vector<char>> assigned;       // per frame: has this variable been given a value yet?
    bool pending = false;
    int pendLine = 0, pendFile = 0;
    size_t pendDepth = 0;
    std::vector<std::pair<int, int64_t>> reads, cmpMarks, writeMarks;
    std::vector<std::array<int64_t, 3>> swapMarks;
    struct Write { int id; int64_t index; Value oldv, newv; };
    std::vector<Write> lastWrites;

    int idOf(const void* p) {
        auto it = ids.find(p);
        if (it != ids.end()) return it->second;
        int id = (int)ids.size() + 1;
        ids.emplace(p, id);
        return id;
    }
    static bool isLibrary(const Func* f) { return f->file.compare(0, 6, "<lib>/") == 0; }
    bool hidden(const Func* f) const { return !showLibrary && isLibrary(f); }
    int fileIndex(const std::string& f) {
        for (size_t i = 0; i < files.size(); ++i)
            if (files[i] == f) return (int)i;
        files.push_back(f);
        return (int)files.size() - 1;
    }

    // ---------------------------------------------------------- values as JSON
    static void jsonString(std::string& out, const std::string& s) {
        out += '"';
        for (size_t i = 0; i < s.size(); ++i) {
            unsigned char c = (unsigned char)s[i];
            if (c == '"') out += "\\\"";
            else if (c == '\\') out += "\\\\";
            else if (c == '\n') out += "\\n";
            else if (c == '\r') out += "\\r";
            else if (c == '\t') out += "\\t";
            else if (c < 0x20) { char b[8]; snprintf(b, sizeof b, "\\u%04x", c); out += b; }
            else if (c < 0x80) out += (char)c;
            else {
                int len = c >= 0xF0 ? 4 : c >= 0xE0 ? 3 : c >= 0xC0 ? 2 : 0;
                bool ok = len > 0 && i + (size_t)len <= s.size();
                for (int k = 1; ok && k < len; ++k) ok = ((unsigned char)s[i + (size_t)k] & 0xC0) == 0x80;
                if (ok) { out.append(s, i, (size_t)len); i += (size_t)len - 1; }
                else out += "\xEF\xBF\xBD";
            }
        }
        out += '"';
    }
    void valueToJson(const Value& v, std::string& out, int depth, int& budget, std::vector<const void*>& path) {
        if (--budget < 0) { out += "{\"$\":\"more\"}"; return; }
        switch (v.tag) {
            case Value::Nothing: out += "null"; return;
            case Value::Bool: out += v.b ? "true" : "false"; return;
            case Value::Int:
                if (v.i > 9007199254740991LL || v.i < -9007199254740991LL) { out += "{\"$\":\"n\",\"s\":\"" + std::to_string(v.i) + "\"}"; return; }
                out += std::to_string(v.i);
                return;
            case Value::Float:
                if (!std::isfinite(v.n)) { out += "{\"$\":\"n\",\"s\":\"" + fmt(v) + "\"}"; return; }
                out += fmt(v);
                return;
            default: break;
        }
        if (isBig(v) || isDec(v)) { out += "{\"$\":\"n\",\"s\":\"" + fmt(v) + "\"}"; return; }
        if (isStr(v)) {
            const std::string& s = asStr(v);
            jsonString(out, s.size() > 240 ? s.substr(0, 240) + "..." : s);
            return;
        }
        if (v.tag != Value::Object) { out += "null"; return; }
        const void* key = v.o;
        if (isList(v) || isMap(v) || isInstance(v)) {
            for (const void* p : path)
                if (p == key) { out += "{\"$\":\"cycle\",\"id\":" + std::to_string(idOf(key)) + "}"; return; }
            if (depth > 14) { out += "{\"$\":\"deep\"}"; return; }
            path.push_back(key);
            int id = idOf(key);
            if (isList(v)) {
                const auto& items = asList(v)->items;
                out += "{\"L\":" + std::to_string(id) + ",\"n\":" + std::to_string(items.size()) + ",\"v\":[";
                size_t shown = std::min<size_t>(items.size(), 80);
                for (size_t i = 0; i < shown; ++i) {
                    if (i) out += ',';
                    valueToJson(items[i], out, depth + 1, budget, path);
                }
                out += "]}";
            } else {
                const Map* m = isMap(v) ? asMap(v) : asMap(asInstance(v)->fields);
                out += isMap(v) ? "{\"M\":" : "{\"O\":";
                out += std::to_string(id);
                if (isInstance(v)) { out += ",\"c\":"; jsonString(out, asClass(asInstance(v)->cls)->name); }
                out += ",\"n\":" + std::to_string(m->entries.size()) + ",\"v\":[";
                size_t shown = std::min<size_t>(m->entries.size(), 60), i = 0;
                for (const auto& e : m->entries) {
                    if (i >= shown) break;
                    if (i++) out += ',';
                    out += '[';
                    valueToJson(e.first, out, depth + 1, budget, path);
                    out += ',';
                    valueToJson(e.second, out, depth + 1, budget, path);
                    out += ']';
                }
                out += "]}";
            }
            path.pop_back();
            return;
        }
        if (isClass(v)) { out += "{\"C\":"; jsonString(out, asClass(v)->name); out += "}"; return; }
        out += "{\"F\":";
        std::string name;
        if (v.o->kind == Kind::Closure) name = static_cast<Closure*>(v.o)->fn->name;
        else if (v.o->kind == Kind::Native) name = static_cast<Native*>(v.o)->name;
        jsonString(out, name);
        out += "}";
    }
    int intern(const Value& v) {
        std::string js;
        int budget = 600;
        std::vector<const void*> path;
        valueToJson(v, js, 0, budget, path);
        auto it = valueIndex.find(js);
        if (it != valueIndex.end()) return it->second;
        valueJson.push_back(js);
        valueIndex.emplace(std::move(js), (int)valueJson.size() - 1);
        return (int)valueJson.size() - 1;
    }
    static bool isData(const Value& v) {
        if (v.tag != Value::Object) return v.tag != Value::Undef;
        Kind k = v.o->kind;
        return k != Kind::Closure && k != Kind::Native && k != Kind::Class && k != Kind::Bound && k != Kind::Func && k != Kind::Handle &&
               k != Kind::Upval;
    }

    // ------------------------------------------------------------- the hooks
    void tick(VM& vm, const Func* fn, size_t pc, uint32_t ins, Value* sp) {
        ++instr;
        if (maxInstr && instr > maxInstr) {
            PlainError e;
            e.msg = "This ran for more than " + std::to_string(maxInstr) + " instructions, so I stopped it. Is there a loop that never ends?";
            e.fatal = true;
            throw e;
        }
        if (!trace || hidden(fn) || truncated) return;
        int line = pc < fn->lines.size() ? fn->lines[pc] : 0;
        size_t depth = vm.frames.size();
        int file = fileIndex(fn->file);
        if (pending && (line != pendLine || depth != pendDepth || file != pendFile)) flush(vm, -2, "");
        if (!pending) {
            pending = true;
            pendLine = line;
            pendDepth = depth;
            pendFile = file;
        }
        if ((int)(ins & 0xFF) == OP_RETURN && depth > 1 && sp > vm.stack) {
            // The last instruction of an action: record this step with the answer, before the action disappears.
            flush(vm, intern(sp[-1]), "");
        }
    }
    void onCall(VM& vm, const Func* f, Value* base, int nargs) {
        size_t depth = vm.frames.size();
        assigned.resize(depth);
        assigned[depth - 1].assign((size_t)f->nlocals, 0);
        for (int i = 0; i < nargs && i < f->nlocals; ++i) assigned[depth - 1][(size_t)i] = 1;
        callStack.resize(depth - 1);
        bool main = f->name == "main program";
        if (!main) { ++calls; ++callsByName[f->name.empty() ? "(unnamed action)" : f->name]; }
        int node = -1;
        if (trace && !main && !hidden(f) && !truncated && callNodes.size() < 4000) {
            CallNode n;
            n.name = f->name.empty() ? "(action)" : f->name;
            for (int i = (int)f->isMethod; i < nargs; ++i) n.args.push_back(intern(base[i]));
            n.start = (int)steps.size();
            for (size_t i = callStack.size(); i-- > 0;)
                if (callStack[i] >= 0) { n.parent = callStack[i]; break; }
            callNodes.push_back(std::move(n));
            node = (int)callNodes.size() - 1;
        }
        callStack.push_back(node);
    }
    void onSetLocal(VM& vm, uint32_t slot) {
        size_t depth = vm.frames.size();
        if (depth == 0 || depth > assigned.size()) return;
        auto& a = assigned[depth - 1];
        if (slot < a.size()) a[slot] = 1;
    }
    void onCompare() {
        ++compares;
        if (!trace) return;
        for (const auto& r : reads) cmpMarks.push_back(r);
        reads.clear();
    }
    void onRead(const Value& box, const Value& key) {
        if (!trace || !isList(box) || key.tag != Value::Int) return;
        if (key.i < 1 || (uint64_t)key.i > asList(box)->items.size()) return;
        reads.emplace_back(idOf(box.o), key.i - 1);
        if (reads.size() > 2) reads.erase(reads.begin());
    }
    void onWrite(const Value& box, const Value& key, const Value& newv) {
        if (!isList(box) || key.tag != Value::Int) return;
        List* l = asList(box);
        if (key.i < 1 || (uint64_t)key.i > l->items.size()) return;
        ++writes;
        int id = idOf(box.o);
        int64_t idx = key.i - 1;
        const Value& oldv = l->items[(size_t)idx];
        if (trace) writeMarks.emplace_back(id, idx);
        if (!equals(oldv, newv)) {
            for (size_t k = lastWrites.size(); k-- > 0;) {
                Write& w = lastWrites[k];
                if (w.id == id && w.index != idx && equals(w.oldv, newv) && equals(w.newv, oldv)) {
                    ++swaps;
                    if (trace) swapMarks.push_back({id, w.index, idx});
                    lastWrites.erase(lastWrites.begin() + (long)k);
                    return;
                }
            }
            lastWrites.push_back({id, idx, oldv, newv});
            if (lastWrites.size() > 4) lastWrites.erase(lastWrites.begin());
        }
    }
    void output(const std::string& text) { outputChunks.push_back(text); }
    // An error is about to travel up: show where it happened.
    void onError(VM& vm, const PlainError& e) {
        if (!trace || truncated) return;
        if (pending) flush(vm, -2, e.msg);
    }
    // Frames were thrown away by an error handler.
    void onUnwind(VM& vm) {
        callStack.resize(std::min(callStack.size(), vm.frames.size()));
        assigned.resize(std::min(assigned.size(), vm.frames.size()));
    }
    void finish(VM& vm) {
        if (trace && pending && !truncated) flush(vm, -2, "");
    }

    // Record the step that has just finished.
    void flush(VM& vm, int ret, const std::string& error) {
        pending = false;
        if (steps.size() >= maxSteps) { truncated = true; return; }
        Step s;
        s.line = pendLine;
        s.file = pendFile;
        s.depth = (int)pendDepth;
        s.ret = ret;
        s.error = error;
        s.outCount = (int)outputChunks.size();
        s.compared = cmpMarks;
        s.written = writeMarks;
        s.swapped = swapMarks;
        cmpMarks.clear();
        writeMarks.clear();
        swapMarks.clear();
        reads.clear();
        size_t limit = std::min(pendDepth, vm.frames.size());
        for (size_t i = callStack.size(); i-- > 0;)
            if (i < limit && callStack[i] >= 0) { s.call = callStack[i]; break; }
        if (ret != -2 && s.call >= 0) {
            callNodes[(size_t)s.call].end = (int)steps.size();
            callNodes[(size_t)s.call].ret = ret;
        }
        Program& prog = vm.prog;
        for (size_t g = 0; g < prog.gnames.size(); ++g) {
            if (!prog.gdeclared[g] || !isData(prog.gvals[g])) continue;
            s.globals.emplace_back(prog.gnames[g], intern(prog.gvals[g]));
        }
        for (size_t i = 0; i < limit; ++i) {
            const VM::Frame& fr = vm.frames[i];
            if (hidden(fr.fn)) continue;
            std::vector<std::pair<std::string, int>> vars;
            for (size_t k = 0; k < fr.fn->localNames.size() && k < (size_t)fr.fn->nlocals; ++k) {
                const std::string& name = fr.fn->localNames[k];
                if (name.empty()) continue;
                if (i < assigned.size() && k < assigned[i].size() && !assigned[i][k]) continue;
                const Value& val = fr.base[k];
                if (!isData(val)) continue;
                vars.emplace_back(name, intern(val));
            }
            if (i == 0) {
                for (auto& v : vars) s.globals.push_back(v);  // loop counters kept at the top level
                continue;
            }
            Step::FrameView fv;
            fv.name = fr.fn->name.empty() ? "(action)" : fr.fn->name;
            if (fr.fn->isMethod && !vars.empty() && vars[0].first == "me") vars.erase(vars.begin());
            fv.vars = std::move(vars);
            if (i + 1 == limit) fv.line = pendLine;  // the frame that was running
            else if (i + 1 < vm.frames.size() && fr.ip && fr.ip > fr.fn->code.data()) {
                size_t off = (size_t)(fr.ip - fr.fn->code.data()) - 1;  // the call it is waiting on
                if (off < fr.fn->lines.size()) fv.line = fr.fn->lines[off];
            }
            s.frames.push_back(std::move(fv));
        }
        steps.push_back(std::move(s));
    }

    // ------------------------------------------------------ the whole trace as JSON
    std::string traceJson(const std::vector<std::pair<std::string, std::string>>& sources, const std::vector<std::string>& watch,
                          const std::string& errorMsg, int errorLine,
                          const std::vector<std::pair<std::string, std::string>>& views = {}) const {
        std::string o = "{\"sources\":[";
        for (size_t i = 0; i < sources.size(); ++i) {
            if (i) o += ',';
            o += "{\"name\":";
            jsonString(o, sources[i].first);
            o += ",\"text\":";
            jsonString(o, sources[i].second);
            o += "}";
        }
        o += "],\"files\":[";
        for (size_t i = 0; i < files.size(); ++i) {
            if (i) o += ',';
            jsonString(o, files[i]);
        }
        o += "],\"watch\":[";
        for (size_t i = 0; i < watch.size(); ++i) {
            if (i) o += ',';
            jsonString(o, watch[i]);
        }
        o += "],\"views\":{";
        for (size_t i = 0; i < views.size(); ++i) {
            if (i) o += ',';
            jsonString(o, views[i].first);
            o += ':';
            jsonString(o, views[i].second);
        }
        o += "},\"vals\":[";
        for (size_t i = 0; i < valueJson.size(); ++i) {
            if (i) o += ',';
            o += valueJson[i];
        }
        o += "],\"out\":[";
        for (size_t i = 0; i < outputChunks.size(); ++i) {
            if (i) o += ',';
            jsonString(o, outputChunks[i]);
        }
        o += "],\"calls\":[";
        for (size_t i = 0; i < callNodes.size(); ++i) {
            const CallNode& c = callNodes[i];
            if (i) o += ',';
            o += "{\"p\":" + std::to_string(c.parent) + ",\"s\":" + std::to_string(c.start) + ",\"e\":" + std::to_string(c.end) +
                 ",\"r\":" + std::to_string(c.ret) + ",\"n\":";
            jsonString(o, c.name);
            o += ",\"a\":[";
            for (size_t k = 0; k < c.args.size(); ++k) o += (k ? "," : "") + std::to_string(c.args[k]);
            o += "]}";
        }
        o += "],\"steps\":[";
        auto pairs = [&](const std::vector<std::pair<std::string, int>>& v) {
            std::string r = "[";
            for (size_t k = 0; k < v.size(); ++k) {
                if (k) r += ',';
                r += '[';
                jsonString(r, v[k].first);
                r += "," + std::to_string(v[k].second) + "]";
            }
            return r + "]";
        };
        for (size_t i = 0; i < steps.size(); ++i) {
            const Step& s = steps[i];
            if (i) o += ',';
            o += "{\"l\":" + std::to_string(s.line) + ",\"fi\":" + std::to_string(s.file) + ",\"d\":" + std::to_string(s.depth) +
                 ",\"o\":" + std::to_string(s.outCount) + ",\"cs\":" + std::to_string(s.call) + ",\"g\":" + pairs(s.globals) + ",\"f\":[";
            for (size_t k = 0; k < s.frames.size(); ++k) {
                if (k) o += ',';
                o += "{\"n\":";
                jsonString(o, s.frames[k].name);
                o += ",\"l\":" + std::to_string(s.frames[k].line) + ",\"v\":" + pairs(s.frames[k].vars) + "}";
            }
            o += "]";
            if (s.ret != -2) o += ",\"r\":" + std::to_string(s.ret);
            if (!s.compared.empty()) {
                o += ",\"c\":[";
                for (size_t k = 0; k < s.compared.size(); ++k) o += (k ? "," : "") + std::string("[") + std::to_string(s.compared[k].first) + "," + std::to_string(s.compared[k].second) + "]";
                o += "]";
            }
            if (!s.written.empty()) {
                o += ",\"w\":[";
                for (size_t k = 0; k < s.written.size(); ++k) o += (k ? "," : "") + std::string("[") + std::to_string(s.written[k].first) + "," + std::to_string(s.written[k].second) + "]";
                o += "]";
            }
            if (!s.swapped.empty()) {
                o += ",\"s\":[";
                for (size_t k = 0; k < s.swapped.size(); ++k)
                    o += (k ? "," : "") + std::string("[") + std::to_string(s.swapped[k][0]) + "," + std::to_string(s.swapped[k][1]) + "," + std::to_string(s.swapped[k][2]) + "]";
                o += "]";
            }
            if (!s.error.empty()) { o += ",\"e\":"; jsonString(o, s.error); }
            o += "}";
        }
        o += "],\"truncated\":";
        o += truncated ? "true" : "false";
        o += ",\"counts\":{\"instructions\":" + std::to_string(instr) + ",\"comparisons\":" + std::to_string(compares) +
             ",\"swaps\":" + std::to_string(swaps) + ",\"writes\":" + std::to_string(writes) + ",\"calls\":" + std::to_string(calls) + "}";
        o += ",\"error\":";
        if (errorMsg.empty()) o += "null";
        else {
            o += "{\"msg\":";
            jsonString(o, errorMsg);
            o += ",\"line\":" + std::to_string(errorLine) + "}";
        }
        return o + "}";
    }
};

}  // namespace plain
