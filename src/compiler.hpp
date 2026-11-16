// Plain - stage 2: compile tokens straight into bytecode.
#pragma once
#include <unordered_set>

#include "lexer.hpp"
#include "numeric.hpp"
#include "modules.hpp"

namespace plain {

// One instruction is a 32-bit word: the low 8 bits are the operation,
// the high 24 bits are its operand. A few "wide" operations use a second word.
#define PLAIN_OPS(X)                                                                                         \
    X(CONST, "CONST") X(NOTHING, "NOTHING") X(TRUE, "TRUE") X(FALSE, "FALSE") X(POP, "POP")                 \
    X(DUP2, "DUP2") X(SWAP, "SWAP") X(GETL, "GET_LOCAL") X(SETL, "SET_LOCAL") X(GETU, "GET_CAPTURED")      \
    X(SETU, "SET_CAPTURED") X(GETG, "GET_GLOBAL") X(GETFN, "GET_ACTION") X(SETG, "SET_GLOBAL")             \
    X(ADD, "ADD") X(SUB, "SUBTRACT") X(MUL, "MULTIPLY") X(DIV, "DIVIDE") X(MOD, "MODULO")                  \
    X(POW, "POWER") X(NEG, "NEGATE") X(NOT, "NOT") X(EQ, "EQUAL") X(NE, "NOT_EQUAL") X(LT, "LESS")         \
    X(GT, "GREATER") X(LE, "AT_MOST") X(GE, "AT_LEAST") X(CONTAINS, "CONTAINS") X(JUMP, "JUMP")            \
    X(JIF, "JUMP_IF_FALSE") X(AND, "AND") X(OR, "OR") X(CALL, "CALL") X(INVOKE, "INVOKE")                  \
    X(RETURN, "RETURN") X(CLOSURE, "CLOSURE") X(NEWLIST, "NEW_LIST") X(APPEND, "APPEND")                    \
    X(NEWMAP, "NEW_MAP") X(MAPPUT, "MAP_PUT") X(GETIDX, "GET_ITEM") X(SETIDX, "SET_ITEM")                   \
    X(LENGTH, "LENGTH") X(SAY, "SAY") X(ASK, "ASK") X(ADDTO, "ADD_TO") X(REMOVE, "REMOVE_FROM")           \
    X(FORTEST, "FOR_TEST") X(ITERPREP, "EACH_START") X(ITERNEXT, "EACH_NEXT") X(REPPREP, "REPEAT_START")   \
    X(REPTEST, "REPEAT_NEXT") X(TRY, "TRY") X(ENDTRY, "END_TRY") X(FAIL, "FAIL") X(ECHO, "ECHO")           \
    X(FORL, "FOR_NEXT_LOCAL") X(FORG, "FOR_NEXT_GLOBAL") X(CLASS, "NEW_CLASS") X(INHERIT, "INHERIT")       \
    X(DEFMETHOD, "DEFINE_ACTION") X(GETSUPER, "GET_PARENT_ACTION") X(FRESH, "FRESH_VARIABLES")

enum Op : uint8_t {
#define X(name, text) OP_##name,
    PLAIN_OPS(X)
#undef X
};

inline const char* opName(int op) {
    static const char* names[] = {
#define X(name, text) text,
        PLAIN_OPS(X)
#undef X
    };
    return names[op];
}

inline bool isWide(int op) { return op == OP_ITERNEXT || op == OP_REPTEST || op == OP_FORL || op == OP_FORG || op == OP_FRESH; }

// Everything that outlives a single compile: global variables, actions and
// the source files that were loaded.
struct Program {
    static const size_t MAX_GLOBALS = 65536;
    std::unordered_map<std::string, int> gslot;
    std::vector<std::string> gnames;
    std::vector<Value> gvals;
    std::vector<uint8_t> gdeclared;  // set by the user's own top-level code
    std::vector<Value> funcs;        // every compiled action, for --explain
    std::unordered_set<std::string> used;
    std::unordered_map<std::string, std::string> embedded;                // sources bundled by "plain build"
    std::unordered_map<std::string, std::string> resolved;                // "file\nname" -> path, remembered for builds
    std::vector<std::pair<std::string, std::string>> sources;             // files loaded with "use"

    // gvals never moves: running threads keep pointers into it.
    Program() { gvals.reserve(MAX_GLOBALS); }

    int slot(const std::string& name) {
        auto it = gslot.find(name);
        if (it != gslot.end()) return it->second;
        if (gnames.size() >= MAX_GLOBALS) fail("This program uses too many different names.");
        int s = (int)gnames.size();
        gslot.emplace(name, s);
        gnames.push_back(name);
        gvals.push_back(Value::undef());
        gdeclared.push_back(0);
        return s;
    }
    void define(const std::string& name, Value v) { gvals[(size_t)slot(name)] = std::move(v); }
};

class Compiler {
public:
    Compiler(Program& p, std::string source, std::string file, bool repl = false)
        : prog(p), src(std::move(source)), file(std::move(file)), repl(repl) {}

    // Compile the whole source into one action that runs the top-level code.
    Value compileMain() {
        try {
            toks = tokenize(src);
            Func* fn = new Func;
            Value fv = Value::obj(fn);
            FS top;
            top.fn = fn;
            fn->name = "main program";
            fn->file = file;
            top.isMain = true;
            fs = &top;
            for (;;) {
                skipNL();
                if (peek().k == Token::End) break;
                statement();
            }
            emit(OP_NOTHING);
            emit(OP_RETURN);
            checkDiscarded();
            return Value::obj(new Closure(fn));
        } catch (PlainError& e) {
            if (e.file.empty()) e.file = file;
            throw;
        }
    }

private:
    struct Loop {
        int contTarget = -1;  // known for loops whose "next round" point is at the top
        std::vector<int> conts, breaks;
        int tryDepth = 0;
    };
    struct FS {  // state of the action being compiled
        Func* fn = nullptr;
        FS* enclosing = nullptr;
        std::unordered_map<std::string, int> locals;
        std::unordered_map<std::string, int> strConsts, numConsts;
        bool isMain = false;
        std::vector<Loop> loops;
        int tryDepth = 0;
        bool isMethod = false;
        std::string className;
        bool classHasParent = false;
    };
    struct Target {
        bool index = false;
        std::string name;
    };

    Program& prog;
    std::string src, file;
    bool repl;
    std::vector<Token> toks;
    size_t pos = 0;
    int curLine = 1;
    int depth = 0;
    int nlBase = 0;     // newlines inside more brackets than this don't end a statement
    int lastCall = -1;  // code index of the most recent call instruction
    FS* fs = nullptr;
    // Lines like "sort(xs)" whose answer is thrown away. Checked once the whole program
    // is known, because the program may define its own action with that name further down.
    struct Discarded { std::string name, arg; int line; };
    std::vector<Discarded> discarded;

