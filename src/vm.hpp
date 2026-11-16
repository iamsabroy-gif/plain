// Plain - stage 3: the virtual machine that runs the bytecode.
#pragma once
#include <atomic>
#include <iostream>
#include <random>
#ifndef PLAIN_WASM
#include <condition_variable>
#include <mutex>
#include <thread>
#endif

#include "compiler.hpp"

namespace plain {

// ------------------------------------------------------ background tasks
// Only one task runs Plain code at any moment; they take turns, switching
// every few thousand instructions and whenever one of them waits (for input,
// the network, a timer or another task). This keeps shared data safe.
#ifdef PLAIN_WASM
// No threads in the web playground: there is only ever one task, so taking turns is a no-op.
struct Gil {
    void lock() {}
    void unlock() {}
    void yield() {}
};
#else
struct Gil {
    std::mutex m;
    std::condition_variable cv;
    uint64_t next = 0, serving = 0;
    std::atomic<int> waiting{0};
    void lock() {
        std::unique_lock<std::mutex> l(m);
        uint64_t mine = next++;
        ++waiting;
        cv.wait(l, [&] { return serving == mine; });
        --waiting;
    }
    void unlock() {
        {
            std::lock_guard<std::mutex> l(m);
            ++serving;
        }
        cv.notify_all();
    }
    void yield() {
        if (waiting.load(std::memory_order_relaxed) > 0) {
            unlock();
            lock();
        }
    }
};
#endif
inline Gil& gil() {
    static Gil g;
    return g;
}
inline std::atomic<bool>& tasksStarted() {
    static std::atomic<bool> started{false};
    return started;
}
// Put one of these around anything that waits, so other tasks can run meanwhile.
// Nothing inside may touch Plain values.
struct Unlocked {
    Unlocked() { gil().unlock(); }
    ~Unlocked() { gil().lock(); }
};

// ----------------------------------------------------- value operations
[[noreturn]] inline void arithFail(const char* verb, const Value& x, const Value& y) {
    fail(std::string("I can only ") + verb + " numbers, but I got " + kindName(x) + " and " + kindName(y) + " (" +
         fmt(x, true) + " and " + fmt(y, true) + "). If one is text that holds a number, use number(x) first.");
}
inline Value subValues(const Value& x, const Value& y) {
    if (!isNumber(x) || !isNumber(y)) arithFail("subtract", x, y);
    return numSub(x, y);
}
inline Value mulValues(const Value& x, const Value& y) {
    if (!isNumber(x) || !isNumber(y)) arithFail("multiply", x, y);
    return numMul(x, y);
}
inline Value divValues(const Value& x, const Value& y) {
    if (!isNumber(x) || !isNumber(y)) arithFail("divide", x, y);
    return numDiv(x, y);
}
inline Value modValues(const Value& x, const Value& y) {
    if (!isNumber(x) || !isNumber(y)) arithFail("take the remainder of", x, y);
    return numMod(x, y);
}
inline Value powValues(const Value& x, const Value& y) {
    if (!isNumber(x) || !isNumber(y)) arithFail("raise to a power", x, y);
    return numPow(x, y);
}

inline Value addValues(const Value& x, const Value& y) {
    if (isNumber(x) && isNumber(y)) return numAdd(x, y);
    if (isStr(x) && isStr(y)) return mkstr(asStr(x) + asStr(y));
    if (isStr(x)) return mkstr(asStr(x) + fmt(y));
    if (isStr(y)) return mkstr(fmt(x) + asStr(y));
    if (isList(x) && isList(y)) {
        List* l = new List;
        Value out = Value::obj(l);
        l->items = asList(x)->items;
        l->items.insert(l->items.end(), asList(y)->items.begin(), asList(y)->items.end());
        return out;
    }
    fail(std::string("I can't add ") + kindName(x) + " and " + kindName(y) + " (" + fmt(x, true) + " and " + fmt(y, true) +
         "). Add numbers to numbers, text to text, or use text(x) to turn a value into text first.");
}

// -1, 0, 1 - or 2 when two numbers cannot be ordered (not-a-number).
inline int compareValues(const Value& x, const Value& y) {
    if (isNumber(x) && isNumber(y)) {
        checkMix(x, y);
        return numCompare(x, y);
    }
    if (isStr(x) && isStr(y)) {
        int c = asStr(x).compare(asStr(y));
        return c < 0 ? -1 : (c > 0 ? 1 : 0);
    }
    fail(std::string("I can't compare ") + kindName(x) + " with " + kindName(y) + " (" + fmt(x, true) + " and " + fmt(y, true) +
         "). Compare numbers with numbers, or text with text. Use number(x) or text(x) to convert.");
}

inline bool containsValue(const Value& box, const Value& x) {
    if (isStr(box)) return asStr(box).find(fmt(x)) != std::string::npos;
    if (isList(box)) {
        for (const Value& v : asList(box)->items)
            if (equals(v, x)) return true;
        return false;
    }
    if (isMap(box)) return asMap(box)->find(x) != nullptr;
    fail(std::string("'contains' needs a list, text or a map to look inside, but I got ") + describe(box) + ".");
}

inline size_t listIndex(const Value& k, size_t size, const char* what) {
    int64_t i;
    if (!wholeValue(k, i)) fail(std::string("An item number must be a whole number, but I got ") + describe(k) + ".");
    if (i < 1 || (uint64_t)i > size)
        fail(std::string("The ") + what + " has " + std::to_string(size) + (size == 1 ? " item" : " items") +
             ", so there is no item " + std::to_string(i) + ". " +
             (size == 0 ? std::string("It is empty - add something first, or check 'length of' before taking an item.")
                        : i < 1 ? std::string("Items are counted from 1, so the first item is item 1.")
                                : "Use a number from 1 to " + std::to_string(size) + ", or check 'length of' first."));
    return (size_t)i - 1;
}

[[noreturn]] inline void noMember(Instance* in, const Value& k, bool action) {
    std::vector<std::string> names;
    Map* fields = asMap(in->fields);
    for (const auto& e : fields->entries)
        if (isStr(e.first)) names.push_back(asStr(e.first));
    for (const Class* c = asClass(in->cls);;) {
        for (const auto& m : c->methods) names.push_back(m.first);
        if (!isClass(c->parent)) break;
        c = asClass(c->parent);
    }
    std::string c = isStr(k) ? closest(asStr(k), names) : "";
    fail("This " + asClass(in->cls)->name + " has " + (action ? "no action" : "nothing") + " called " +
         (isStr(k) ? "'" + asStr(k) + "'" : fmt(k, true)) + "." + (c.empty() ? "" : " Did you mean '" + c + "'?"));
}

inline Value getIndex(const Value& box, const Value& k) {
    if (isList(box)) {
        List* l = asList(box);
        return l->items[listIndex(k, l->items.size(), "list")];
    }
    if (isMap(box)) {
        Value* v = asMap(box)->find(k);
        if (v) return *v;
        std::vector<std::string> names;
        for (const auto& e : asMap(box)->entries)
            if (isStr(e.first)) names.push_back(asStr(e.first));
        std::string c = isStr(k) ? closest(asStr(k), names) : "";
        fail("This map has no entry called " + fmt(k, true) + "." +
             (c.empty() ? " Check the spelling, or test first with has_key(map, name)." : " Did you mean \"" + c + "\"?"));
    }
    if (isInstance(box)) {
        Instance* in = asInstance(box);
        if (!isStr(k)) noMember(in, k, false);
        Value* f = asMap(in->fields)->find(k);
        if (f) return *f;
        const Value* m = asClass(in->cls)->findMethod(asStr(k));
        if (!m) noMember(in, k, false);
        return Value::obj(new Bound(box, *m));
    }
    if (isStr(box)) {
        const std::string& s = asStr(box);
        if (u8len(s) == s.size()) return mkstr(std::string(1, s[listIndex(k, s.size(), "text")]));
        std::vector<std::string> chars = u8chars(s);
        return mkstr(chars[listIndex(k, chars.size(), "text")]);
    }
    fail(std::string("I can only take an item from a list, text, a map or an object, but I got ") + describe(box) + ".");
}

inline void setIndex(const Value& box, const Value& k, const Value& v) {
    if (isList(box)) {
        List* l = asList(box);
        l->items[listIndex(k, l->items.size(), "list")] = v;
    } else if (isMap(box)) {
        asMap(box)->set(k, v);
    } else if (isInstance(box)) {
        if (!isStr(k)) fail("The names of the things inside an object are text.");
        asMap(asInstance(box)->fields)->set(k, v);
    } else {
        fail(std::string("I can only change an item of a list, a map or an object, but I got ") + describe(box) + ".");
    }
}

inline int64_t lengthOf(const Value& v) {
    if (isList(v)) return (int64_t)asList(v)->items.size();
    if (isStr(v)) return (int64_t)u8len(asStr(v));
    if (isMap(v)) return (int64_t)asMap(v)->entries.size();
    fail(std::string("'length of' needs a list, text or a map, but I got ") + describe(v) + ".");
}

// "area needs 2 values (w, h), but you gave it 1."
inline std::string arityMessage(const Func* f, int given) {
    int want = f->nparams - (int)f->isMethod, got = given - (int)f->isMethod;
    std::string names;
    for (int i = (int)f->isMethod; i < f->nparams && i < (int)f->localNames.size(); ++i) names += (names.empty() ? "" : ", ") + f->localNames[(size_t)i];
    return "'" + (f->name.empty() ? std::string("this action") : f->name) + "' needs " + std::to_string(want) + " value(s)" +
           (names.empty() ? "" : " (" + names + ")") + ", but you gave it " + std::to_string(got) + ". Call it like: " +
           (f->name.empty() ? std::string("action") : f->name) + "(" + names + ")";
}

// ------------------------------------------------------------------- VM
struct VM;
struct Observer;
inline thread_local VM* tl_vm = nullptr;
inline Value vmToText(const Value& v);

struct VM {
    static const size_t MAX_FRAMES = 200000;

