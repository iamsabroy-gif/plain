// Plain - values, objects and shared helpers.
#pragma once
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "bigint.hpp"

// Where Plain runs. The web playground (WebAssembly) has no threads, sockets, processes or
// package manager, like the Windows build has no sockets or git: PLAIN_POSIX is for full builds.
#if defined(__wasi__) && !defined(PLAIN_WASM)
#define PLAIN_WASM 1
#endif
#if !defined(_WIN32) && !defined(PLAIN_WASM)
#define PLAIN_POSIX 1
#endif

namespace plain {

// Every problem Plain reports to the user travels as a PlainError.
struct PlainError {
    std::string msg;
    int line = 0;
    std::string file;
    bool incomplete = false;  // the program ended inside an open block (used by the interactive session)
    bool fatal = false;       // cannot be caught by 'try' (the run was stopped from outside)
};

[[noreturn]] inline void fail(const std::string& msg, int line = 0) {
    PlainError e;
    e.msg = msg;
    e.line = line;
    throw e;
}

// ---------------------------------------------------------------- objects
enum class Kind : uint8_t { Str, BigNum, Decimal, List, Map, Func, Native, Closure, Upval, Class, Instance, Bound, Handle };

// Heap objects are reference counted.
struct Obj {
    uint32_t rc = 0;
    Kind kind;
    explicit Obj(Kind k) : kind(k) {}
    virtual ~Obj() {}
};

struct Value;
struct Visitor {
    virtual void visit(const Value& v) = 0;
    virtual ~Visitor() {}
};

// Objects that can hold other objects are tracked, so that groups of them
// that only refer to each other (cycles) can be found and freed.
struct GCObj;
struct GCState {
    GCObj* head = nullptr;
    size_t live = 0, allocs = 0, threshold = 100000;
};
inline GCState g_gc;

struct GCObj : Obj {
    GCObj* gprev = nullptr;
    GCObj* gnext = nullptr;
    int64_t gcRefs = 0;
    bool gmark = false;
    explicit GCObj(Kind k) : Obj(k) {
        gnext = g_gc.head;
        if (g_gc.head) g_gc.head->gprev = this;
        g_gc.head = this;
        ++g_gc.live;
        ++g_gc.allocs;
    }
    ~GCObj() override {
        if (gprev) gprev->gnext = gnext;
        else g_gc.head = gnext;
        if (gnext) gnext->gprev = gprev;
        --g_gc.live;
    }
    virtual void traverse(Visitor&) {}
    virtual void clearRefs() {}
};

// A Value is 16 bytes: a tag plus a number, a boolean or an object pointer.
struct Value {
    enum Tag : uint8_t { Nothing, Bool, Int, Float, Object, Undef };
    Tag tag;
    union {
        int64_t i;
        double n;
        bool b;
        Obj* o;
        uint64_t bits;
    };

    Value() : tag(Nothing), bits(0) {}
    Value(const Value& v) : tag(v.tag), bits(v.bits) {
        if (tag == Object) ++o->rc;
    }
    Value(Value&& v) noexcept : tag(v.tag), bits(v.bits) { v.tag = Nothing; }
    ~Value() { release(); }
    Value& operator=(const Value& v) {
        if (v.tag == Object) ++v.o->rc;
        release();
        tag = v.tag;
        bits = v.bits;
        return *this;
    }
    Value& operator=(Value&& v) noexcept {
        if (this != &v) {
            release();
            tag = v.tag;
            bits = v.bits;
            v.tag = Nothing;
        }
        return *this;
    }
    void release() {
        if (tag == Object && --o->rc == 0) delete o;
    }
    void clear() {
        release();
        tag = Nothing;
        bits = 0;
    }