    // ------------------------------------------------------------ tokens
    bool soft(const Token& t) const { return t.k == Token::NL && t.depth > nlBase; }
    size_t at(size_t k) const {
        size_t i = pos, last = toks.size() - 1;
        for (;;) {
            while (i < last && soft(toks[i])) ++i;
            if (k == 0) return i;
            --k;
            if (i < last) ++i;
        }
    }
    const Token& peek(size_t k = 0) const { return toks[at(k)]; }
    const Token& next() {
        pos = at(0);
        const Token& t = toks[pos];
        if (pos < toks.size() - 1) ++pos;
        curLine = t.line;
        return t;
    }
    bool kw(const char* w, size_t k = 0) const { return peek(k).k == Token::Kw && peek(k).text == w; }
    bool sym(const char* s, size_t k = 0) const { return peek(k).k == Token::Sym && peek(k).text == s; }
    bool word(const char* w, size_t k = 0) const { return peek(k).k == Token::Word && peek(k).text == w; }
    bool acceptKw(const char* w) { if (kw(w)) { next(); return true; } return false; }
    bool acceptSym(const char* s) { if (sym(s)) { next(); return true; } return false; }
    bool atEnd() const { return peek().k == Token::NL || peek().k == Token::End; }
    void skipNL() { while (peek().k == Token::NL) next(); }

    static std::string show(const Token& t) {
        switch (t.k) {
            case Token::NL: return "the end of the line";
            case Token::End: return "the end of the program";
            case Token::Str: return quote(t.text);
            default: return "'" + t.text + "'";
        }
    }
    [[noreturn]] void err(const std::string& msg, int line = 0) {
        PlainError e;
        e.msg = msg;
        e.line = line ? line : peek().line;
        e.incomplete = peek().k == Token::End;  // ran out of program: the interactive session can ask for more
        throw e;
    }
    [[noreturn]] void neverClosed(const char* what, int openLine) {
        PlainError e;
        e.msg = std::string("The '") + what + "' that starts on line " + std::to_string(openLine) +
                " is never closed. Add 'end' after its last line.";
        e.line = openLine;
        e.incomplete = true;
        throw e;
    }

    void expectKw(const char* w, const char* context) {
        if (!acceptKw(w)) err(std::string("I expected '") + w + "' " + context + ", but found " + show(peek()) + ".");
    }
    void expectSym(const char* s, const char* context) {
        if (!acceptSym(s)) err(std::string("I expected '") + s + "' " + context + ", but found " + show(peek()) + ".");
    }
    // What a reserved word is for, and what to call a variable instead.
    static std::string reservedHelp(const std::string& w) {
        static const std::unordered_map<std::string, std::pair<const char*, const char*>> info = {
            {"item", {"'item 2 of list'", "'entry' or 'thing'"}}, {"times", {"'repeat 3 times'", "'count' or 'rounds'"}},
            {"length", {"'length of list'", "'size' or 'total'"}}, {"set", {"'set x to 5'", "'group' or 'values'"}},
            {"to", {"'set x to 5'", "'target' or 'destination'"}}, {"from", {"'for i from 1 to 5'", "'source' or 'start'"}},
            {"by", {"'increase x by 1'", "'step' or 'amount'"}}, {"of", {"'item 2 of list'", "'owner'"}},
            {"in", {"'for each x in list'", "'inside'"}}, {"into", {"'ask \"Name?\" into name'", "'inside'"}},
            {"end", {"closing a block", "'last' or 'finish'"}}, {"back", {"'give back x'", "'behind' or 'previous'"}},
            {"give", {"'give back x'", "'gift'"}}, {"each", {"'for each x in list'", "'every'"}},
            {"add", {"'add x to list'", "'addition' or 'total'"}}, {"remove", {"'remove x from list'", "'removed'"}},
            {"at", {"'is at least'", "'place'"}}, {"most", {"'is at most'", "'biggest'"}}, {"least", {"'is at least'", "'smallest'"}},
            {"less", {"'is less than'", "'fewer'"}}, {"greater", {"'is greater than'", "'bigger'"}}, {"than", {"'is less than'", "'other'"}},
            {"equal", {"'is equal to'", "'same'"}}, {"contains", {"'list contains x'", "'has_it'"}},
            {"new", {"'new Dog()'", "'fresh'"}}, {"me", {"'me' inside a class", "'myself' or 'this_one'"}},
            {"parent", {"'parent' inside a class", "'parent_node' or 'above'"}}, {"action", {"'action with x gives ...'", "'task' or 'step'"}},
            {"stop", {"leaving a loop", "'halt'"}}, {"skip", {"going to the next round", "'jump'"}},
            {"say", {"showing a value", "'message'"}}, {"show", {"showing a value", "'display'"}}, {"print", {"showing a value", "'output'"}},
            {"ask", {"asking the user", "'question'"}}, {"if", {"'if x then'", "'condition'"}}, {"then", {"'if x then'", "'next_step'"}},
            {"otherwise", {"'otherwise' in an if", "'else_case'"}}, {"repeat", {"'repeat 3 times'", "'again'"}},
            {"while", {"'while x'", "'during'"}}, {"for", {"'for each' and 'for i from'", "'purpose'"}},
            {"define", {"making an action", "'definition'"}}, {"with", {"'define f with x'", "'using'"}},
            {"class", {"making a class", "'kind' or 'category'"}}, {"extends", {"'class A extends B'", "'grows'"}},
            {"gives", {"'action with x gives ...'", "'result'"}}, {"true", {"the value true", "'yes_value'"}},
            {"false", {"the value false", "'no_value'"}}, {"nothing", {"the empty value", "'empty'"}},
            {"is", {"comparing values", "'same'"}}, {"not", {"'not x'", "'negated'"}}, {"and", {"'a and b'", "'both'"}},
            {"or", {"'a or b'", "'either'"}}, {"plus", {"'a plus b'", "'bonus'"}}, {"minus", {"'a minus b'", "'penalty'"}},
            {"multiplied", {"'a multiplied by b'", "'product'"}}, {"divided", {"'a divided by b'", "'share'"}},
            {"modulo", {"'a modulo b'", "'remainder'"}}, {"increase", {"'increase x by 1'", "'growth'"}},
            {"decrease", {"'decrease x by 1'", "'shrink'"}},
        };
        auto it = info.find(w);
        if (it == info.end()) return "'" + w + "' is a word Plain uses itself, so it can't be used as a name. Try a different name, like 'my_" + w + "'.";
        return "'" + w + "' is a reserved word: Plain uses it in " + it->second.first + ", so it can't also be a name. Pick another name, such as " +
               it->second.second + " (or 'my_" + w + "').";
    }
    std::string expectName(const char* context) {
        const Token& t = peek();
        if (t.k == Token::Word) return next().text;
        if (t.k == Token::Kw) err(reservedHelp(t.text));
        err(std::string("I expected a name ") + context + ", but found " + show(t) + ".");
    }
    void endOfStatement() {
        if (peek().k == Token::NL) { next(); return; }
        if (peek().k == Token::End) return;
        err("I didn't expect " + show(peek()) + " here.");
    }

    // -------------------------------------------------------------- code
    int here() const { return (int)fs->fn->code.size(); }
    int emit(Op op, int a = 0) {
        fs->fn->code.push_back((uint32_t)op | ((uint32_t)a << 8));
        fs->fn->lines.push_back(curLine);
        return here() - 1;
    }
    int emitWide(Op op, int a) {
        int at = emit(op, a);
        fs->fn->code.push_back(0);
        fs->fn->lines.push_back(curLine);
        return at;
    }
    void emitCall(Op op, int a) {
        emit(op, a);
        lastCall = here() - 1;
    }
    void patch(int at) { fs->fn->code[(size_t)at] = (fs->fn->code[(size_t)at] & 0xFF) | ((uint32_t)here() << 8); }
    void patchWide(int at) { fs->fn->code[(size_t)at + 1] = (uint32_t)here(); }