    struct Frame {
        Func* fn;
        Closure* cl;
        const uint32_t* ip;
        Value* base;
        Value* ret;  // where the answer goes
        bool ctor;   // an object's 'init': the call gives back the new object
    };
    struct Handler {
        size_t depth;
        Value* sp;
        const uint32_t* target;
    };

    Program& prog;
    Value* stack;
    Value* stackEnd;
    Value* spTop = nullptr;  // top of the stack while a built-in action runs
    std::vector<Frame> frames;
    std::vector<Handler> handlers;
    std::vector<Value> openUps;  // variables still living on the stack, lowest first
    std::vector<std::string> args;
    std::mt19937_64 rng;
    Observer* obs = nullptr;  // set to watch a run (counts, traces); null for a normal, full-speed run

    explicit VM(Program& p, size_t stackSize = 1 << 20) : prog(p), rng(std::random_device{}()) {
        stack = static_cast<Value*>(calloc(stackSize, sizeof(Value)));  // all-zero bits == nothing
        stackEnd = stack + stackSize;
        spTop = stack;
        tl_vm = this;
        g_toTextHook = vmToText;
    }
    ~VM() {
        for (Value* p = stack; p < stackEnd && p < stack + 64; ++p) p->clear();
        free(stack);
        if (tl_vm == this) tl_vm = nullptr;
    }
    VM(const VM&) = delete;