    static Value integer(int64_t x) { Value v; v.tag = Int; v.i = x; return v; }
    static Value real(double x) { Value v; v.tag = Float; v.n = x; return v; }
    static Value boolean(bool x) { Value v; v.tag = Bool; v.b = x; return v; }
    static Value obj(Obj* p) { Value v; v.tag = Object; v.o = p; ++p->rc; return v; }
    static Value undef() { Value v; v.tag = Undef; return v; }
};

struct Str : Obj {
    std::string s;
    explicit Str(std::string x) : Obj(Kind::Str), s(std::move(x)) {}
};
struct BigNum : Obj {
    BigInt v;
    explicit BigNum(BigInt x) : Obj(Kind::BigNum), v(std::move(x)) {}
};
struct DecNum : Obj {
    Dec v;
    explicit DecNum(Dec x) : Obj(Kind::Decimal), v(std::move(x)) {}
};

inline bool isKind(const Value& v, Kind k) { return v.tag == Value::Object && v.o->kind == k; }
inline bool isStr(const Value& v) { return isKind(v, Kind::Str); }
inline bool isList(const Value& v) { return isKind(v, Kind::List); }
inline bool isMap(const Value& v) { return isKind(v, Kind::Map); }
inline bool isBig(const Value& v) { return isKind(v, Kind::BigNum); }
inline bool isDec(const Value& v) { return isKind(v, Kind::Decimal); }
inline bool isInstance(const Value& v) { return isKind(v, Kind::Instance); }
inline bool isClass(const Value& v) { return isKind(v, Kind::Class); }
inline bool isNumber(const Value& v) {
    return v.tag == Value::Int || v.tag == Value::Float || (v.tag == Value::Object && (v.o->kind == Kind::BigNum || v.o->kind == Kind::Decimal));
}
inline std::string& asStr(const Value& v) { return static_cast<Str*>(v.o)->s; }
inline const BigInt& asBig(const Value& v) { return static_cast<BigNum*>(v.o)->v; }
inline const Dec& asDec(const Value& v) { return static_cast<DecNum*>(v.o)->v; }
inline Value mkstr(std::string s) { return Value::obj(new Str(std::move(s))); }

struct List : GCObj {
    std::vector<Value> items;
    List() : GCObj(Kind::List) {}
    void traverse(Visitor& vis) override { for (const Value& v : items) vis.visit(v); }
    void clearRefs() override { std::vector<Value>().swap(items); }
};
inline List* asList(const Value& v) { return static_cast<List*>(v.o); }

// forward declarations (defined below / in numeric.hpp)
inline bool equals(const Value& a, const Value& b);
inline size_t hashValue(const Value& v);
inline std::string fmt(const Value& v, bool nested = false, int depth = 0);
inline int numCompare(const Value& a, const Value& b);

struct KeyHash { size_t operator()(const Value& v) const { return hashValue(v); } };
struct KeyEq { bool operator()(const Value& a, const Value& b) const { return equals(a, b); } };

inline void checkKey(const Value& k) {
    if (isNumber(k) || isStr(k) || k.tag == Value::Bool) return;
    fail("Only text, numbers and true/false can be used as names for entries in a map. Try using text, like to_json(x) or text(x), as the name.");
}

// A map keeps its entries in the order they were added.
struct Map : GCObj {
    std::vector<std::pair<Value, Value>> entries;
    std::unordered_map<Value, size_t, KeyHash, KeyEq> index;
    Map() : GCObj(Kind::Map) {}
    Value* find(const Value& k) {
        checkKey(k);
        auto it = index.find(k);
        return it == index.end() ? nullptr : &entries[it->second].second;
    }
    void set(const Value& k, Value v) {
        checkKey(k);
        auto it = index.find(k);
        if (it != index.end()) {
            entries[it->second].second = std::move(v);
        } else {
            index.emplace(k, entries.size());
            entries.emplace_back(k, std::move(v));
        }
    }
    bool remove(const Value& k) {
        checkKey(k);
        auto it = index.find(k);
        if (it == index.end()) return false;
        entries.erase(entries.begin() + (long)it->second);
        index.clear();
        for (size_t i = 0; i < entries.size(); ++i) index.emplace(entries[i].first, i);
        return true;
    }
    void traverse(Visitor& vis) override { for (const auto& e : entries) { vis.visit(e.first); vis.visit(e.second); } }
    void clearRefs() override {
        index.clear();
        std::vector<std::pair<Value, Value>>().swap(entries);
    }
};
inline Map* asMap(const Value& v) { return static_cast<Map*>(v.o); }

// A compiled action (function) prototype: bytecode plus its constants.
struct UpDesc {
    bool isLocal;
    uint32_t index;
};
struct Func : Obj {
    std::string name, file;
    int nparams = 0, nlocals = 0;
    bool isMethod = false;  // slot 0 is 'me'; nparams counts it
    std::vector<uint32_t> code;
    std::vector<int> lines;  // source line of each code word
    std::vector<Value> consts;
    std::vector<std::string> localNames;
    std::vector<UpDesc> upvals;
    Func() : Obj(Kind::Func) {}
};

// A variable of an enclosing action that a closure still uses.
struct Upval : GCObj {
    Value* slot = nullptr;  // into the stack while open; &closed afterwards
    Value closed;
    Upval() : GCObj(Kind::Upval) {}
    void traverse(Visitor& vis) override { if (slot == &closed) vis.visit(closed); }
    void clearRefs() override { closed.clear(); }
};

// An action ready to be called: a prototype plus the variables it captured.
struct Closure : GCObj {
    Value protoVal;
    Func* fn;
    std::vector<Value> ups;
    explicit Closure(Func* f) : GCObj(Kind::Closure), protoVal(Value::obj(f)), fn(f) {}
    void traverse(Visitor& vis) override { for (const Value& v : ups) vis.visit(v); }
    void clearRefs() override { std::vector<Value>().swap(ups); }
};

struct Class : GCObj {
    std::string name;
    Value parent;
    std::unordered_map<std::string, Value> methods;
    explicit Class(std::string n) : GCObj(Kind::Class), name(std::move(n)) {}
    void traverse(Visitor& vis) override { vis.visit(parent); for (const auto& m : methods) vis.visit(m.second); }
    void clearRefs() override { parent.clear(); methods.clear(); }
    const Value* findMethod(const std::string& n) const {
        for (const Class* c = this;;) {
            auto it = c->methods.find(n);
            if (it != c->methods.end()) return &it->second;
            if (!isClass(c->parent)) return nullptr;
            c = static_cast<const Class*>(c->parent.o);
        }
    }
};
inline Class* asClass(const Value& v) { return static_cast<Class*>(v.o); }

struct Instance : GCObj {
    Value cls;     // a Class
    Value fields;  // a Map
    Instance() : GCObj(Kind::Instance) {}
    void traverse(Visitor& vis) override { vis.visit(cls); vis.visit(fields); }
    void clearRefs() override { cls.clear(); fields.clear(); }
};
inline Instance* asInstance(const Value& v) { return static_cast<Instance*>(v.o); }

// An action of an object, remembered together with the object ('me').
struct Bound : GCObj {
    Value self, method;
    Bound(Value s, Value m) : GCObj(Kind::Bound), self(std::move(s)), method(std::move(m)) {}
    void traverse(Visitor& vis) override { vis.visit(self); vis.visit(method); }
    void clearRefs() override { self.clear(); method.clear(); }
};

// Threads, channels, locks, sockets: things you can pass around but not look inside.
struct Handle : GCObj {
    Handle() : GCObj(Kind::Handle) {}
    virtual std::string label() const = 0;
};

struct VM;
typedef Value (*NativeFn)(VM&, Value*, int);

// A built-in action written in C++.
struct Native : Obj {
    std::string name;
    int arity;  // -1 means "any number of values"
    NativeFn fn;
    Native(std::string n, int a, NativeFn f) : Obj(Kind::Native), name(std::move(n)), arity(a), fn(f) {}
};

// Set by the VM: asks an object's own 'to_text' action for its text.
// Returns Undef when the object has none.
inline Value (*g_toTextHook)(const Value&) = nullptr;

// ------------------------------------------------------------- formatting
inline std::string fmtNum(double x) {
    char buf[64];
    if (x == std::floor(x) && std::fabs(x) < 1e15) snprintf(buf, sizeof buf, "%lld", (long long)x);
    else snprintf(buf, sizeof buf, "%.14g", x);
    return buf;
}

inline std::string quote(const std::string& s) {
    std::string out = "\"";
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else if (c == '\n') out += "\\n";
        else if (c == '\t') out += "\\t";
        else out += c;
    }
    return out + "\"";
}