    int addConst(Value v) {
        fs->fn->consts.push_back(std::move(v));
        return (int)fs->fn->consts.size() - 1;
    }
    int strConst(const std::string& s) {
        auto it = fs->strConsts.find(s);
        if (it != fs->strConsts.end()) return it->second;
        int idx = addConst(mkstr(s));
        fs->strConsts.emplace(s, idx);
        return idx;
    }
    void emitStr(const std::string& s) { emit(OP_CONST, strConst(s)); }
    void emitNumber(const Token& t, bool negate) {
        std::string key = std::to_string(t.numKind) + (negate ? "-" : "+") + t.text;
        auto it = fs->numConsts.find(key);
        if (it != fs->numConsts.end()) { emit(OP_CONST, it->second); return; }
        int idx = addConst(numberLiteral(t.text, t.numKind, negate));
        fs->numConsts.emplace(key, idx);
        emit(OP_CONST, idx);
    }
    int nameOperand(const std::string& name) {
        int idx = strConst(name);
        if (idx >= 65536) err("This action uses too many different names.");
        return idx;
    }

    int newLocal(const std::string& name) {
        int s = fs->fn->nlocals++;
        fs->fn->localNames.push_back(name);
        if (!name.empty()) fs->locals[name] = s;
        return s;
    }

    // Find a variable of an enclosing action and capture it.
    int addUpvalue(FS* f, bool isLocal, int index) {
        auto& ups = f->fn->upvals;
        for (size_t i = 0; i < ups.size(); ++i)
            if (ups[i].isLocal == isLocal && ups[i].index == (uint32_t)index) return (int)i;
        if (ups.size() >= 16000000) err("This action uses too many variables of the actions around it.");
        ups.push_back({isLocal, (uint32_t)index});
        return (int)ups.size() - 1;
    }
    int resolveUpvalue(FS* f, const std::string& name) {
        FS* p = f->enclosing;
        if (!p) return -1;
        auto it = p->locals.find(name);
        if (it != p->locals.end()) return addUpvalue(f, true, it->second);
        int idx = resolveUpvalue(p, name);
        if (idx >= 0) return addUpvalue(f, false, idx);
        return -1;
    }

    void loadName(const std::string& name, bool forCall = false) {
        auto it = fs->locals.find(name);  // (the top level only has these for loop counters used by closures)
        if (it != fs->locals.end()) { emit(OP_GETL, it->second); return; }
        int u = resolveUpvalue(fs, name);
        if (u >= 0) { emit(OP_GETU, u); return; }
        emit(forCall ? OP_GETFN : OP_GETG, prog.slot(name));
    }
    // Where a 'set' writes: at the top level, a global. Inside an action: its own
    // variable, or one of an action around it, or a global the top-level code
    // already created - and otherwise a new variable of this action.
    void storeName(const std::string& name, bool forceLocal = false) {
        if (fs->isMain) {
            auto own = fs->locals.find(name);
            if (own != fs->locals.end()) { emit(OP_SETL, own->second); return; }
            if (!forceLocal) {
                int u = resolveUpvalue(fs, name);
                if (u >= 0) { emit(OP_SETU, u); return; }
            }
            int s = prog.slot(name);
            prog.gdeclared[(size_t)s] = 1;
            emit(OP_SETG, s);
            return;
        }
        auto it = fs->locals.find(name);
        if (it != fs->locals.end()) { emit(OP_SETL, it->second); return; }
        if (!forceLocal) {
            int u = resolveUpvalue(fs, name);
            if (u >= 0) { emit(OP_SETU, u); return; }
            auto g = prog.gslot.find(name);
            if (g != prog.gslot.end() && prog.gdeclared[(size_t)g->second]) { emit(OP_SETG, g->second); return; }
        }
        emit(OP_SETL, newLocal(name));
    }

    bool inMethod() const { return methodContext() != nullptr; }
    FS* methodContext() const {
        for (FS* f = fs; f; f = f->enclosing)
            if (f->isMethod) return f;
        return nullptr;
    }

    // Parse the thing being changed: a name, 'item i of xs', xs[i] or person's field.
    Target target() {
        Target t;
        if (kw("item") && !kw("to", 1) && !kw("by", 1)) {
            next();
            additive();
            expectKw("of", "after the item number");
            postfix();
            emit(OP_SWAP);
            t.index = true;
            return t;
        }
        if (kw("me")) {
            next();
            if (!inMethod()) err("'me' only works inside an action of a class.", curLine);
            t.name = "me";
            if (!(sym("[") || peek().k == Token::Poss)) err("'me' can't be changed. Did you mean something like: me's name", curLine);
        } else {
            t.name = expectName("here");
        }
        if (sym("[") || peek().k == Token::Poss) {
            loadName(t.name);
            for (;;) {
                accessorKey();
                if (sym("[") || peek().k == Token::Poss) emit(OP_GETIDX);
                else break;
            }
            t.index = true;
        }
        return t;
    }
    void accessorKey() {
        if (acceptSym("[")) {
            expression();
            expectSym("]", "to close the '['");
        } else {
            next();  // 's
            const Token& t = peek();
            if (t.k != Token::Word && t.k != Token::Kw) err("I expected a name after 's, but found " + show(t) + ".");
            emitStr(next().text);
        }
    }
    void loadTarget(const Target& t) {
        if (t.index) { emit(OP_DUP2); emit(OP_GETIDX); }
        else loadName(t.name);
    }
    void store(const Target& t) {
        if (t.index) emit(OP_SETIDX);
        else storeName(t.name);
    }

    // -------------------------------------------------------- statements
    void statement() {
        const Token& t = peek();
        if (t.k == Token::Kw) {
            const std::string& w = t.text;
            if (w == "set") return setStmt();
            if (w == "say" || w == "show" || w == "print") return sayStmt();
            if (w == "ask") return askStmt();
            if (w == "add") return addStmt();
            if (w == "remove") return removeStmt();
            if (w == "increase" || w == "decrease") return changeStmt(w == "increase");
            if (w == "if") return ifStmt();
            if (w == "repeat") return repeatStmt();
            if (w == "while") return whileStmt();
            if (w == "for") return forStmt();
            if (w == "define") return defineStmt();
            if (w == "class") return classStmt();
            if (w == "give") return giveStmt();
            if (w == "stop" || w == "skip") return jumpStmt(w == "stop");
            if (w == "end") err("There is an 'end' here, but nothing is open for it to close.");
            if (w == "otherwise") err("'otherwise' only works inside an 'if'.");
            if (!(w == "true" || w == "false" || w == "nothing" || w == "not" || w == "length" || w == "item" ||
                  w == "me" || w == "parent" || w == "new" || w == "action"))
                err("A line can't start with '" + w + "'.");
        }
        if (t.k == Token::Word) {
            const std::string& w = t.text;
            if (w == "try" && peek(1).k == Token::NL) return tryStmt();
            if (w == "fail" && kw("with", 1)) return failStmt();
            if (w == "use" && peek(1).k == Token::Str) return useStmt();
            if (w == "call" && peek(1).k == Token::Word) return callStmt();
            if (w == "on" && word("error", 1)) err("'on error' only works inside a 'try'.");
            const Token& n = peek(1);
            bool looksLikeStore = (n.k == Token::Sym && n.text == "=") ||
                                  (!repl && n.k == Token::Kw && n.text == "is" && peek(2).k != Token::Kw);
            if (looksLikeStore)
                err("To keep a value in '" + w + "', start the line with 'set', like: set " + w + " to 5");
            bool exprLike = (n.k == Token::Sym && n.text != "{") || n.k == Token::Poss ||
                            (repl && (n.k == Token::NL || n.k == Token::End || n.k == Token::Kw));
            if (!exprLike) unknownInstruction(w);
        }
        exprStatement();
    }