    [[noreturn]] void unknownName(const Func* fn, uint32_t slot, bool action) {
        std::vector<std::string> names;
        for (size_t i = 0; i < prog.gnames.size(); ++i)
            if (prog.gvals[i].tag != Value::Undef && (!action || prog.gvals[i].tag == Value::Object)) names.push_back(prog.gnames[i]);
        for (const std::string& n : fn->localNames) names.push_back(n);
        const std::string& name = prog.gnames[slot];
        std::string c = closest(name, names);
        if (action && c.empty()) {
            // Names other languages use, and what Plain calls them.
            static const std::unordered_map<std::string, const char*> elsewhere = {
                {"len", "length of xs"}, {"size", "length of xs"}, {"count", "length of xs"},
                {"append", "add x to xs"}, {"push", "add x to xs"}, {"str", "text(x)"}, {"string", "text(x)"},
                {"int", "integer(x)"}, {"num", "number(x)"}, {"input", "ask \"Question?\" into answer"},
                {"upper", "uppercase(t)"}, {"lower", "lowercase(t)"}, {"strip", "trim(t)"},
                {"sorted", "sort(xs)"}, {"reversed", "reverse(xs)"},
                {"type", "type_of(x)"}, {"filter", "keep_if(xs, test)"}, {"map", "map_each(xs, change)"},
            };
            auto it = elsewhere.find(name);
            if (it != elsewhere.end()) fail("Plain has no '" + name + "' action. Write: " + it->second);
        }
        if (action)
            fail("I don't know an action called '" + name + "'." + (c.empty() ? " Create it with 'define'." : " Did you mean '" + c + "'?"));
        fail("I don't know anything called '" + name + "'." +
             (c.empty() ? " Create it first with: set " + name + " to ..." : " Did you mean '" + c + "'?"));
    }

    Value capture(Value* loc) {
        size_t at = openUps.size();
        while (at > 0 && static_cast<Upval*>(openUps[at - 1].o)->slot > loc) --at;
        if (at > 0 && static_cast<Upval*>(openUps[at - 1].o)->slot == loc) return openUps[at - 1];
        Upval* u = new Upval;
        u->slot = loc;
        Value up = Value::obj(u);
        openUps.insert(openUps.begin() + (long)at, up);
        return up;
    }
    // The stack slots from 'from' upwards are about to disappear: move the
    // variables that anonymous actions still use into their own storage.
    void closeUps(Value* from) {
        while (!openUps.empty()) {
            Upval* up = static_cast<Upval*>(openUps.back().o);
            if (up->slot < from) break;
            up->closed = *up->slot;
            up->slot = &up->closed;
            openUps.pop_back();
        }
    }

    // Run a compiled program (a closure with no values).
    Value run(const Value& program) {
        frames.clear();
        handlers.clear();
        openUps.clear();
        Value* sp = stack;
        *sp++ = program;
        return execute(sp, 0, 0);
    }

    // A new round of a loop starts: variables of the last round that closures kept get their own copy,
    // so the next round makes new ones.
    void closeRange(Value* lo, Value* hi) {
        for (size_t i = openUps.size(); i-- > 0;) {
            Upval* up = static_cast<Upval*>(openUps[i].o);
            if (up->slot < lo) break;
            if (up->slot >= hi) continue;
            up->closed = *up->slot;
            up->slot = &up->closed;
            openUps.erase(openUps.begin() + (long)i);
        }
    }

    // Call any action with some values and wait for its answer. Safe to use from
    // inside a built-in action (that is how map_each and friends work).
    Value call(const Value& callee, const std::vector<Value>& values) {
        Value* sp = spTop;
        if (sp + values.size() + 8192 >= stackEnd) fail("Too many actions are waiting for each other.");
        *sp++ = callee;
        for (const Value& v : values) *sp++ = v;
        return execute(sp, (uint32_t)values.size(), frames.size());
    }