inline std::string fmt(const Value& v, bool nested, int depth) {
    switch (v.tag) {
        case Value::Nothing: return "nothing";
        case Value::Undef: return "nothing";
        case Value::Bool: return v.b ? "true" : "false";
        case Value::Int: return std::to_string(v.i);
        case Value::Float: return fmtNum(v.n);
        default: break;
    }
    if (depth > 40) return "...";
    switch (v.o->kind) {
        case Kind::Str: return nested ? quote(asStr(v)) : asStr(v);
        case Kind::BigNum: return asBig(v).toString();
        case Kind::Decimal: return decToString(asDec(v));
        case Kind::List: {
            std::string out = "[";
            List* l = asList(v);
            Value keep = v;
            for (size_t i = 0; i < l->items.size(); ++i) {
                if (i) out += ", ";
                Value x = l->items[i];  // a copy: formatting may run Plain code that changes the list
                out += fmt(x, true, depth + 1);
            }
            return out + "]";
        }
        case Kind::Map: {
            std::string out = "{";
            Map* m = asMap(v);
            Value keep = v;
            for (size_t i = 0; i < m->entries.size(); ++i) {
                if (i) out += ", ";
                Value k = m->entries[i].first, x = m->entries[i].second;
                out += fmt(k, true, depth + 1) + ": " + fmt(x, true, depth + 1);
            }
            return out + "}";
        }
        case Kind::Instance: {
            if (g_toTextHook) {
                Value r = g_toTextHook(v);
                if (r.tag != Value::Undef) return isStr(r) ? asStr(r) : fmt(r, false, depth + 1);
            }
            Instance* inst = asInstance(v);
            std::string out = asClass(inst->cls)->name + "(";
            Map* m = asMap(inst->fields);
            Value keep = v;
            for (size_t i = 0; i < m->entries.size(); ++i) {
                if (i) out += ", ";
                Value k = m->entries[i].first, x = m->entries[i].second;
                out += fmt(k, false, depth + 1) + ": " + fmt(x, true, depth + 1);
            }
            return out + ")";
        }
        case Kind::Class: return "<class " + asClass(v)->name + ">";
        case Kind::Closure: {
            const std::string& n = static_cast<Closure*>(v.o)->fn->name;
            return n.empty() ? "<action>" : "<action " + n + ">";
        }
        case Kind::Func: return "<action " + static_cast<Func*>(v.o)->name + ">";
        case Kind::Native: return "<action " + static_cast<Native*>(v.o)->name + ">";
        case Kind::Bound: return "<action of " + fmt(static_cast<Bound*>(v.o)->self, false, depth + 1) + ">";
        case Kind::Handle: return "<" + static_cast<Handle*>(v.o)->label() + ">";
        case Kind::Upval: return "<variable>";
    }
    return "?";
}