    [[noreturn]] void unknownInstruction(const std::string& w) {
        static const std::pair<const char*, const char*> hints[] = {
            {"else", "otherwise"}, {"elif", "otherwise if"}, {"elseif", "otherwise if"},
            {"return", "give back"}, {"function", "define"}, {"def", "define"}, {"func", "define"},
            {"break", "stop"}, {"continue", "skip"}, {"let", "set"}, {"var", "set"},
            {"echo", "say"}, {"input", "ask"}, {"import", "use"}, {"throw", "fail with"}, {"catch", "on error"},
            {"lambda", "action"}, {"this", "me"}, {"self", "me"}, {"super", "parent"},
        };
        std::string lower = w;
        for (char& c : lower) c = (char)tolower((unsigned char)c);
        for (const auto& h : hints)
            if (lower == h.first) err("Plain says '" + std::string(h.second) + "' instead of '" + w + "'.");
        std::vector<std::string> words = {"set", "say", "show", "print", "ask", "add", "remove", "increase",
                                          "decrease", "if", "repeat", "while", "for", "define", "class", "give",
                                          "stop", "skip", "try", "fail", "use", "call"};
        std::string c = closest(lower, words);
        err("I don't know the instruction '" + w + "'." + (c.empty() ? " A line starts with a word like 'set', 'say' or 'if'." : " Did you mean '" + c + "'?"));
    }

    void exprStatement() {
        int line = peek().line;
        size_t start = at(0);
        expression();
        if (repl && fs->isMain) {
            emit(OP_ECHO);
        } else {
            if (lastCall != here() - 1)
                err("This line works out a value but does nothing with it. Start it with 'say' to show it, or 'set ... to' to keep it.", line);
            noteDiscardedCall(start, line);
            emit(OP_POP);
        }
        endOfStatement();
    }

    // The whole line is "name(...)" with a global name: remember it, in case that is a
    // built-in action that only gives back an answer (like sort), which would be lost.
    void noteDiscardedCall(size_t start, int line) {
        if (toks[start].k != Token::Word || !(toks[start + 1].k == Token::Sym && toks[start + 1].text == "(")) return;
        const std::string& name = toks[start].text;
        if (fs->locals.count(name) || resolveUpvalue(fs, name) >= 0) return;
        size_t i = start + 1;
        for (int open = 0; i < toks.size(); ++i) {
            const Token& t = toks[i];
            if (t.k == Token::Sym && (t.text == "(" || t.text == "[" || t.text == "{")) ++open;
            else if (t.k == Token::Sym && (t.text == ")" || t.text == "]" || t.text == "}") && --open == 0) break;
        }
        if (at(0) != i + 1) return;  // more follows the ')', like sort(xs)[1]
        bool simpleArg = toks[start + 2].k == Token::Word && toks[start + 3].k == Token::Sym &&
                         (toks[start + 3].text == ")" || toks[start + 3].text == ",");
        discarded.push_back({name, simpleArg ? toks[start + 2].text : "", line});
    }

    // Built-in actions that only give back an answer. Calling one on a line of its own does nothing.
    void checkDiscarded() {
        static const std::unordered_set<std::string> oneValue = {"sort", "reverse", "copy", "uppercase", "lowercase", "trim"};
        static const std::unordered_set<std::string> changers = {
            "sort", "reverse", "sort_by", "map_each", "keep_if", "copy", "slice",
            "uppercase", "lowercase", "trim", "replace",
        };
        static const std::unordered_set<std::string> answers = {
            "sqrt", "abs", "floor", "ceiling", "round", "power", "sin", "cos", "tan", "exp", "log", "pi",
            "min", "max", "sum", "text", "number", "split", "join", "find", "starts_with", "ends_with",
            "range", "first", "last", "index_of", "keys", "values", "has_key", "type_of", "fraction", "whole",
            "integer", "float", "decimal", "quotient", "fixed", "is_integer", "is_float", "is_decimal",
            "is_a", "to_json", "from_json", "find_first", "combine", "url_encode", "url_decode",
        };
        for (const Discarded& d : discarded) {
            auto g = prog.gslot.find(d.name);
            if (g == prog.gslot.end() || prog.gdeclared[(size_t)g->second]) continue;  // the program's own action
            bool changer = changers.count(d.name) > 0;
            if (!changer && !answers.count(d.name)) continue;
            PlainError e;
            e.line = d.line;
            if (changer && !d.arg.empty())
                e.msg = "'" + d.name + "' gives back a new value and leaves " + d.arg + " as it was, so this line changes nothing. "
                        "Keep the answer: set " + d.arg + " to " + d.name + "(" + d.arg + (oneValue.count(d.name) ? "" : ", ...") + ")";
            else
                e.msg = "'" + d.name + "' gives back an answer, but this line does nothing with it. Show it with 'say', or keep it with 'set ... to'.";
            throw e;
        }
    }

    void setStmt() {
        next();
        Target t = target();
        expectKw("to", "after the name in 'set'");
        expression();
        store(t);
        endOfStatement();
    }

    void sayStmt() {
        next();
        int n = 0;
        if (!atEnd()) {
            do {
                expression();
                ++n;
            } while (acceptSym(","));
        }
        if (!atEnd()) err("Put a comma between the values to say, like: say \"Total:\", total");
        emit(OP_SAY, n);
        endOfStatement();
    }

    void askStmt() {
        next();
        if (kw("into")) emitStr("");
        else expression();
        expectKw("into", "after the question in 'ask'");
        std::string name = expectName("to keep the answer in");
        emit(OP_ASK);
        storeName(name);
        endOfStatement();
    }

    void addStmt() {
        next();
        expression();
        expectKw("to", "in 'add ... to ...'");
        Target t = target();
        loadTarget(t);
        emit(OP_ADDTO, t.index ? 2 : 0);
        store(t);
        emit(OP_POP);
        endOfStatement();
    }

    void removeStmt() {
        next();
        expression();
        expectKw("from", "in 'remove ... from ...'");
        postfix();
        emit(OP_REMOVE);
        endOfStatement();
    }

    void changeStmt(bool increase) {
        next();
        Target t = target();
        expectKw("by", increase ? "in 'increase ... by ...'" : "in 'decrease ... by ...'");
        loadTarget(t);
        expression();
        emit(increase ? OP_ADD : OP_SUB);
        store(t);
        endOfStatement();
    }