    // The main loop exists in two copies: one with the watching hooks compiled in, one without any trace of them.
    template <bool OBS>
    Value executeT(Value* sp, uint32_t nargs, size_t stopDepth);
    Value execute(Value* sp, uint32_t nargs, size_t stopDepth) {
        return obs ? executeT<true>(sp, nargs, stopDepth) : executeT<false>(sp, nargs, stopDepth);
    }
};

}  // namespace plain
#include "observe.hpp"
namespace plain {

// An object may define 'to_text' to say how it is shown.
inline Value vmToText(const Value& v) {
    VM* vm = tl_vm;
    if (!vm || !isInstance(v)) return Value::undef();
    const Value* m = asClass(asInstance(v)->cls)->findMethod("to_text");
    if (!m) return Value::undef();
    return vm->call(Value::obj(new Bound(v, *m)), {});
}

#define UPVAL(k) static_cast<Upval*>(cl->ups[k].o)

inline size_t collectGarbage();
#define TICK()                                                 \
    if (--budget < 0) {                                        \
        budget = 2048;                                         \
        if (g_gc.allocs >= g_gc.threshold) collectGarbage();   \
        gil().yield();                                         \
    }

#define SYNC() (spTop = sp)

// Start running action F (a closure's prototype, or a method). Values are on the stack from ARGBASE.
#define ENTER(F, C, ARGBASE, ARGC, RET, CTOR)                                                                      \
    {                                                                                                              \
        Func* f_ = (F);                                                                                            \
        if ((int)(ARGC) != f_->nparams)                                                                            \
            fail(arityMessage(f_, (int)(ARGC)));                                                                       \
        if (frames.size() >= MAX_FRAMES || sp + f_->nlocals + 4096 >= stackEnd)                                    \
            fail("'" + f_->name + "' keeps calling itself and never finishes. Make sure it has a case that stops, like: if n is at most 1 then give back 1"); \
        if (!frames.empty()) frames.back().ip = ip;                                                                \
        base = (ARGBASE);                                                                                          \
        for (int i_ = (int)(ARGC); i_ < f_->nlocals; ++i_) *sp++ = Value();                                        \
        cl = (C);                                                                                                  \
        frames.push_back({f_, cl, f_->code.data(), base, (RET), (CTOR)});                                          \
        fn = f_;                                                                                                   \
        code = ip = f_->code.data();                                                                               \
        consts = f_->consts.data();                                                                                \
        if constexpr (OBS) obs->onCall(*this, f_, base, (int)(ARGC));                                              \
        TICK()                                                                                                     \
    }

#define ARITH(intop, op, slow)                                              \
    {                                                                       \
        Value& x = sp[-2];                                                  \
        Value& y = sp[-1];                                                  \
        if (x.tag == Value::Int && y.tag == Value::Int) {                   \
            int64_t r;                                                      \
            if (!intop(x.i, y.i, &r)) {                                     \
                x.i = r;                                                    \
                --sp;                                                       \
                break;                                                      \
            }                                                               \
        } else if (x.tag == Value::Float && y.tag == Value::Float) {        \
            x.n = x.n op y.n;                                               \
            --sp;                                                           \
            break;                                                          \
        }                                                                   \
        SYNC();                                                             \
        Value r = slow(x, y);                                               \
        --sp;                                                               \
        sp->clear();                                                        \
        sp[-1] = std::move(r);                                              \
    }                                                                       \
    break;

#define SLOWOP(slow)                    \
    {                                   \
        SYNC();                         \
        Value r = slow(sp[-2], sp[-1]); \
        --sp;                           \
        sp->clear();                    \
        sp[-1] = std::move(r);          \
    }                                   \
    break;

#define COMPARE(op)                                                                    \
    {                                                                                  \
        Value& x = sp[-2];                                                             \
        Value& y = sp[-1];                                                             \
        bool r;                                                                        \
        if constexpr (OBS) obs->onCompare();                                           \
        if (x.tag == Value::Int && y.tag == Value::Int) r = x.i op y.i;                \
        else if (x.tag == Value::Float && y.tag == Value::Float) r = x.n op y.n;       \
        else {                                                                         \
            int c = compareValues(x, y);                                               \
            r = c != 2 && c op 0;                                                      \
        }                                                                              \
        --sp;                                                                          \
        sp->clear();                                                                   \
        sp[-1] = Value::boolean(r);                                                    \
    }                                                                                  \
    break;

template <bool OBS>
inline Value VM::executeT(Value* sp, uint32_t nargs, size_t stopDepth) {
    Value* entrySp = sp - nargs - 1;
    Value* base = entrySp;
    Func* fn = frames.empty() ? nullptr : frames.back().fn;
    Closure* cl = frames.empty() ? nullptr : frames.back().cl;
    const uint32_t* code = fn ? fn->code.data() : nullptr;
    const uint32_t* ip = code;
    const Value* consts = fn ? fn->consts.data() : nullptr;
    Value* globals = prog.gvals.data();
    int budget = 2048;
    uint32_t n = nargs;
    bool starting = true;

    for (;;) {
        try {
            for (;;) {
                uint32_t ins, a;
                if (starting) {
                    starting = false;
                    ins = (uint32_t)OP_CALL | (nargs << 8);
                } else {
                    ins = *ip++;
                    if constexpr (OBS) obs->tick(*this, fn, (size_t)(ip - 1 - code), ins, sp);
                }
                a = ins >> 8;
                switch (ins & 0xFF) {
                    case OP_CONST: *sp++ = consts[a]; break;
                    case OP_NOTHING: *sp++ = Value(); break;
                    case OP_TRUE: *sp++ = Value::boolean(true); break;
                    case OP_FALSE: *sp++ = Value::boolean(false); break;
                    case OP_POP: (--sp)->clear(); break;
                    case OP_DUP2:
                        sp[0] = sp[-2];
                        sp[1] = sp[-1];
                        sp += 2;
                        break;
                    case OP_SWAP: std::swap(sp[-1], sp[-2]); break;
                    case OP_GETL: *sp++ = base[a]; break;
                    case OP_SETL:
                        base[a] = std::move(*--sp);
                        if constexpr (OBS) obs->onSetLocal(*this, a);
                        break;
                    case OP_GETG: {
                        const Value& g = globals[a];
                        if (g.tag == Value::Undef) unknownName(fn, a, false);
                        *sp++ = g;
                        break;
                    }
                    case OP_GETFN: {
                        const Value& g = globals[a];
                        if (g.tag == Value::Undef) unknownName(fn, a, true);
                        *sp++ = g;
                        break;
                    }
                    case OP_SETG: globals[a] = std::move(*--sp); break;
                    case OP_GETU: *sp++ = *UPVAL(a)->slot; break;
                    case OP_SETU: *UPVAL(a)->slot = std::move(*--sp); break;
                    case OP_CLOSURE: {
                        Func* f = static_cast<Func*>(consts[a].o);
                        Closure* c = new Closure(f);
                        Value cv = Value::obj(c);
                        for (size_t k = 0; k < f->upvals.size(); ++k) {
                            uint32_t w = *ip++;
                            if (w >> 31) c->ups.push_back(capture(base + (w & 0x7FFFFFFF)));
                            else c->ups.push_back(cl->ups[w & 0x7FFFFFFF]);
                        }
                        *sp++ = std::move(cv);
                        break;
                    }

                    case OP_ADD: ARITH(__builtin_add_overflow, +, addValues)
                    case OP_SUB: ARITH(__builtin_sub_overflow, -, subValues)
                    case OP_MUL: ARITH(__builtin_mul_overflow, *, mulValues)
                    case OP_DIV: {
                        Value& x = sp[-2];
                        Value& y = sp[-1];
                        if (x.tag == Value::Float && y.tag == Value::Float && y.n != 0) {
                            x.n /= y.n;
                            --sp;
                            break;
                        }
                    }
                        SLOWOP(divValues)
                    case OP_MOD: {
                        Value& x = sp[-2];
                        Value& y = sp[-1];
                        if (x.tag == Value::Int && y.tag == Value::Int && y.i > 0) {
                            int64_t r = x.i % y.i;
                            x.i = r < 0 ? r + y.i : r;
                            --sp;
                            break;
                        }
                    }
                        SLOWOP(modValues)
                    case OP_POW: SLOWOP(powValues)
                    case OP_NEG:
                        if (!isNumber(sp[-1])) fail(std::string("I can only put a minus sign before a number, but I got ") + describe(sp[-1]) + ".");
                        sp[-1] = numNeg(sp[-1]);
                        break;
                    case OP_NOT: sp[-1] = Value::boolean(!truthy(sp[-1])); break;

                    case OP_EQ: {
                        if constexpr (OBS) obs->onCompare();
                        bool r = equals(sp[-2], sp[-1]);
                        --sp;
                        sp->clear();
                        sp[-1] = Value::boolean(r);
                        break;
                    }
                    case OP_NE: {
                        if constexpr (OBS) obs->onCompare();
                        bool r = !equals(sp[-2], sp[-1]);
                        --sp;
                        sp->clear();
                        sp[-1] = Value::boolean(r);
                        break;
                    }
                    case OP_LT: COMPARE(<)
                    case OP_GT: COMPARE(>)
                    case OP_LE: COMPARE(<=)
                    case OP_GE: COMPARE(>=)
                    case OP_CONTAINS: {
                        SYNC();
                        bool r = containsValue(sp[-2], sp[-1]);
                        --sp;
                        sp->clear();
                        sp[-1] = Value::boolean(r);
                        break;
                    }

                    case OP_JUMP:
                        if (code + a < ip) TICK()
                        ip = code + a;
                        break;
                    case OP_JIF: {
                        --sp;
                        bool t = sp->tag == Value::Bool ? sp->b : truthy(*sp);
                        sp->clear();
                        if (!t) ip = code + a;
                        break;
                    }
                    case OP_AND:
                        if (!truthy(sp[-1])) ip = code + a;
                        else (--sp)->clear();
                        break;
                    case OP_OR:
                        if (truthy(sp[-1])) ip = code + a;
                        else (--sp)->clear();
                        break;

                    case OP_CALL:
                        n = a;
                    call_entry:
                        // The stack holds [callee][n values]. Keep unwrapping until it is something runnable.
                        for (;;) {
                            Value* callee = sp - n - 1;
                            if (callee->tag != Value::Object) fail(std::string("I can only call an action, but this is ") + describe(*callee) + ".");
                            Kind k = callee->o->kind;
                            if (k == Kind::Closure) {
                                Closure* c = static_cast<Closure*>(callee->o);
                                ENTER(c->fn, c, callee + 1, n, callee, false)
                                break;
                            }
                            if (k == Kind::Native) {
                                Native* nf = static_cast<Native*>(callee->o);
                                if (nf->arity >= 0 && (int)n != nf->arity)
                                    fail("'" + nf->name + "' needs " + std::to_string(nf->arity) + " value(s), but you gave it " + std::to_string(n) + ".");
                                SYNC();
                                Value r = nf->fn(*this, sp - n, (int)n);
                                for (Value* p = callee; p < sp; ++p) p->clear();
                                sp = callee;
                                *sp++ = std::move(r);
                                if (frames.size() == stopDepth) return std::move(*--sp);
                                break;
                            }
                            if (k == Kind::Bound) {
                                // The object takes the callee's place: it becomes 'me', the first value.
                                Bound* b = static_cast<Bound*>(callee->o);
                                Value self = b->self, method = b->method;
                                if (method.tag != Value::Object || method.o->kind != Kind::Closure) {
                                    *callee = std::move(method);
                                    continue;
                                }
                                Closure* c = static_cast<Closure*>(method.o);  // the object's class keeps it alive
                                *callee = std::move(self);
                                ENTER(c->fn, c, callee, n + 1, callee, false)
                                break;
                            }
                            if (k == Kind::Class) {
                                Class* c = static_cast<Class*>(callee->o);
                                Instance* in = new Instance;
                                Value iv = Value::obj(in);
                                in->cls = *callee;
                                in->fields = Value::obj(new Map);
                                const Value* init = c->findMethod("init");
                                if (init && init->tag == Value::Object && init->o->kind == Kind::Closure) {
                                    Closure* ic = static_cast<Closure*>(init->o);
                                    *callee = std::move(iv);  // the object takes the place of the class: it is 'me'
                                    ENTER(ic->fn, ic, callee, n + 1, callee, true)
                                    // the values were after the class; they now follow 'me' already
                                    break;
                                }
                                if (n != 0) fail("'" + c->name + "' has no 'init' action, so it can't be given values when it is made.");
                                *callee = std::move(iv);
                                if (frames.size() == stopDepth) return std::move(*--sp);
                                break;
                            }
                            fail(std::string("I can only call an action, but this is ") + describe(*callee) + ".");
                        }
                        break;
                    case OP_INVOKE: {
                        // The stack holds [object][n values].
                        uint32_t nameIdx = a >> 8;
                        n = a & 255;
                        Value* recv = sp - n - 1;
                        const Value& key = consts[nameIdx];
                        if (isInstance(*recv)) {
                            Instance* in = asInstance(*recv);
                            const Class* cls = asClass(in->cls);
                            size_t at = (size_t)(ip - 1 - code);
                            if (fn->caches.size() < fn->code.size()) fn->caches.resize(fn->code.size());
                            InlineCache& ic = fn->caches[at];
                            if (ic.cls == cls && ic.version == g_classVersion) {
                                Closure* c = ic.method;  // the class keeps it alive
                                ENTER(c->fn, c, recv, n + 1, recv, false)
                                break;
                            }
                            const Value* m = cls->findMethod(asStr(key));
                            if (m && m->tag == Value::Object && m->o->kind == Kind::Closure) {
                                Closure* c = static_cast<Closure*>(m->o);
                                ic.cls = cls;
                                ic.method = c;
                                ic.version = g_classVersion;
                                ENTER(c->fn, c, recv, n + 1, recv, false)
                                break;
                            }
                            if (!asMap(in->fields)->find(key)) noMember(in, key, true);
                        }
                        // Not a method: an action stored in a map entry or a field. Make the stack [callee][n values].
                        Value target = getIndex(*recv, key);
                        *recv = std::move(target);
                        goto call_entry;
                    }
                    case OP_GETSUPER: {
                        // [me][class] -> an action of the class's parent, remembered together with 'me'
                        Class* c = asClass(sp[-1]);
                        const Value* m = isClass(c->parent) ? asClass(c->parent)->findMethod(asStr(consts[a])) : nullptr;
                        if (!m) fail("The parent of '" + c->name + "' has no action called '" + asStr(consts[a]) + "'.");
                        Value bound = Value::obj(new Bound(sp[-2], *m));
                        (--sp)->clear();
                        sp[-1] = std::move(bound);
                        break;
                    }
                    case OP_RETURN: {
                        Value r = std::move(*--sp);
                        Frame fr = frames.back();
                        if (fr.ctor) r = *fr.base;
                        while (!handlers.empty() && handlers.back().depth == frames.size()) handlers.pop_back();
                        if (!openUps.empty()) closeUps(fr.base);
                        for (Value* p = fr.ret; p < sp; ++p) p->clear();
                        sp = fr.ret;
                        frames.pop_back();
                        if (frames.size() == stopDepth) return r;
                        *sp++ = std::move(r);
                        Frame& f = frames.back();
                        fn = f.fn;
                        cl = f.cl;
                        code = fn->code.data();
                        consts = fn->consts.data();
                        ip = f.ip;
                        base = f.base;
                        break;
                    }

                    case OP_FRESH: {
                        uint32_t to = *ip++;
                        if (!openUps.empty()) closeRange(base + a, base + to);
                        break;
                    }
                    case OP_CLASS:
                        ++g_classVersion;
                        *sp++ = Value::obj(new Class(asStr(consts[a])));
                        break;
                    case OP_INHERIT: {
                        if (!isClass(sp[-1])) fail(std::string("A class can only extend another class, but I got ") + describe(sp[-1]) + ".");
                        Class* child = asClass(sp[-2]);
                        for (const Class* p = asClass(sp[-1]);;) {
                            if (p == child) fail("A class can't extend itself.");
                            if (!isClass(p->parent)) break;
                            p = asClass(p->parent);
                        }
                        child->parent = sp[-1];
                        ++g_classVersion;
                        (--sp)->clear();
                        (--sp)->clear();
                        break;
                    }
                    case OP_DEFMETHOD: {
                        asClass(sp[-2])->methods[asStr(consts[a])] = sp[-1];
                        ++g_classVersion;
                        (--sp)->clear();
                        (--sp)->clear();
                        break;
                    }

                    case OP_NEWLIST: *sp++ = Value::obj(new List); break;
                    case OP_APPEND:
                        asList(sp[-2])->items.push_back(std::move(sp[-1]));
                        --sp;
                        break;
                    case OP_NEWMAP: *sp++ = Value::obj(new Map); break;
                    case OP_MAPPUT:
                        asMap(sp[-3])->set(sp[-2], sp[-1]);
                        (--sp)->clear();
                        (--sp)->clear();
                        break;
                    case OP_GETIDX: {
                        SYNC();
                        Value r = getIndex(sp[-2], sp[-1]);
                        if constexpr (OBS) obs->onRead(sp[-2], sp[-1]);
                        --sp;
                        sp->clear();
                        sp[-1] = std::move(r);
                        break;
                    }
                    case OP_SETIDX:
                        if constexpr (OBS) obs->onWrite(sp[-3], sp[-2], sp[-1]);
                        setIndex(sp[-3], sp[-2], sp[-1]);
                        (--sp)->clear();
                        (--sp)->clear();
                        (--sp)->clear();
                        break;
                    case OP_LENGTH: sp[-1] = Value::integer(lengthOf(sp[-1])); break;

                    case OP_SAY: {
                        SYNC();
                        std::string out;
                        for (Value* p = sp - a; p < sp; ++p) {
                            if (p != sp - a) out += ' ';
                            out += fmt(*p);
                        }
                        out += '\n';
                        if constexpr (OBS) {
                            if (obs->capture) obs->output(out);
                            else fwrite(out.data(), 1, out.size(), stdout);
                        } else {
                            fwrite(out.data(), 1, out.size(), stdout);
                        }
                        for (uint32_t i = 0; i < a; ++i) (--sp)->clear();
                        break;
                    }
                    case OP_ASK: {
                        SYNC();
                        std::string prompt = fmt(sp[-1]);
                        if (!prompt.empty()) {
                            if constexpr (OBS) {
                                if (obs->capture) obs->output(prompt + " ");
                                else { fputs(prompt.c_str(), stdout); fputc(' ', stdout); }
                            } else {
                                fputs(prompt.c_str(), stdout);
                                fputc(' ', stdout);
                            }
                        }
                        fflush(stdout);
                        std::string line;
                        {
                            Unlocked u;
                            if (!std::getline(std::cin, line)) line.clear();
                        }
                        sp[-1] = parseInput(line);
                        break;
                    }
                    case OP_ADDTO: {
                        SYNC();
                        Value& v = sp[-1];
                        Value& x = sp[-2 - (int)a];
                        if (isList(v)) asList(v)->items.push_back(x);
                        else if (isNumber(v) || isStr(v)) v = addValues(v, x);
                        else fail(std::string("I can only add to a number, text or a list, but I got ") + describe(v) + ".");
                        break;
                    }
                    case OP_REMOVE: {
                        Value& x = sp[-2];
                        Value& box = sp[-1];
                        if (isList(box)) {
                            auto& items = asList(box)->items;
                            size_t i = 0;
                            while (i < items.size() && !equals(items[i], x)) ++i;
                            if (i == items.size()) fail(fmt(x, true) + " isn't in the list, so I can't remove it. Check first with: if list contains " + fmt(x, true) + " then ...");
                            items.erase(items.begin() + (long)i);
                        } else if (isMap(box)) {
                            if (!asMap(box)->remove(x)) fail("This map has no entry called " + fmt(x, true) + ", so I can't remove it.");
                        } else {
                            fail(std::string("I can only remove things from a list or a map, but I got ") + describe(box) + ".");
                        }
                        (--sp)->clear();
                        (--sp)->clear();
                        break;
                    }

                    case OP_FORTEST: {
                        for (int k = 3; k >= 1; --k)
                            if (!isNumber(sp[-k])) fail(std::string("'for' counts with numbers, but I got ") + describe(sp[-k]) + ".");
                        if (isZeroNum(sp[-1])) fail("A 'for' loop can't count 'by 0' - it would never finish.");
                        int c = numCompare(sp[-3], sp[-2]);
                        bool up = numCompare(sp[-1], Value::integer(0)) > 0;
                        bool done = c == 2 || (up ? c > 0 : c < 0);
                        sp -= 3;
                        sp[0].clear();
                        sp[1].clear();
                        sp[2].clear();
                        if (done) ip = code + a;
                        break;
                    }
                    case OP_FORL:
                    case OP_FORG: {
                        uint32_t w = *ip++;
                        Value& v = (ins & 0xFF) == OP_FORL ? base[a] : globals[a];
                        const Value& limit = base[w & 0xFF];
                        const Value& step = base[(w & 0xFF) + 1];
                        // The counter only moves on if there is another round, so after the loop
                        // it holds the last number counted ('for i from 1 to 3' leaves i at 3).
                        bool again;
                        int64_t nv;
                        if (v.tag == Value::Int && step.tag == Value::Int && limit.tag == Value::Int &&
                            !__builtin_add_overflow(v.i, step.i, &nv)) {
                            again = step.i > 0 ? nv <= limit.i : nv >= limit.i;
                            if (again) v.i = nv;
                        } else {
                            if (!isNumber(v))
                                fail(std::string("The counter of a 'for' loop must stay a number, but it became ") + describe(v) + ".");
                            Value next = numAdd(v, step);
                            int c = numCompare(next, limit);
                            bool up = numCompare(step, Value::integer(0)) > 0;
                            again = c != 2 && (up ? c <= 0 : c >= 0);
                            if (again) v = std::move(next);
                        }
                        if (again) {
                            TICK()
                            ip = code + (w >> 8);
                        }
                        break;
                    }
                    case OP_ITERPREP: {
                        Value& it = sp[-1];
                        if (isStr(it)) {
                            List* l = new List;
                            Value lv = Value::obj(l);
                            for (std::string& c : u8chars(asStr(it))) l->items.push_back(mkstr(std::move(c)));
                            it = std::move(lv);
                        } else if (isMap(it)) {
                            List* l = new List;
                            Value lv = Value::obj(l);
                            for (const auto& e : asMap(it)->entries) l->items.push_back(e.first);
                            it = std::move(lv);
                        } else if (!isList(it)) {
                            fail(std::string("'for each' needs a list, text or a map to go through, but I got ") + describe(it) + ".");
                        }
                        base[a] = std::move(*--sp);
                        base[a + 1] = Value::integer(0);
                        break;
                    }
                    case OP_ITERNEXT: {
                        uint32_t target = *ip++;
                        List* l = asList(base[a]);
                        size_t i = (size_t)base[a + 1].i;
                        if (i >= l->items.size()) {
                            ip = code + target;
                        } else {
                            *sp++ = l->items[i];
                            base[a + 1].i = (int64_t)(i + 1);
                            TICK()
                        }
                        break;
                    }
                    case OP_REPPREP: {
                        if (!isNumber(sp[-1])) fail(std::string("'repeat' needs a number of times, but I got ") + describe(sp[-1]) + ".");
                        Value t = toInteger(sp[-1]);
                        int64_t times = t.tag == Value::Int ? t.i : (asBig(t).neg ? 0 : INT64_MAX);
                        base[a] = Value::integer(times);
                        (--sp)->clear();
                        break;
                    }
                    case OP_REPTEST: {
                        uint32_t target = *ip++;
                        if (base[a].i < 1) {
                            ip = code + target;
                        } else {
                            base[a].i -= 1;
                            TICK()
                        }
                        break;
                    }

                    case OP_TRY: handlers.push_back({frames.size(), sp, code + a}); break;
                    case OP_ENDTRY:
                        for (uint32_t i = 0; i < a && !handlers.empty(); ++i) handlers.pop_back();
                        break;
                    case OP_FAIL: SYNC(); fail(fmt(sp[-1]));
                    case OP_ECHO:
                        SYNC();
                        --sp;
                        if (sp->tag != Value::Nothing) printf("%s\n", fmt(*sp, true).c_str());
                        sp->clear();
                        break;
                    default: fail("Something went wrong inside Plain itself (unknown instruction).");
                }
            }
        } catch (PlainError& e) {
            if constexpr (OBS) obs->onError(*this, e);
            bool inside = frames.size() > stopDepth && fn;
            if (e.line == 0 && inside) {
                size_t at = (size_t)(ip - code);
                at = at ? at - 1 : 0;
                if (at < fn->lines.size()) e.line = fn->lines[at];
                e.file = fn->file;
            }
            if (e.fatal || handlers.empty() || handlers.back().depth <= stopDepth) {
                closeUps(entrySp);
                for (Value* p = entrySp; p < sp; ++p) p->clear();
                frames.resize(std::min(frames.size(), stopDepth));
                if constexpr (OBS) obs->onUnwind(*this);
                throw;
            }
            // A 'try' is waiting: unwind to it and hand it the message.
            Handler h = handlers.back();
            handlers.pop_back();
            while (frames.size() > h.depth) frames.pop_back();
            if constexpr (OBS) obs->onUnwind(*this);
            closeUps(h.sp);
            for (Value* p = h.sp; p < sp; ++p) p->clear();
            sp = h.sp;
            *sp++ = mkstr(e.msg);
            Frame& f = frames.back();
            fn = f.fn;
            cl = f.cl;
            code = fn->code.data();
            consts = fn->consts.data();
            base = f.base;
            ip = h.target;
        }
    }
}

#undef UPVAL
#undef TICK
#undef SYNC
#undef ENTER
#undef ARITH
#undef SLOWOP
#undef COMPARE

}  // namespace plain