// How Plain describes a value's type in messages.
inline const char* kindName(const Value& v) {
    switch (v.tag) {
        case Value::Bool: return "a true/false value";
        case Value::Int: case Value::Float: return "a number";
        case Value::Object:
            switch (v.o->kind) {
                case Kind::Str: return "text";
                case Kind::BigNum: case Kind::Decimal: return "a number";
                case Kind::List: return "a list";
                case Kind::Map: return "a map";
                case Kind::Instance: return "an object";
                case Kind::Class: return "a class";
                case Kind::Handle: return "a handle";
                default: return "an action";
            }
        default: return "nothing";
    }
}

inline std::string describe(const Value& v) { return std::string(kindName(v)) + " (" + fmt(v, true) + ")"; }

inline bool truthy(const Value& v) {
    switch (v.tag) {
        case Value::Bool: return v.b;
        case Value::Int: return v.i != 0;
        case Value::Float: return v.n != 0;
        case Value::Object:
            if (v.o->kind == Kind::Str) return !asStr(v).empty();
            if (v.o->kind == Kind::List) return !asList(v)->items.empty();
            if (v.o->kind == Kind::Decimal) return !asDec(v).u.isZero();
            return true;
        default: return false;
    }
}

inline bool equals(const Value& a, const Value& b) {
    if (isNumber(a)) return isNumber(b) && numCompare(a, b) == 0;
    if (a.tag != b.tag) return false;
    switch (a.tag) {
        case Value::Bool: return a.b == b.b;
        case Value::Object: break;
        default: return true;
    }
    if (a.o == b.o) return true;
    if (a.o->kind != b.o->kind) return false;
    if (a.o->kind == Kind::Str) return asStr(a) == asStr(b);
    if (a.o->kind == Kind::List) {
        const auto& x = asList(a)->items;
        const auto& y = asList(b)->items;
        if (x.size() != y.size()) return false;
        for (size_t i = 0; i < x.size(); ++i)
            if (!equals(x[i], y[i])) return false;
        return true;
    }
    if (a.o->kind == Kind::Map) {
        Map* x = asMap(a);
        Map* y = asMap(b);
        if (x->entries.size() != y->entries.size()) return false;
        for (const auto& e : x->entries) {
            Value* other = y->find(e.first);
            if (!other || !equals(e.second, *other)) return false;
        }
        return true;
    }
    return false;
}