    // Compile statements until 'end', 'otherwise' or 'on error'.
    void block(int openLine, const char* what) {
        for (;;) {
            skipNL();
            if (peek().k == Token::End) neverClosed(what, openLine);
            if (kw("end") || kw("otherwise")) return;
            if (fs->tryDepth > 0 && word("on") && word("error", 1)) return;
            statement();
        }
    }
    void expectEnd(int openLine, const char* what, bool finishStatement = true) {
        if (!acceptKw("end"))
            err(std::string("I expected 'end' to close the '") + what + "' from line " + std::to_string(openLine) +
                ", but found " + show(peek()) + ".");
        if (finishStatement) endOfStatement();
    }

    void ifStmt() {
        int line = next().line;
        expression();
        acceptKw("then");
        endOfStatement();
        int jf = emit(OP_JIF);
        block(line, "if");
        std::vector<int> ends;
        while (kw("otherwise")) {
            next();
            ends.push_back(emit(OP_JUMP));
            patch(jf);
            jf = -1;
            if (acceptKw("if")) {
                expression();
                acceptKw("then");
                endOfStatement();
                jf = emit(OP_JIF);
                block(line, "if");
            } else {
                endOfStatement();
                block(line, "if");
                break;
            }
        }
        if (jf >= 0) patch(jf);
        expectEnd(line, "if");
        for (int e : ends) patch(e);
    }

    // Does the body of the loop that starts here make an action (so a closure may keep
    // the loop's variables)? Reads ahead to the matching 'end'. Over-estimating is harmless.
    bool bodyHasClosure() const {
        int open = 1;
        for (size_t i = pos; i < toks.size() && toks[i].k != Token::End; ++i) {
            const Token& t = toks[i];
            bool starts = i == 0 || toks[i - 1].k == Token::NL;
            if (t.k == Token::Kw && t.text == "end") {
                if (--open == 0) return false;
            } else if (t.k == Token::Kw && t.text == "action") {
                return true;
            } else if (t.k == Token::Kw && t.text == "define") {
                return true;
            } else if (starts && t.k == Token::Kw &&
                       (t.text == "if" || t.text == "repeat" || t.text == "while" || t.text == "for" || t.text == "class")) {
                ++open;
            } else if (starts && t.k == Token::Word && t.text == "try" && toks[i + 1].k == Token::NL) {
                ++open;
            }
        }
        return false;
    }
    // Each round of a loop gets its own copy of the variables made in the body.
    int emitFresh(int from) { return emitWide(OP_FRESH, from); }
    void patchFresh(int at) { fs->fn->code[(size_t)at + 1] = (uint32_t)fs->fn->nlocals; }

    // A loop variable that closures may capture: its own slot, visible only inside the loop.
    struct LoopVar { std::string name; int slot = -1; bool had = false; int oldSlot = -1; };
    LoopVar scopeLoopVar(const std::string& name) {
        LoopVar v;
        v.name = name;
        auto it = fs->locals.find(name);
        if (it != fs->locals.end()) { v.had = true; v.oldSlot = it->second; }
        v.slot = newLocal(name);
        return v;
    }
    void endLoopVar(const LoopVar& v) {
        if (v.slot < 0) return;
        if (v.had) fs->locals[v.name] = v.oldSlot;
        else fs->locals.erase(v.name);
    }

    void closeLoop(Loop& loop) {
        for (int b : loop.breaks) patch(b);
    }
    Loop& openLoop(int contTarget) {
        Loop l;
        l.contTarget = contTarget;
        l.tryDepth = fs->tryDepth;
        fs->loops.push_back(l);
        return fs->loops.back();
    }

    void repeatStmt() {
        int line = next().line;
        expression();
        expectKw("times", "after the number in 'repeat'");
        endOfStatement();
        bool fresh = !fs->isMain && bodyHasClosure();
        int h = newLocal("");
        emit(OP_REPPREP, h);
        int top = here();
        int test = emitWide(OP_REPTEST, h);
        openLoop(top);
        int fr = fresh ? emitFresh(fs->fn->nlocals) : -1;
        block(line, "repeat");
        if (fr >= 0) patchFresh(fr);
        emit(OP_JUMP, top);
        patchWide(test);
        closeLoop(fs->loops.back());
        fs->loops.pop_back();
        expectEnd(line, "repeat");
    }

    void whileStmt() {
        int line = next().line;
        int top = here();
        expression();
        endOfStatement();
        bool fresh = !fs->isMain && bodyHasClosure();
        int jf = emit(OP_JIF);
        openLoop(top);
        int fr = fresh ? emitFresh(fs->fn->nlocals) : -1;
        block(line, "while");
        if (fr >= 0) patchFresh(fr);
        emit(OP_JUMP, top);
        patch(jf);
        closeLoop(fs->loops.back());
        fs->loops.pop_back();
        expectEnd(line, "while");
    }

    void forStmt() {
        int line = next().line;
        if (acceptKw("each")) {
            std::string name = expectName("for each item");
            expectKw("in", "in 'for each ... in ...'");
            expression();
            endOfStatement();
            bool fresh = bodyHasClosure();
            int h = newLocal("");
            newLocal("");
            emit(OP_ITERPREP, h);
            int top = here();
            int test = emitWide(OP_ITERNEXT, h);
            int fr = -1;
            LoopVar lv;
            if (fresh) {
                lv = scopeLoopVar(name);  // a variable of its own, new in every round
                fr = emitFresh(lv.slot);
                emit(OP_SETL, lv.slot);
            } else {
                storeName(name, true);
            }
            openLoop(top);
            block(line, "for each");
            if (fr >= 0) { patchFresh(fr); endLoopVar(lv); }
            emit(OP_JUMP, top);
            patchWide(test);
            closeLoop(fs->loops.back());
            fs->loops.pop_back();
            expectEnd(line, "for each");
            return;
        }
        std::string name = expectName("for the counter");
        expectKw("from", "in 'for ... from ... to ...'");
        expression();
        LoopVar lv;
        // Look ahead past this header line to see whether the body makes actions.
        size_t savedPos = pos;
        while (toks[pos].k != Token::NL && toks[pos].k != Token::End) ++pos;
        if (toks[pos].k == Token::NL) ++pos;
        bool scoped = bodyHasClosure();
        pos = savedPos;
        if (scoped) {
            lv = scopeLoopVar(name);
            emit(OP_SETL, lv.slot);
        } else {
            storeName(name, true);
        }
        expectKw("to", "in 'for ... from ... to ...'");
        expression();
        int h = newLocal("");
        emit(OP_SETL, h);
        int h2 = newLocal("");
        if (acceptKw("by")) expression();
        else emit(OP_CONST, addConst(Value::integer(1)));
        emit(OP_SETL, h2);
        endOfStatement();
        // Where does the counter live? (after storeName it is either a local or a global)
        bool local = fs->locals.count(name) > 0;
        int slot = local ? fs->locals[name] : prog.slot(name);
        loadName(name);
        emit(OP_GETL, h);
        emit(OP_GETL, h2);
        int test = emit(OP_FORTEST);
        int top = here();
        openLoop(-1);
        block(line, "for");
        Loop& loop = fs->loops.back();
        curLine = line;
        // 'skip' jumps here: to the fresh-variables step if there is one, then the counting step.
        for (int c : loop.conts) patch(c);
        if (scoped) patchFresh(emitFresh(slot));
        // Fused "add the step, test, jump back" instruction.
        int nextAt = emitWide(local ? OP_FORL : OP_FORG, slot);
        if (h > 255) err("This action has too many loops.");
        fs->fn->code[(size_t)nextAt + 1] = ((uint32_t)top << 8) | (uint32_t)(h & 0xFF);
        patch(test);
        closeLoop(loop);
        fs->loops.pop_back();
        if (scoped) endLoopVar(lv);
        expectEnd(line, "for");
    }

    void jumpStmt(bool isStop) {
        next();
        if (fs->loops.empty()) err(std::string("'") + (isStop ? "stop" : "skip") + "' only works inside a loop.", curLine);
        Loop& loop = fs->loops.back();
        if (fs->tryDepth > loop.tryDepth) emit(OP_ENDTRY, fs->tryDepth - loop.tryDepth);
        if (isStop) loop.breaks.push_back(emit(OP_JUMP));
        else if (loop.contTarget >= 0) emit(OP_JUMP, loop.contTarget);
        else loop.conts.push_back(emit(OP_JUMP));
        endOfStatement();
    }

    // Everything after the name of an action: "[with a and b]" and then either
    // "gives <expression>" (lambdas only) or a block closed by 'end'.
    // Returns the finished prototype; the caller decides how to create the closure.
    Value compileFunction(const std::string& name, int line, bool isMethod, const std::string& className,
                          bool hasParent, bool statementForm) {
        Func* fn = new Func;
        Value fv = Value::obj(fn);
        fn->name = name;
        fn->file = file;
        fn->isMethod = isMethod;
        FS nf;
        nf.fn = fn;
        nf.enclosing = fs;
        nf.isMethod = isMethod;
        nf.className = className;
        nf.classHasParent = hasParent;
        FS* saved = fs;
        fs = &nf;
        if (isMethod) newLocal("me");
        if (statementForm && sym("("))
            err("Plain names the values of an action after 'with', like: define " + (name.empty() ? std::string("area") : name) + " with a, b");
        if (acceptKw("with")) {
            do {
                std::string p = expectName("for a value the action needs");
                if (nf.locals.count(p)) err("'" + (name.empty() ? std::string("this action") : name) + "' has two values called '" + p + "'.");
                newLocal(p);
            } while (acceptSym(",") || acceptKw("and"));
        }
        fn->nparams = fn->nlocals;
        const char* what = isMethod ? "define" : (statementForm ? "define" : "action");
        if (!statementForm && acceptKw("gives")) {
            expression();
            emit(OP_RETURN);
        } else {
            int savedBase = nlBase;
            if (statementForm) {
                endOfStatement();
            } else {
                // The newline after the header belongs to the body, even inside brackets.
                const Token& raw = toks[pos];
                if (raw.k != Token::NL)
                    err("I expected 'gives' or a new line after the values of this action, but found " + show(peek()) + ".");
                nlBase = raw.depth;
                next();
            }
            block(line, what);
            emit(OP_NOTHING);
            emit(OP_RETURN);
            expectEnd(line, what, statementForm);
            nlBase = savedBase;
        }
        fs = saved;
        prog.funcs.push_back(fv);
        return fv;
    }

    void emitClosure(const Value& fv) {
        Func* fn = static_cast<Func*>(fv.o);
        emit(OP_CLOSURE, addConst(fv));
        for (const UpDesc& u : fn->upvals) {
            fs->fn->code.push_back((u.isLocal ? 0x80000000u : 0u) | u.index);
            fs->fn->lines.push_back(curLine);
        }
    }

    void defineStmt() {
        int line = next().line;
        std::string name = expectName("for the new action");
        if (fs->isMain) {
            // Actions at the top level are registered right away, so they can be
            // called from anywhere in the program, even above their definition.
            int s = prog.slot(name);
            prog.gdeclared[(size_t)s] = 1;
            Value fv = compileFunction(name, line, false, "", false, true);
            if (!static_cast<Func*>(fv.o)->upvals.empty()) {  // it uses a loop's variable: make it when the line runs
                emitClosure(fv);
                emit(OP_SETG, s);
            } else {
                prog.gvals[(size_t)s] = Value::obj(new Closure(static_cast<Func*>(fv.o)));
            }
        } else {
            // Inside another action: a variable of that action, created when this line runs.
            int slot;
            auto it = fs->locals.find(name);
            slot = it != fs->locals.end() ? it->second : newLocal(name);
            Value fv = compileFunction(name, line, false, "", false, true);
            emitClosure(fv);
            emit(OP_SETL, slot);
        }
    }

    void classStmt() {
        int line = next().line;
        std::string name = expectName("for the class");
        emit(OP_CLASS, nameOperand(name));
        storeName(name, true);
        bool hasParent = false;
        if (acceptKw("extends")) {
            hasParent = true;
            loadName(name);
            expression();
            emit(OP_INHERIT);
        }
        endOfStatement();
        for (;;) {
            skipNL();
            if (peek().k == Token::End) neverClosed("class", line);
            if (kw("end")) break;
            int mline = peek().line;
            std::string mname;
            if (kw("define")) {
                next();
                mname = expectName("for the action");
            } else if (word("init")) {
                next();
                mname = "init";
            } else {
                err("Inside a class I expected 'define' or 'init', but found " + show(peek()) + ".");
            }
            loadName(name);
            Value fv = compileFunction(mname, mline, true, name, hasParent, true);
            emitClosure(fv);
            emit(OP_DEFMETHOD, nameOperand(mname));
        }
        expectEnd(line, "class");
    }

    void giveStmt() {
        next();
        expectKw("back", "after 'give'");
        if (fs->isMain) err("'give back' only works inside a 'define'.", curLine);
        if (atEnd()) emit(OP_NOTHING);
        else expression();
        emit(OP_RETURN);
        endOfStatement();
    }

    void tryStmt() {
        int line = next().line;
        endOfStatement();
        int t = emit(OP_TRY);
        fs->tryDepth++;
        block(line, "try");
        fs->tryDepth--;
        emit(OP_ENDTRY, 1);
        int j = emit(OP_JUMP);
        patch(t);
        if (!(word("on") && word("error", 1)))
            err("I expected 'on error' to finish the 'try' from line " + std::to_string(line) + ", but found " + show(peek()) + ".");
        next();
        next();
        if (!atEnd()) storeName(expectName("to keep the error message in"));
        else emit(OP_POP);
        endOfStatement();
        block(line, "try");
        expectEnd(line, "try");
        patch(j);
    }

    void failStmt() {
        next();
        next();
        expression();
        emit(OP_FAIL);
        endOfStatement();
    }

    void callStmt() {
        next();
        std::string name = next().text;
        loadName(name, true);
        int n = 0;
        if (acceptKw("with")) {
            do {
                expression();
                ++n;
            } while (acceptSym(","));
        }
        emitCall(OP_CALL, n);
        emit(OP_POP);
        endOfStatement();
    }