// ------------------------------------------------------------------ UTF-8
inline size_t u8len(const std::string& s) {
    size_t n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) ++n;
    return n;
}

// Split text into characters (code points), so non-English text works too.
inline std::vector<std::string> u8chars(const std::string& s) {
    std::vector<std::string> out;
    for (size_t i = 0; i < s.size();) {
        size_t j = i + 1;
        while (j < s.size() && ((unsigned char)s[j] & 0xC0) == 0x80) ++j;
        out.emplace_back(s, i, j - i);
        i = j;
    }
    return out;
}

// --------------------------------------------------------- "did you mean"
inline size_t editDistance(const std::string& a, const std::string& b) {
    // Counts single-letter slips: a wrong, missing or extra letter, or two letters swapped.
    std::vector<std::vector<size_t>> d(a.size() + 1, std::vector<size_t>(b.size() + 1));
    for (size_t i = 0; i <= a.size(); ++i) d[i][0] = i;
    for (size_t j = 0; j <= b.size(); ++j) d[0][j] = j;
    for (size_t i = 1; i <= a.size(); ++i)
        for (size_t j = 1; j <= b.size(); ++j) {
            d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
            if (i > 1 && j > 1 && a[i - 1] == b[j - 2] && a[i - 2] == b[j - 1]) d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + 1);
        }
    return d[a.size()][b.size()];
}

inline std::string closest(const std::string& name, const std::vector<std::string>& candidates) {
    size_t limit = std::max<size_t>(1, name.size() / 3);
    std::string best;
    size_t bestD = limit + 1;
    for (const std::string& c : candidates) {
        if (c == name || c.empty()) continue;
        size_t d = editDistance(name, c);
        if (d < bestD) {
            bestD = d;
            best = c;
        }
    }
    return best;
}

inline bool readFile(const std::string& path, std::string& out) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return false;
    char buf[65536];
    size_t n;
    out.clear();
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) out.append(buf, n);
    fclose(f);
    return true;
}

}  // namespace plain