    // use "other" - run another file, or an installed package, once.
    void useStmt() {
        int line = next().line;
        std::string name = next().text;
        endOfStatement();
        std::string key = file + "\n" + name;
        std::string path;
        auto known = prog.resolved.find(key);
        if (known != prog.resolved.end()) {
            path = known->second;
        } else {
            path = resolveModule(file, name, prog.embedded.empty() ? nullptr : &prog.embedded);
            if (path.empty())
                err("I couldn't find '" + name + "'. It should be a file next to this one" +
                        (name.find('.') == std::string::npos && name.find('/') == std::string::npos
                             ? ", or a package installed with: plain install ..."
                             : "."),
                    line);
            prog.resolved[key] = path;
        }
        if (!prog.used.insert(path).second) return;
        std::string source;
        auto it = prog.embedded.find(path);
        if (const char* lib = libSource(path)) source = lib;
        else if (it != prog.embedded.end()) source = it->second;
        else if (!readFile(path, source)) err("I couldn't read the file '" + path + "'.", line);
        prog.sources.emplace_back(path, source);
        Compiler sub(prog, source, path, false);
        Value module = sub.compileMain();
        int saved = curLine;
        curLine = line;
        emit(OP_CONST, addConst(module));
        emitCall(OP_CALL, 0);
        emit(OP_POP);
        curLine = saved;
    }

    // ------------------------------------------------------- expressions
    void expression() {
        if (++depth > 200) err("This line is nested too deeply for me to follow.");
        orExpr();
        --depth;
    }
    void orExpr() {
        andExpr();
        while (acceptKw("or")) {
            int j = emit(OP_OR);
            andExpr();
            patch(j);
        }
    }
    void andExpr() {
        notExpr();
        while (acceptKw("and")) {
            int j = emit(OP_AND);
            notExpr();
            patch(j);
        }
    }
    void notExpr() {
        if (acceptKw("not")) {
            notExpr();
            emit(OP_NOT);
        } else {
            comparison();
        }
    }
    void comparison() {
        additive();
        if (acceptKw("is")) {
            bool neg = acceptKw("not");
            if (acceptKw("greater")) { expectKw("than", "after 'greater'"); additive(); emit(OP_GT); }
            else if (acceptKw("less")) { expectKw("than", "after 'less'"); additive(); emit(OP_LT); }
            else if (acceptKw("at")) {
                if (acceptKw("least")) { additive(); emit(OP_GE); }
                else if (acceptKw("most")) { additive(); emit(OP_LE); }
                else err("I expected 'least' or 'most' after 'at', but found " + show(peek()) + ".");
            }
            else if (acceptKw("equal")) { acceptKw("to"); additive(); emit(OP_EQ); }
            else if (acceptKw("in")) { additive(); emit(OP_SWAP); emit(OP_CONTAINS); }
            else { additive(); emit(OP_EQ); }
            if (neg) emit(OP_NOT);
        } else if (acceptKw("contains")) { additive(); emit(OP_CONTAINS); }
        else if (acceptSym("==") || acceptSym("=")) { additive(); emit(OP_EQ); }
        else if (acceptSym("!=")) { additive(); emit(OP_NE); }
        else if (acceptSym("<=")) { additive(); emit(OP_LE); }
        else if (acceptSym(">=")) { additive(); emit(OP_GE); }
        else if (acceptSym("<")) { additive(); emit(OP_LT); }
        else if (acceptSym(">")) { additive(); emit(OP_GT); }
        else return;
        if (kw("is") || kw("contains") || sym("==") || sym("=") || sym("!=") || sym("<=") || sym(">=") || sym("<") || sym(">"))
            err("Compare two values at a time, and join the comparisons with 'and', like: a is less than b and b is less than c");
    }
    void additive() {
        multiplicative();
        for (;;) {
            if (acceptSym("+") || acceptKw("plus")) { multiplicative(); emit(OP_ADD); }
            else if (acceptSym("-") || acceptKw("minus")) { multiplicative(); emit(OP_SUB); }
            else break;
        }
    }
    void multiplicative() {
        unary();
        for (;;) {
            if (acceptSym("*")) { unary(); emit(OP_MUL); }
            else if (acceptKw("multiplied")) { expectKw("by", "after 'multiplied'"); unary(); emit(OP_MUL); }
            else if (acceptSym("/")) { unary(); emit(OP_DIV); }
            else if (acceptKw("divided")) { expectKw("by", "after 'divided'"); unary(); emit(OP_DIV); }
            else if (acceptSym("%") || acceptKw("modulo")) { unary(); emit(OP_MOD); }
            else break;
        }
    }
    void unary() {
        if (acceptSym("-")) {
            if (peek().k == Token::Num && !sym("^", 1)) {
                Token t = next();
                emitNumber(t, true);
                postfixOps();
                return;
            }
            unary();
            emit(OP_NEG);
        } else {
            power();
        }
    }
    void power() {
        postfix();
        if (acceptSym("^")) {
            unary();
            emit(OP_POW);
        }
    }
    void postfix() {
        primary();
        postfixOps();
    }
    void callArguments(int& n) {
        n = 0;
        if (!sym(")")) {
            do {
                expression();
                ++n;
            } while (acceptSym(","));
        }
        expectSym(")", "to close the '('");
        if (n > 250) err("That is too many values for one action.");
    }
    void postfixOps() {
        for (;;) {
            if (sym("(")) {
                next();
                int n;
                callArguments(n);
                emitCall(OP_CALL, n);
            } else if (peek().k == Token::Poss) {
                next();
                const Token& t = peek();
                if (t.k != Token::Word && t.k != Token::Kw) err("I expected a name after 's, but found " + show(t) + ".");
                std::string name = next().text;
                if (sym("(")) {
                    next();
                    int n;
                    callArguments(n);
                    emitCall(OP_INVOKE, (nameOperand(name) << 8) | n);
                } else {
                    emitStr(name);
                    emit(OP_GETIDX);
                }
            } else if (sym("[")) {
                next();
                expression();
                expectSym("]", "to close the '['");
                emit(OP_GETIDX);
            } else {
                break;
            }
        }
    }
    // "Hello {name}, you have {length of xs} items": each {…} that holds a value is
    // worked out and joined in as text. Braces around anything else stay as they are,
    // so text like "{value: ..., left: ...}" keeps working.
    void templateText(const Token& s) {
        std::string literal;
        size_t from = 0;
        bool started = false;
        auto flush = [&]() {
            if (!started) { emitStr(literal); started = true; }
            else if (!literal.empty()) { emitStr(literal); emit(OP_ADD); }
            literal.clear();
        };
        for (const auto& h : s.holes) {
            literal += s.text.substr(from, h.first - from);
            std::string inside = s.text.substr(h.first + 1, h.second - h.first - 1);
            from = h.second + 1;
            if (!holeExpression(inside, s.line, false)) {
                literal += "{" + inside + "}";
                continue;
            }
            flush();
            holeExpression(inside, s.line, true);
            emit(OP_ADD);
        }
        literal += s.text.substr(from);
        flush();
    }
    // Compile the text inside a template's braces as one expression. With keep false
    // this only tries, and leaves no trace: it says whether the text is a value.
    bool holeExpression(const std::string& inside, int line, bool keep) {
        size_t first = inside.find_first_not_of(" \t");
        if (first == std::string::npos) return false;
        char c = inside[first];
        if (!(isIdStart(c) || c == '(' || c == '-' || isdigit((unsigned char)c) || c == '[')) return false;
        std::vector<Token> sub;
        try { sub = tokenize(inside); } catch (PlainError&) { return false; }
        for (Token& t : sub) t.line = line;
        std::swap(toks, sub);
        size_t savedPos = pos, codeSize = fs->fn->code.size();
        int savedDepth = depth, savedBase = nlBase, savedCall = lastCall, savedLine = curLine;
        pos = 0;
        nlBase = 0;
        bool ok = true;
        try {
            expression();
            if (peek().k != Token::NL && peek().k != Token::End) ok = false;
        } catch (PlainError&) {
            ok = false;
        }
        std::swap(toks, sub);
        pos = savedPos;
        depth = savedDepth;
        nlBase = savedBase;
        curLine = savedLine;
        lastCall = savedCall;
        if (!keep || !ok) {
            fs->fn->code.resize(codeSize);
            fs->fn->lines.resize(codeSize);
        }
        return ok;
    }

    void primary() {
        const Token& t = peek();
        switch (t.k) {
            case Token::Num: { Token n = next(); emitNumber(n, false); return; }
            case Token::Str: {
                Token s = next();
                if (s.holes.empty()) emitStr(s.text);
                else templateText(s);
                return;
            }
            case Token::Word: {
                std::string name = next().text;
                loadName(name, sym("("));
                return;
            }
            case Token::Kw:
                if (acceptKw("true")) { emit(OP_TRUE); return; }
                if (acceptKw("false")) { emit(OP_FALSE); return; }
                if (acceptKw("nothing")) { emit(OP_NOTHING); return; }
                if (acceptKw("length")) {
                    expectKw("of", "after 'length'");
                    postfix();
                    emit(OP_LENGTH);
                    return;
                }
                if (acceptKw("item")) {
                    additive();
                    expectKw("of", "after the item number");
                    postfix();
                    emit(OP_SWAP);
                    emit(OP_GETIDX);
                    return;
                }
                if (kw("me")) {
                    next();
                    if (!inMethod()) err("'me' only works inside an action of a class.", curLine);
                    loadName("me");
                    return;
                }
                if (kw("parent")) {
                    int line = next().line;
                    FS* m = methodContext();
                    if (!m) err("'parent' only works inside an action of a class.", line);
                    if (!m->classHasParent) err("This class has no parent. Add 'extends SomeClass' to the class line to use 'parent'.", line);
                    if (peek().k != Token::Poss) err("I expected 's and the name of an action after 'parent', like: parent's init(name)");
                    next();
                    const Token& nt = peek();
                    if (nt.k != Token::Word && nt.k != Token::Kw) err("I expected the name of an action after parent's, but found " + show(nt) + ".");
                    std::string name = next().text;
                    loadName("me");
                    loadName(m->className);
                    emit(OP_GETSUPER, nameOperand(name));
                    return;
                }
                if (kw("new")) {
                    int line = next().line;
                    if (peek().k != Token::Word) err("I expected the name of a class after 'new', but found " + show(peek()) + ".");
                    std::string cname = next().text;
                    loadName(cname);
                    if (!sym("(")) err("I expected '(' after 'new " + cname + "', like: new " + cname + "(...)", line);
                    next();
                    int n;
                    callArguments(n);
                    emitCall(OP_CALL, n);
                    return;
                }
                if (kw("action")) {
                    int line = next().line;
                    Value fv = compileFunction("", line, false, "", false, false);
                    emitClosure(fv);
                    return;
                }
                break;
            case Token::Sym:
                if (acceptSym("(")) {
                    expression();
                    expectSym(")", "to close the '('");
                    return;
                }
                if (acceptSym("[")) {
                    emit(OP_NEWLIST);
                    if (!sym("]")) {
                        do {
                            if (sym("]")) break;  // allow a trailing comma
                            expression();
                            emit(OP_APPEND);
                        } while (acceptSym(","));
                    }
                    expectSym("]", "to close the list");
                    return;
                }
                if (acceptSym("{")) {
                    emit(OP_NEWMAP);
                    if (!sym("}")) {
                        do {
                            if (sym("}")) break;
                            if (peek().k == Token::Kw && sym(":", 1)) err(reservedHelp(peek().text));
                            if (peek().k == Token::Word && sym(":", 1)) emitStr(next().text);
                            else expression();
                            expectSym(":", "between a name and its value in a map");
                            expression();
                            emit(OP_MAPPUT);
                        } while (acceptSym(","));
                    }
                    expectSym("}", "to close the map");
                    return;
                }
                break;
            default: break;
        }
        err("I expected a value here, but found " + show(t) + ".");
    }
};

// Print a compiled action as readable bytecode (used by --explain).
inline void disassemble(const Program& prog, const Func& fn) {
    printf("-- %s%s\n", fn.name.empty() ? "(unnamed action)" : fn.name.c_str(), fn.name == "main program" ? "" : (fn.name.empty() ? "" : " (action)"));
    for (size_t i = 0; i < fn.code.size(); ++i) {
        uint32_t ins = fn.code[i];
        int op = (int)(ins & 0xFF);
        uint32_t a = ins >> 8;
        printf("  %4zu  line %-4d %-18s", i, fn.lines[i], opName(op));
        switch (op) {
            case OP_CONST: printf(" %s", fmt(fn.consts[a], true).c_str()); break;
            case OP_GETG: case OP_SETG: case OP_GETFN: printf(" %s", prog.gnames[a].c_str()); break;
            case OP_GETL: case OP_SETL:
                if (fn.localNames[a].empty()) printf(" (hidden %u)", a);
                else printf(" %s", fn.localNames[a].c_str());
                break;
            case OP_GETU: case OP_SETU: printf(" #%u", a); break;
            case OP_JUMP: case OP_JIF: case OP_AND: case OP_OR: case OP_TRY: case OP_FORTEST: printf(" -> %u", a); break;
            case OP_CALL: case OP_SAY: case OP_ENDTRY: printf(" %u", a); break;
            case OP_INVOKE: printf(" %s with %u value(s)", asStr(fn.consts[a >> 8]).c_str(), a & 255); break;
            case OP_CLASS: case OP_DEFMETHOD: case OP_GETSUPER: printf(" %s", asStr(fn.consts[a]).c_str()); break;
            case OP_ITERNEXT: case OP_REPTEST: printf(" -> %u", fn.code[i + 1]); break;
            case OP_FORL: printf(" %s -> %u", fn.localNames[a].c_str(), fn.code[i + 1] >> 8); break;
            case OP_FORG: printf(" %s -> %u", prog.gnames[a].c_str(), fn.code[i + 1] >> 8); break;
            case OP_CLOSURE: {
                const Func* f = static_cast<const Func*>(fn.consts[a].o);
                printf(" %s, captures %zu variable(s)", f->name.empty() ? "(unnamed)" : f->name.c_str(), f->upvals.size());
                printf("\n");
                i += f->upvals.size();
                continue;
            }
            default: break;
        }
        printf("\n");
        if (isWide(op)) ++i;
    }
}

}  // namespace plain
