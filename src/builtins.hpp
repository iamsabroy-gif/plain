// Plain - the standard library: built-in actions written in C++.
#pragma once
#include <chrono>
#include <climits>
#include <ctime>
#include <thread>

#include "tasks.hpp"

#ifndef _WIN32
#include <arpa/inet.h>
#include <csignal>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace plain {

#define BUILTIN(fname) static Value fname([[maybe_unused]] VM& vm, [[maybe_unused]] Value* a, [[maybe_unused]] int n)

static double argNum(const char* fn, Value* a, int i) {
    if (!isNumber(a[i])) fail(std::string("'") + fn + "' needs a number, but I got " + describe(a[i]) + ".");
    return toDouble(a[i]);
}
static int64_t argInt(const char* fn, Value* a, int i) {
    int64_t out;
    if (!wholeValue(a[i], out)) fail(std::string("'") + fn + "' needs a whole number, but I got " + describe(a[i]) + ".");
    return out;
}
static void needNumber(const char* fn, Value* a, int i) {
    if (!isNumber(a[i])) fail(std::string("'") + fn + "' needs a number, but I got " + describe(a[i]) + ".");
}
static const std::string& argStr(const char* fn, Value* a, int i) {
    if (!isStr(a[i])) fail(std::string("'") + fn + "' needs text, but I got " + describe(a[i]) + ".");
    return asStr(a[i]);
}
static List* argList(const char* fn, Value* a, int i) {
    if (!isList(a[i])) fail(std::string("'") + fn + "' needs a list, but I got " + describe(a[i]) + ".");
    return asList(a[i]);
}
static Map* argMap(const char* fn, Value* a, int i) {
    if (!isMap(a[i])) fail(std::string("'") + fn + "' needs a map, but I got " + describe(a[i]) + ".");
    return asMap(a[i]);
}
static void needArgs(const char* fn, int n, int lo, int hi) {
    if (n < lo || n > hi)
        fail(std::string("'") + fn + "' needs " + (lo == hi ? std::to_string(lo) : std::to_string(lo) + " to " + std::to_string(hi)) +
             " value(s), but you gave it " + std::to_string(n) + ".");
}
// ------------------------------------------------------------------ maths
static Value b_whole_of(const Value& v) {
    if (v.tag == Value::Float) return std::isfinite(v.n) ? wholeFloatToInteger(std::trunc(v.n)) : v;
    if (isDec(v)) return fromBig(decTrunc(asDec(v)));
    return v;
}
BUILTIN(b_sqrt) {
    double x = argNum("sqrt", a, 0);
    if (x < 0) fail("I can't take the square root of a negative number (" + fmt(a[0]) + ").");
    return Value::real(std::sqrt(x));
}
BUILTIN(b_abs) {
    needNumber("abs", a, 0);
    return numAbs(a[0]);
}
BUILTIN(b_floor) {
    needNumber("floor", a, 0);
    if (a[0].tag == Value::Float) return std::isfinite(a[0].n) ? wholeFloatToInteger(std::floor(a[0].n)) : a[0];
    if (isDec(a[0])) return fromBig(decFloor(asDec(a[0])));
    return a[0];
}
BUILTIN(b_ceiling) {
    needNumber("ceiling", a, 0);
    if (a[0].tag == Value::Float) return std::isfinite(a[0].n) ? wholeFloatToInteger(std::ceil(a[0].n)) : a[0];
    if (isDec(a[0])) return fromBig(BigInt::sub(BigInt(0), decFloor(decNeg(asDec(a[0])))));
    return a[0];
}
BUILTIN(b_round) {
    needArgs("round", n, 1, 2);
    needNumber("round", a, 0);
    if (n == 1) {
        if (a[0].tag == Value::Float) return std::isfinite(a[0].n) ? wholeFloatToInteger(std::round(a[0].n)) : a[0];
        if (isDec(a[0])) return fromBig(decTrunc(decRound(asDec(a[0]), 0)));
        return a[0];
    }
    return numRound(a[0], (long)argInt("round", a, 1));
}
BUILTIN(b_power) {
    needNumber("power", a, 0);
    needNumber("power", a, 1);
    return numPow(a[0], a[1]);
}
BUILTIN(b_fraction) {
    needNumber("fraction", a, 0);
    return numSub(a[0], b_whole_of(a[0]));
}
BUILTIN(b_whole) {
    needNumber("whole", a, 0);
    return b_whole_of(a[0]);
}
BUILTIN(b_integer) { return toInteger(a[0]); }
BUILTIN(b_float) { return toFloat(a[0]); }
BUILTIN(b_decimal) { return toDecimal(a[0]); }
BUILTIN(b_quotient) {
    needNumber("quotient", a, 0);
    needNumber("quotient", a, 1);
    return numQuotient(a[0], a[1]);
}
BUILTIN(b_fixed) {
    needNumber("fixed", a, 0);
    return mkstr(fixedText(a[0], (long)argInt("fixed", a, 1)));
}
BUILTIN(b_is_integer) { return Value::boolean(a[0].tag == Value::Int || isBig(a[0])); }
BUILTIN(b_is_decimal) { return Value::boolean(isDec(a[0])); }
BUILTIN(b_is_float) { return Value::boolean(a[0].tag == Value::Float); }
BUILTIN(b_sin) { return Value::real(std::sin(argNum("sin", a, 0))); }
BUILTIN(b_cos) { return Value::real(std::cos(argNum("cos", a, 0))); }
BUILTIN(b_tan) { return Value::real(std::tan(argNum("tan", a, 0))); }
BUILTIN(b_exp) { return Value::real(std::exp(argNum("exp", a, 0))); }
BUILTIN(b_log) {
    double x = argNum("log", a, 0);
    if (x <= 0) fail("'log' needs a number greater than zero, but I got " + fmt(a[0]) + ".");
    return Value::real(std::log(x));
}
BUILTIN(b_pi) { return Value::real(3.14159265358979323846); }
static Value minMax(const char* fn, Value* a, int n, bool wantMax) {
    Value* items = a;
    int count = n;
    if (n == 1 && isList(a[0])) {
        items = asList(a[0])->items.data();
        count = (int)asList(a[0])->items.size();
    }
    if (count == 0) fail(std::string("'") + fn + "' needs at least one value.");
    int best = 0;
    for (int i = 1; i < count; ++i) {
        int c = compareValues(items[i], items[best]);
        if (wantMax ? c > 0 : c < 0) best = i;
    }
    return items[best];
}
BUILTIN(b_min) { return minMax("min", a, n, false); }
BUILTIN(b_max) { return minMax("max", a, n, true); }
BUILTIN(b_random) {
    needArgs("random", n, 0, 2);
    if (n == 0) return Value::real(std::uniform_real_distribution<double>(0.0, 1.0)(vm.rng));
    double lo = n == 2 ? argNum("random", a, 0) : 1, hi = argNum("random", a, n - 1);
    if (hi < lo) fail("'random' needs the smaller number first (" + fmt(a[0]) + " is greater than " + fmt(a[n - 1]) + ").");
    return Value::integer(std::uniform_int_distribution<long long>((long long)std::ceil(lo), (long long)std::floor(hi))(vm.rng));
}
BUILTIN(b_sum) {
    Value total = Value::integer(0);
    for (Value& v : argList("sum", a, 0)->items) {
        if (!isNumber(v)) fail(std::string("'sum' can only add up numbers, but the list contains ") + describe(v) + ".");
        total = numAdd(total, v);
    }
    return total;
}

// ------------------------------------------------------------------- text
BUILTIN(b_text) { return mkstr(fmt(a[0])); }
BUILTIN(b_number) {
    if (isNumber(a[0])) return a[0];
    if (a[0].tag == Value::Bool) return Value::integer(a[0].b ? 1 : 0);
    if (isStr(a[0])) {
        Value v = parseInput(asStr(a[0]));
        if (isNumber(v)) return v;
    }
    fail("I can't turn " + fmt(a[0], true) + " into a number.");
}
static std::string uppercaseCopy(std::string s) {
    for (char& c : s) c = (char)toupper((unsigned char)c);
    return s;
}
BUILTIN(b_uppercase) {
    std::string s = argStr("uppercase", a, 0);
    for (char& c : s) c = (char)toupper((unsigned char)c);
    return mkstr(s);
}
BUILTIN(b_lowercase) {
    std::string s = argStr("lowercase", a, 0);
    for (char& c : s) c = (char)tolower((unsigned char)c);
    return mkstr(s);
}
BUILTIN(b_trim) {
    const std::string& s = argStr("trim", a, 0);
    size_t x = s.find_first_not_of(" \t\r\n"), y = s.find_last_not_of(" \t\r\n");
    return mkstr(x == std::string::npos ? "" : s.substr(x, y - x + 1));
}
BUILTIN(b_split) {
    const std::string& s = argStr("split", a, 0);
    const std::string& sep = argStr("split", a, 1);
    std::vector<Value> out;
    if (sep.empty()) {
        for (std::string& c : u8chars(s)) out.push_back(mkstr(std::move(c)));
    } else {
        size_t start = 0, at;
        while ((at = s.find(sep, start)) != std::string::npos) {
            out.push_back(mkstr(s.substr(start, at - start)));
            start = at + sep.size();
        }
        out.push_back(mkstr(s.substr(start)));
    }
    return mklist(std::move(out));
}
BUILTIN(b_join) {
    List* l = argList("join", a, 0);
    const std::string& sep = argStr("join", a, 1);
    std::string out;
    for (size_t i = 0; i < l->items.size(); ++i) {
        if (i) out += sep;
        out += fmt(l->items[i]);
    }
    return mkstr(out);
}
BUILTIN(b_replace) {
    std::string s = argStr("replace", a, 0);
    const std::string& from = argStr("replace", a, 1);
    const std::string& to = argStr("replace", a, 2);
    if (from.empty()) fail("'replace' needs some text to look for, but I got empty text.");
    size_t at = 0;
    while ((at = s.find(from, at)) != std::string::npos) {
        s.replace(at, from.size(), to);
        at += to.size();
    }
    return mkstr(s);
}
BUILTIN(b_find) {
    const std::string& s = argStr("find", a, 0);
    size_t at = s.find(argStr("find", a, 1));
    if (at == std::string::npos) return Value::integer(0);
    return Value::integer((int64_t)u8len(s.substr(0, at)) + 1);
}
BUILTIN(b_starts_with) {
    const std::string& s = argStr("starts_with", a, 0);
    const std::string& p = argStr("starts_with", a, 1);
    return Value::boolean(s.compare(0, p.size(), p) == 0);
}
BUILTIN(b_ends_with) {
    const std::string& s = argStr("ends_with", a, 0);
    const std::string& p = argStr("ends_with", a, 1);
    return Value::boolean(s.size() >= p.size() && s.compare(s.size() - p.size(), p.size(), p) == 0);
}
// slice(list or text, from, to) - both ends included, counting from 1.
BUILTIN(b_slice) {
    int64_t from = argInt("slice", a, 1), to = argInt("slice", a, 2);
    if (isList(a[0])) {
        auto& items = asList(a[0])->items;
        long lo = std::max(1L, (long)from), hi = std::min((long)items.size(), (long)to);
        std::vector<Value> out;
        for (long i = lo; i <= hi; ++i) out.push_back(items[(size_t)i - 1]);
        return mklist(std::move(out));
    }
    std::vector<std::string> chars = u8chars(argStr("slice", a, 0));
    long lo = std::max(1L, (long)from), hi = std::min((long)chars.size(), (long)to);
    std::string out;
    for (long i = lo; i <= hi; ++i) out += chars[(size_t)i - 1];
    return mkstr(out);
}

// ------------------------------------------------------------------ lists
BUILTIN(b_sort) {
    std::vector<Value> items = argList("sort", a, 0)->items;
    std::stable_sort(items.begin(), items.end(), [](const Value& x, const Value& y) { return compareValues(x, y) < 0; });
    return mklist(std::move(items));
}
BUILTIN(b_reverse) {
    if (isStr(a[0])) {
        std::vector<std::string> chars = u8chars(asStr(a[0]));
        std::string out;
        for (size_t i = chars.size(); i-- > 0;) out += chars[i];
        return mkstr(out);
    }
    std::vector<Value> items = argList("reverse", a, 0)->items;
    std::reverse(items.begin(), items.end());
    return mklist(std::move(items));
}
BUILTIN(b_range) {
    needArgs("range", n, 2, 3);
    double lo = argNum("range", a, 0), hi = argNum("range", a, 1), step = n == 3 ? argNum("range", a, 2) : 1;
    if (step == 0) fail("'range' can't count by 0.");
    if (a[0].tag == Value::Int && a[1].tag != Value::Int && a[1].tag != Value::Float && !isBig(a[1])) fail("'range' needs whole or float numbers.");
    std::vector<Value> out;
    if (a[0].tag == Value::Int && a[1].tag == Value::Int && (n < 3 || a[2].tag == Value::Int)) {
        int64_t s = n == 3 ? a[2].i : 1;
        for (int64_t x = a[0].i; s > 0 ? x <= a[1].i : x >= a[1].i; x += s) {
            if (out.size() > 50000000) fail("That range is too big to hold in a list.");
            out.push_back(Value::integer(x));
        }
        return mklist(std::move(out));
    }
    for (double x = lo; step > 0 ? x <= hi : x >= hi; x += step) {
        if (out.size() > 50000000) fail("That range is too big to hold in a list.");
        out.push_back(Value::real(x));
    }
    return mklist(std::move(out));
}
BUILTIN(b_first) {
    if (isStr(a[0]) && !asStr(a[0]).empty()) return mkstr(u8chars(asStr(a[0])).front());
    if (isStr(a[0])) fail("The text is empty, so it has no first character.");
    List* l = argList("first", a, 0);
    if (l->items.empty()) fail("The list is empty, so it has no first item.");
    return l->items.front();
}
BUILTIN(b_last) {
    if (isStr(a[0]) && !asStr(a[0]).empty()) return mkstr(u8chars(asStr(a[0])).back());
    if (isStr(a[0])) fail("The text is empty, so it has no last character.");
    List* l = argList("last", a, 0);
    if (l->items.empty()) fail("The list is empty, so it has no last item.");
    return l->items.back();
}
BUILTIN(b_insert) {
    List* l = argList("insert", a, 0);
    int64_t at = argInt("insert", a, 1);
    if (at < 1 || at > (int64_t)l->items.size() + 1)
        fail("I can't insert at position " + std::to_string(at) + " - the list has " + std::to_string(l->items.size()) + " item(s).");
    l->items.insert(l->items.begin() + (long)at - 1, a[2]);
    return Value();
}
BUILTIN(b_index_of) {
    auto& items = argList("index_of", a, 0)->items;
    for (size_t i = 0; i < items.size(); ++i)
        if (equals(items[i], a[1])) return Value::integer((int64_t)i + 1);
    return Value::integer(0);
}
BUILTIN(b_copy) {
    if (isList(a[0])) return mklist(asList(a[0])->items);
    if (isMap(a[0])) {
        Map* m = new Map;
        Value out = Value::obj(m);
        for (const auto& e : asMap(a[0])->entries) m->set(e.first, e.second);
        return out;
    }
    return a[0];
}
BUILTIN(b_keys) {
    std::vector<Value> out;
    for (const auto& e : argMap("keys", a, 0)->entries) out.push_back(e.first);
    return mklist(std::move(out));
}
BUILTIN(b_values) {
    std::vector<Value> out;
    for (const auto& e : argMap("values", a, 0)->entries) out.push_back(e.second);
    return mklist(std::move(out));
}
BUILTIN(b_has_key) { return Value::boolean(argMap("has_key", a, 0)->find(a[1]) != nullptr); }
BUILTIN(b_type_of) {
    const Value& v = a[0];
    if (v.tag == Value::Int || isBig(v)) return mkstr("integer");
    if (v.tag == Value::Float) return mkstr("float");
    if (isDec(v)) return mkstr("decimal");
    if (isKind(v, Kind::Instance)) return mkstr(asClass(asInstance(v)->cls)->name);
    if (isKind(v, Kind::Class)) return mkstr("class");
    if (isKind(v, Kind::Handle)) return mkstr(static_cast<Handle*>(v.o)->label());
    if (v.tag == Value::Bool) return mkstr("true/false");
    if (isStr(v)) return mkstr("text");
    if (isList(v)) return mkstr("list");
    if (isMap(v)) return mkstr("map");
    if (v.tag == Value::Object) return mkstr("action");
    return mkstr("nothing");
}

// ------------------------------------------------------------------ files
BUILTIN(b_read_file) {
    std::string out;
    if (!readFile(argStr("read_file", a, 0), out)) fail("I couldn't open the file '" + asStr(a[0]) + "'.");
    return mkstr(out);
}
BUILTIN(b_read_lines) {
    std::string text;
    if (!readFile(argStr("read_lines", a, 0), text)) fail("I couldn't open the file '" + asStr(a[0]) + "'.");
    std::vector<Value> out;
    size_t start = 0;
    while (start < text.size()) {
        size_t at = text.find('\n', start);
        if (at == std::string::npos) at = text.size();
        std::string line = text.substr(start, at - start);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        out.push_back(mkstr(std::move(line)));
        start = at + 1;
    }
    return mklist(std::move(out));
}
static Value writeTo(const char* fn, Value* a, const char* mode) {
    const std::string& path = argStr(fn, a, 0);
    FILE* f = fopen(path.c_str(), mode);
    if (!f) fail("I couldn't write to the file '" + path + "'.");
    std::string s = fmt(a[1]);
    fwrite(s.data(), 1, s.size(), f);
    fclose(f);
    return Value();
}
BUILTIN(b_write_file) { return writeTo("write_file", a, "wb"); }
BUILTIN(b_append_file) { return writeTo("append_file", a, "ab"); }
BUILTIN(b_file_exists) {
    FILE* f = fopen(argStr("file_exists", a, 0).c_str(), "rb");
    if (f) fclose(f);
    return Value::boolean(f != nullptr);
}
BUILTIN(b_delete_file) {
    if (remove(argStr("delete_file", a, 0).c_str()) != 0) fail("I couldn't delete the file '" + asStr(a[0]) + "'.");
    return Value();
}

// ----------------------------------------------------------------- system
BUILTIN(b_clock) {
    static const auto start = std::chrono::steady_clock::now();
    return Value::real(std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count());
}
BUILTIN(b_time_now) { return Value::integer((int64_t)std::time(nullptr)); }
BUILTIN(b_date_text) {
    needArgs("date_text", n, 0, 1);
    std::time_t t = std::time(nullptr);
    char buf[128];
    strftime(buf, sizeof buf, n == 1 ? argStr("date_text", a, 0).c_str() : "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return mkstr(buf);
}
BUILTIN(b_wait) {
    fflush(stdout);
    double seconds = std::max(0.0, argNum("wait", a, 0));
    Unlocked u;  // other tasks run while this one sleeps
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
    return Value();
}
BUILTIN(b_arguments) {
    std::vector<Value> out;
    for (const std::string& s : vm.args) out.push_back(mkstr(s));
    return mklist(std::move(out));
}
BUILTIN(b_environment) {
    const char* v = getenv(argStr("environment", a, 0).c_str());
    return v ? mkstr(v) : Value();
}
BUILTIN(b_exit) {
    needArgs("exit", n, 0, 1);
    fflush(stdout);
    fflush(stderr);
    _Exit(n == 1 ? (int)argInt("exit", a, 0) : 0);
}

// ------------------------------------------------------------------- JSON
BUILTIN(b_to_json) {
    needArgs("to_json", n, 1, 2);
    std::string out;
    int indent = n == 2 ? (int)std::max<int64_t>(0, std::min<int64_t>(16, argInt("to_json", a, 1))) : -1;
    toJson(a[0], out, 0, indent, 0);
    return mkstr(out);
}
BUILTIN(b_from_json) { return jsonParse(argStr("from_json", a, 0)); }

// ---------------------------------------------------------------- objects
BUILTIN(b_is_a) {
    if (!isKind(a[1], Kind::Class)) fail(std::string("'is_a' needs a class as its second value, but I got ") + describe(a[1]) + ".");
    if (!isKind(a[0], Kind::Instance)) return Value::boolean(false);
    for (Class* c = asClass(asInstance(a[0])->cls);;) {
        if (c == a[1].o) return Value::boolean(true);
        if (!isClass(c->parent)) break;
        c = asClass(c->parent);
    }
    return Value::boolean(false);
}
// Used by sort_by: sort 'items' by the matching entries of 'keys'.
BUILTIN(b_sort_keys) {
    auto& items = argList("sort_by", a, 0)->items;
    auto& keys = argList("sort_by", a, 1)->items;
    std::vector<size_t> order(items.size());
    for (size_t i = 0; i < order.size(); ++i) order[i] = i;
    std::stable_sort(order.begin(), order.end(), [&](size_t x, size_t y) { return compareValues(keys[x], keys[y]) < 0; });
    std::vector<Value> out;
    for (size_t i : order) out.push_back(items[i]);
    return mklist(std::move(out));
}

// -------------------------------------------------------------- networking
#ifndef _WIN32
// Run another program, feed it 'input' and collect what it prints.
inline int runProcess(const std::vector<std::string>& argv, const std::string& input, std::string& out, std::string& err) {
    int in[2], ou[2], er[2];
    if (pipe(in) != 0 || pipe(ou) != 0 || pipe(er) != 0) return -1;
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        dup2(in[0], 0);
        dup2(ou[1], 1);
        dup2(er[1], 2);
        for (int fd : {in[0], in[1], ou[0], ou[1], er[0], er[1]}) close(fd);
        std::vector<char*> args;
        for (const std::string& s : argv) args.push_back(const_cast<char*>(s.c_str()));
        args.push_back(nullptr);
        execvp(args[0], args.data());
        _exit(127);
    }
    close(in[0]);
    close(ou[1]);
    close(er[1]);
    size_t sent = 0;
    while (sent < input.size()) {
        ssize_t w = write(in[1], input.data() + sent, input.size() - sent);
        if (w <= 0) break;
        sent += (size_t)w;
    }
    close(in[1]);
    char buf[65536];
    ssize_t r;
    while ((r = read(ou[0], buf, sizeof buf)) > 0) out.append(buf, (size_t)r);
    while ((r = read(er[0], buf, sizeof buf)) > 0) err.append(buf, (size_t)r);
    close(ou[0]);
    close(er[0]);
    int status = 0;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

// http_request(method, url, body, headers) -> {status: 200, body: "..."}
// Uses the 'curl' program, which handles https, redirects and proxies.
static Value plainHttp(const std::string& method, std::string url, const std::string& payload, const std::string& contentType, const Value& headers, int redirects);
static Value httpRequest(const std::string& method, const std::string& url, const Value& body, const Value& headers) {
    if (url.compare(0, 7, "http://") != 0 && url.compare(0, 8, "https://") != 0)
        fail("A web address must start with http:// or https://, but I got " + quote(url) + ".");
    if (url.compare(0, 7, "http://") == 0) {
        bool js = isMap(body) || isList(body) || isKind(body, Kind::Instance);
        std::string pl;
        if (body.tag != Value::Nothing) {
            if (js) toJson(body, pl, 0, -1, 0);
            else pl = fmt(body);
        }
        if (headers.tag != Value::Nothing && !isMap(headers))
            fail(std::string("The headers of a web request must be a map, but I got ") + describe(headers) + ".");
        return plainHttp(method, url, pl, js ? "application/json" : "", headers, 0);
    }
    std::vector<std::string> argv = {"curl", "-sS", "-L", "--max-time", "60", "-X", method, "-w", "\n%{http_code}"};
    std::string payload;
    bool json = isMap(body) || isList(body) || isKind(body, Kind::Instance);
    if (body.tag != Value::Nothing) {
        if (json) toJson(body, payload, 0, -1, 0);
        else payload = fmt(body);
        argv.push_back("--data-binary");
        argv.push_back("@-");
    }
    bool hasType = false;
    if (isMap(headers)) {
        for (const auto& e : asMap(headers)->entries) {
            std::string name = fmt(e.first), lower = name;
            for (char& c : lower) c = (char)tolower((unsigned char)c);
            if (lower == "content-type") hasType = true;
            argv.push_back("-H");
            argv.push_back(name + ": " + fmt(e.second));
        }
    } else if (headers.tag != Value::Nothing) {
        fail(std::string("The headers of a web request must be a map, but I got ") + describe(headers) + ".");
    }
    if (json && !hasType) {
        argv.push_back("-H");
        argv.push_back("Content-Type: application/json");
    }
    argv.push_back("--");
    argv.push_back(url);
    std::string out, err;
    int code;
    {
        Unlocked u;
        code = runProcess(argv, payload, out, err);
    }
    if (code == 127) fail("Web requests need the 'curl' program, and I couldn't find it on this computer.");
    if (code != 0) {
        while (!err.empty() && (err.back() == '\n' || err.back() == '\r')) err.pop_back();
        fail("I couldn't reach " + url + (err.empty() ? "." : ": " + err));
    }
    size_t cut = out.find_last_of('\n');
    Map* m = new Map;
    Value result = Value::obj(m);
    m->set(mkstr("status"), Value::integer(cut == std::string::npos ? 0 : atoi(out.c_str() + cut + 1)));
    m->set(mkstr("body"), mkstr(cut == std::string::npos ? out : out.substr(0, cut)));
    return result;
}
BUILTIN(b_http_get) {
    needArgs("http_get", n, 1, 2);
    return httpRequest("GET", argStr("http_get", a, 0), Value(), n == 2 ? a[1] : Value());
}
BUILTIN(b_http_post) {
    needArgs("http_post", n, 2, 3);
    return httpRequest("POST", argStr("http_post", a, 0), a[1], n == 3 ? a[2] : Value());
}
BUILTIN(b_http_request) {
    needArgs("http_request", n, 2, 4);
    return httpRequest(uppercaseCopy(argStr("http_request", a, 0)), argStr("http_request", a, 1), n >= 3 ? a[2] : Value(), n == 4 ? a[3] : Value());
}

// Plain TCP connections: a connection is just a number that names it.
static int argConn(const char* fn, Value* a) {
    int64_t fd = argInt(fn, a, 0);
    if (fd < 0 || fd > INT_MAX) fail(std::string("'") + fn + "' needs a connection, but " + std::to_string(fd) + " is not one.");
    return (int)fd;
}
BUILTIN(b_tcp_connect) {
    std::string host = argStr("tcp_connect", a, 0), port = std::to_string(argInt("tcp_connect", a, 1));
    struct addrinfo hints, *res = nullptr;
    memset(&hints, 0, sizeof hints);
    hints.ai_socktype = SOCK_STREAM;
    int fd = -1;
    {
        Unlocked u;
        if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) == 0) {
            for (struct addrinfo* p = res; p; p = p->ai_next) {
                fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
                if (fd < 0) continue;
                if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) break;
                close(fd);
                fd = -1;
            }
            freeaddrinfo(res);
        }
    }
    if (fd < 0) fail("I couldn't connect to " + host + " on port " + port + ".");
    return Value::integer(fd);
}
BUILTIN(b_tcp_listen) {
    int64_t port = argInt("tcp_listen", a, 0);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((uint16_t)port);
    if (fd < 0 || setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) != 0 ||
        bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof addr) != 0 || listen(fd, 64) != 0) {
        if (fd >= 0) close(fd);
        fail("I couldn't listen on port " + std::to_string(port) + " (it may be in use, or not allowed).");
    }
    return Value::integer(fd);
}
BUILTIN(b_tcp_accept) {
    int server = argConn("tcp_accept", a), fd;
    fflush(stdout);
    {
        Unlocked u;
        fd = accept(server, nullptr, nullptr);
    }
    if (fd < 0) fail("I couldn't accept a connection.");
    return Value::integer(fd);
}
BUILTIN(b_tcp_send) {
    int fd = argConn("tcp_send", a);
    std::string data = fmt(a[1]);
    size_t sent = 0;
    Unlocked u;
    while (sent < data.size()) {
        ssize_t w = send(fd, data.data() + sent, data.size() - sent, 0);
        if (w <= 0) break;
        sent += (size_t)w;
    }
    return Value::boolean(sent == data.size());
}
// tcp_receive(connection) gives the next chunk of text, or "" once the other side has closed.
BUILTIN(b_tcp_receive) {
    needArgs("tcp_receive", n, 1, 2);
    int fd = argConn("tcp_receive", a);
    int64_t limit = n == 2 ? argInt("tcp_receive", a, 1) : 65536;
    if (limit < 1 || limit > (1 << 26)) fail("'tcp_receive' can read between 1 and 67108864 bytes at a time.");
    std::string buf((size_t)limit, '\0');
    ssize_t r;
    fflush(stdout);
    {
        Unlocked u;
        r = recv(fd, &buf[0], buf.size(), 0);
    }
    buf.resize(r > 0 ? (size_t)r : 0);
    return mkstr(std::move(buf));
}
// tcp_receive_line(connection) reads up to the next line break (not included).
BUILTIN(b_tcp_receive_line) {
    int fd = argConn("tcp_receive_line", a);
    std::string line;
    fflush(stdout);
    {
        Unlocked u;
        char c;
        while (recv(fd, &c, 1, 0) == 1 && c != '\n') line += c;
    }
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return mkstr(std::move(line));
}
BUILTIN(b_tcp_close) {
    close(argConn("tcp_close", a));
    return Value();
}
BUILTIN(b_tcp_port) {
    int fd = argConn("tcp_port", a);
    struct sockaddr_in addr;
    socklen_t len = sizeof addr;
    memset(&addr, 0, sizeof addr);
    if (getsockname(fd, reinterpret_cast<struct sockaddr*>(&addr), &len) != 0) fail("That isn't a network connection.");
    return Value::integer(ntohs(addr.sin_port));
}

// ---- a small built-in web client and server (plain http; https goes through curl)
static std::string lowerCopy(std::string s) {
    for (char& c : s) c = (char)tolower((unsigned char)c);
    return s;
}
static bool sendAll(int fd, const std::string& data) {
    size_t sent = 0;
    while (sent < data.size()) {
        ssize_t w = send(fd, data.data() + sent, data.size() - sent, 0);
        if (w <= 0) return false;
        sent += (size_t)w;
    }
    return true;
}
struct HttpParts {
    std::string head;  // everything before the blank line
    std::string rest;  // what came after it
    bool complete = false;
};
// Read from fd until the blank line that ends the headers.
static HttpParts readHead(int fd) {
    HttpParts p;
    std::string buf;
    char chunk[8192];
    while (buf.size() < (1 << 20)) {
        size_t at = buf.find("\r\n\r\n");
        if (at != std::string::npos) {
            p.head = buf.substr(0, at);
            p.rest = buf.substr(at + 4);
            p.complete = true;
            return p;
        }
        ssize_t r = recv(fd, chunk, sizeof chunk, 0);
        if (r <= 0) break;
        buf.append(chunk, (size_t)r);
    }
    p.head = buf;
    return p;
}
static Value parseHeaders(const std::string& head, size_t from) {
    Map* m = new Map;
    Value out = Value::obj(m);
    size_t pos = from;
    while (pos < head.size()) {
        size_t end = head.find("\r\n", pos);
        if (end == std::string::npos) end = head.size();
        std::string line = head.substr(pos, end - pos);
        pos = end + 2;
        size_t colon = line.find(':');
        if (colon == std::string::npos) continue;
        size_t v = line.find_first_not_of(" \t", colon + 1);
        m->set(mkstr(lowerCopy(line.substr(0, colon))), mkstr(v == std::string::npos ? "" : line.substr(v)));
    }
    return out;
}
static std::string headerOf(const Value& headers, const char* name) {
    Value* v = asMap(headers)->find(mkstr(name));
    return v ? fmt(*v) : "";
}
static void readBody(int fd, const std::string& te, const std::string& cl, std::string& body, bool untilClose) {
    char chunk[65536];
    auto fill = [&](std::string& buf, size_t want) {  // make sure buf has at least 'want' bytes if possible
        while (buf.size() < want) {
            ssize_t r = recv(fd, chunk, sizeof chunk, 0);
            if (r <= 0) return false;
            buf.append(chunk, (size_t)r);
        }
        return true;
    };
    if (te.find("chunked") != std::string::npos) {
        std::string raw = body, out;
        body.clear();
        for (;;) {
            size_t eol;
            while ((eol = raw.find("\r\n")) == std::string::npos) {
                ssize_t r = recv(fd, chunk, sizeof chunk, 0);
                if (r <= 0) { body = out; return; }
                raw.append(chunk, (size_t)r);
            }
            size_t size = strtoul(raw.substr(0, eol).c_str(), nullptr, 16);
            raw.erase(0, eol + 2);
            if (size == 0) break;
            if (!fill(raw, size + 2)) { out += raw.substr(0, std::min(size, raw.size())); body = out; return; }
            out += raw.substr(0, size);
            raw.erase(0, size + 2);
            if (out.size() > ((size_t)1 << 30)) fail("That web response is too large.");
        }
        body = out;
    } else if (!cl.empty()) {
        size_t want = (size_t)strtoull(cl.c_str(), nullptr, 10);
        if (want > ((size_t)1 << 30)) fail("That web request or response is too large.");
        fill(body, want);
        if (body.size() > want) body.resize(want);
    } else if (untilClose) {
        while (fill(body, body.size() + 1)) {}
    }
}

static Value plainHttp(const std::string& method, std::string url, const std::string& payload, const std::string& contentType,
                       const Value& headers, int redirects) {
    // http://host[:port][/path]
    std::string rest = url.substr(7);
    size_t slash = rest.find('/');
    std::string hostport = rest.substr(0, slash), path = slash == std::string::npos ? "/" : rest.substr(slash);
    std::string host = hostport, port = "80";
    size_t colon = hostport.rfind(':');
    if (colon != std::string::npos && hostport.find(']') == std::string::npos) {
        host = hostport.substr(0, colon);
        port = hostport.substr(colon + 1);
    }
    std::string request = method + " " + path + " HTTP/1.1\r\nHost: " + hostport + "\r\nConnection: close\r\nUser-Agent: Plain\r\n";
    bool hasType = false;
    if (isMap(headers))
        for (const auto& e : asMap(headers)->entries) {
            std::string name = fmt(e.first);
            if (lowerCopy(name) == "content-type") hasType = true;
            if (name.find_first_of("\r\n") != std::string::npos || fmt(e.second).find_first_of("\r\n") != std::string::npos)
                fail("A header can't contain a line break.");
            request += name + ": " + fmt(e.second) + "\r\n";
        }
    if (!contentType.empty() && !hasType) request += "Content-Type: " + contentType + "\r\n";
    if (!payload.empty() || method == "POST" || method == "PUT") request += "Content-Length: " + std::to_string(payload.size()) + "\r\n";
    request += "\r\n" + payload;

    int fd = -1;
    HttpParts head;
    Value respHeaders;
    std::string body;
    int status = 0;
    bool ok = false;
    std::string problem;
    {
        // Nothing in this block may touch Plain values except those it creates itself.
        Unlocked u;
        struct addrinfo hints, *res = nullptr;
        memset(&hints, 0, sizeof hints);
        hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) == 0) {
            for (struct addrinfo* p = res; p; p = p->ai_next) {
                fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
                if (fd < 0) continue;
                struct timeval tv;
                tv.tv_sec = 30;
                tv.tv_usec = 0;
                setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
                if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) break;
                close(fd);
                fd = -1;
            }
            freeaddrinfo(res);
        }
    }
    if (fd < 0) fail("I couldn't connect to " + host + " on port " + port + ".");
    {
        Unlocked u;
        if (sendAll(fd, request)) {
            head = readHead(fd);
            ok = head.complete;
        } else {
            problem = "I couldn't send the request.";
        }
    }
    if (!ok) {
        close(fd);
        fail("I couldn't get a proper answer from " + url + (problem.empty() ? "." : ": " + problem));
    }
    size_t eol = head.head.find("\r\n");
    std::string statusLine = head.head.substr(0, eol);
    size_t sp1 = statusLine.find(' ');
    status = sp1 == std::string::npos ? 0 : atoi(statusLine.c_str() + sp1 + 1);
    respHeaders = parseHeaders(head.head, eol == std::string::npos ? head.head.size() : eol + 2);
    body = head.rest;
    {
        std::string te = lowerCopy(headerOf(respHeaders, "transfer-encoding")), cl = headerOf(respHeaders, "content-length");
        Unlocked u;
        readBody(fd, te, cl, body, true);
    }
    close(fd);
    if ((status == 301 || status == 302 || status == 303 || status == 307 || status == 308) && redirects < 5) {
        std::string loc = headerOf(respHeaders, "location");
        if (!loc.empty()) {
            if (loc[0] == '/') loc = "http://" + hostport + loc;
            bool toGet = status == 303 || ((status == 301 || status == 302) && method == "POST");
            if (loc.compare(0, 7, "http://") == 0)
                return plainHttp(toGet ? "GET" : method, loc, toGet ? "" : payload, toGet ? "" : contentType, headers, redirects + 1);
            if (loc.compare(0, 8, "https://") == 0) fail("That web address moved to " + loc + ", which needs https. Use the https address directly.");
        }
    }
    Map* m = new Map;
    Value result = Value::obj(m);
    m->set(mkstr("status"), Value::integer(status));
    m->set(mkstr("body"), mkstr(body));
    m->set(mkstr("headers"), respHeaders);
    return result;
}

static Value urlDecodeValue(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '+') out += ' ';
        else if (s[i] == '%' && i + 2 < s.size() + 0 && isxdigit((unsigned char)s[i + 1]) && isxdigit((unsigned char)s[i + 2])) {
            out += (char)strtol(s.substr(i + 1, 2).c_str(), nullptr, 16);
            i += 2;
        } else out += s[i];
    }
    return mkstr(out);
}
BUILTIN(b_url_decode) { return urlDecodeValue(argStr("url_decode", a, 0)); }
BUILTIN(b_url_encode) {
    std::string out;
    for (unsigned char c : fmt(a[0])) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') out += (char)c;
        else { char b[4]; snprintf(b, sizeof b, "%%%02X", c); out += b; }
    }
    return mkstr(out);
}

static std::string reasonFor(int status) {
    switch (status) {
        case 200: return "OK"; case 201: return "Created"; case 204: return "No Content"; case 301: return "Moved Permanently";
        case 302: return "Found"; case 304: return "Not Modified"; case 400: return "Bad Request"; case 401: return "Unauthorized";
        case 403: return "Forbidden"; case 404: return "Not Found"; case 405: return "Method Not Allowed"; case 500: return "Internal Server Error";
        default: return "OK";
    }
}

// http_serve(server, handler [, how_many]) answers web requests that arrive on a listening
// connection (made with tcp_listen). The handler gets a map: method, path, query, headers, body.
// It gives back text, or a map with status, body and headers, or a list/map to send as JSON.
BUILTIN(b_http_serve) {
    needArgs("http_serve", n, 2, 3);
    int server = argConn("http_serve", a);
    Value handler = a[1];
    int64_t limit = n == 3 ? argInt("http_serve", a, 2) : -1;
    for (int64_t served = 0; limit < 0 || served < limit; ++served) {
        int fd;
        fflush(stdout);
        {
            Unlocked u;
            fd = accept(server, nullptr, nullptr);
        }
        if (fd < 0) fail("I couldn't accept a connection.");
        HttpParts head;
        {
            Unlocked u;
            struct timeval tv;
            tv.tv_sec = 30;
            tv.tv_usec = 0;
            setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
            head = readHead(fd);
        }
        std::string out;
        int status = 200;
        std::string body, contentType = "text/plain; charset=utf-8";
        Value extra;
        if (!head.complete) {
            close(fd);
            continue;
        }
        try {
            size_t eol = head.head.find("\r\n");
            std::string line = head.head.substr(0, eol);
            size_t s1 = line.find(' '), s2 = line.find(' ', s1 + 1);
            std::string method = line.substr(0, s1);
            std::string target = s1 == std::string::npos ? "" : line.substr(s1 + 1, s2 == std::string::npos ? std::string::npos : s2 - s1 - 1);
            std::string path = target, qs;
            size_t q = target.find('?');
            if (q != std::string::npos) { path = target.substr(0, q); qs = target.substr(q + 1); }
            Value headers = parseHeaders(head.head, eol == std::string::npos ? head.head.size() : eol + 2);
            std::string reqBody = head.rest;
            {
                std::string te = lowerCopy(headerOf(headers, "transfer-encoding")), cl = headerOf(headers, "content-length");
                Unlocked u;
                readBody(fd, te, cl, reqBody, false);
            }
            Map* query = new Map;
            Value queryV = Value::obj(query);
            size_t pos = 0;
            while (pos < qs.size()) {
                size_t amp = qs.find('&', pos);
                if (amp == std::string::npos) amp = qs.size();
                std::string pair = qs.substr(pos, amp - pos);
                pos = amp + 1;
                if (pair.empty()) continue;
                size_t eq = pair.find('=');
                Value k = urlDecodeValue(pair.substr(0, eq));
                query->set(k, eq == std::string::npos ? mkstr("") : urlDecodeValue(pair.substr(eq + 1)));
            }
            Map* req = new Map;
            Value reqV = Value::obj(req);
            req->set(mkstr("method"), mkstr(method));
            req->set(mkstr("path"), urlDecodeValue(path));
            req->set(mkstr("query"), queryV);
            req->set(mkstr("headers"), headers);
            req->set(mkstr("body"), mkstr(reqBody));
            Value reply = vm.call(handler, {reqV});
            if (isMap(reply) && (asMap(reply)->find(mkstr("status")) || asMap(reply)->find(mkstr("body")))) {
                Map* r = asMap(reply);
                if (Value* st = r->find(mkstr("status"))) {
                    int64_t code;
                    if (!wholeValue(*st, code) || code < 100 || code > 599) fail("A web reply needs a status between 100 and 599, but I got " + fmt(*st, true) + ".");
                    status = (int)code;
                }
                if (Value* b = r->find(mkstr("body"))) {
                    if (isMap(*b) || isList(*b)) { toJson(*b, body, 0, -1, 0); contentType = "application/json"; }
                    else body = fmt(*b);
                }
                if (Value* h = r->find(mkstr("headers"))) extra = *h;
            } else if (isMap(reply) || isList(reply)) {
                toJson(reply, body, 0, -1, 0);
                contentType = "application/json";
            } else {
                body = fmt(reply);
            }
        } catch (const PlainError& e) {
            status = 500;
            body = "Oops! " + e.msg;
            contentType = "text/plain; charset=utf-8";
            extra = Value();
            fprintf(stderr, "web handler failed: %s\n", e.msg.c_str());
        }
        out = "HTTP/1.1 " + std::to_string(status) + " " + reasonFor(status) + "\r\nConnection: close\r\nContent-Length: " + std::to_string(body.size()) + "\r\n";
        bool hasType = false;
        if (isMap(extra))
            for (const auto& e : asMap(extra)->entries) {
                std::string name = fmt(e.first), val = fmt(e.second);
                if (name.find_first_of("\r\n:") != std::string::npos || val.find_first_of("\r\n") != std::string::npos) continue;
                if (lowerCopy(name) == "content-type") hasType = true;
                out += name + ": " + val + "\r\n";
            }
        if (!hasType) out += "Content-Type: " + contentType + "\r\n";
        out += "\r\n" + body;
        {
            Unlocked u;
            sendAll(fd, out);
            shutdown(fd, SHUT_WR);
            close(fd);
        }
    }
    return Value();
}
#else
BUILTIN(b_no_network) { fail("Networking is not available in the Windows build of Plain yet."); }
#define b_http_get b_no_network
#define b_http_post b_no_network
#define b_http_request b_no_network
#define b_tcp_connect b_no_network
#define b_tcp_listen b_no_network
#define b_tcp_accept b_no_network
#define b_tcp_send b_no_network
#define b_tcp_receive b_no_network
#define b_tcp_receive_line b_no_network
#define b_tcp_close b_no_network
#define b_tcp_port b_no_network
#define b_http_serve b_no_network
BUILTIN(b_url_encode) { return a[0]; }
BUILTIN(b_url_decode) { return a[0]; }
#endif

// Built-in actions that are easier to write in Plain itself.
static const char* PRELUDE = R"PLAIN(
define map_each with items and work
    set out to []
    for each x in items
        add work(x) to out
    end
    give back out
end
define keep_if with items and test
    set out to []
    for each x in items
        if test(x) then
            add x to out
        end
    end
    give back out
end
define find_first with items and test
    for each x in items
        if test(x) then
            give back x
        end
    end
    give back nothing
end
define combine with items and start and work
    set total to start
    for each x in items
        set total to work(total, x)
    end
    give back total
end
define sort_by with items and key_of
    give back __sort_keys(items, map_each(items, key_of))
end
)PLAIN";

inline void registerBuiltins(Program& prog) {
    struct Entry { const char* name; int arity; NativeFn fn; };
    static const Entry table[] = {
        {"sqrt", 1, b_sqrt}, {"abs", 1, b_abs}, {"floor", 1, b_floor}, {"ceiling", 1, b_ceiling},
        {"round", -1, b_round}, {"power", 2, b_power}, {"sin", 1, b_sin}, {"cos", 1, b_cos},
        {"tan", 1, b_tan}, {"exp", 1, b_exp}, {"log", 1, b_log}, {"pi", 0, b_pi},
        {"min", -1, b_min}, {"max", -1, b_max}, {"random", -1, b_random}, {"sum", 1, b_sum},
        {"text", 1, b_text}, {"number", 1, b_number}, {"uppercase", 1, b_uppercase},
        {"lowercase", 1, b_lowercase}, {"trim", 1, b_trim}, {"split", 2, b_split}, {"join", 2, b_join},
        {"replace", 3, b_replace}, {"find", 2, b_find}, {"starts_with", 2, b_starts_with},
        {"ends_with", 2, b_ends_with}, {"slice", 3, b_slice},
        {"sort", 1, b_sort}, {"reverse", 1, b_reverse}, {"range", -1, b_range}, {"first", 1, b_first},
        {"last", 1, b_last}, {"insert", 3, b_insert}, {"index_of", 2, b_index_of}, {"copy", 1, b_copy},
        {"keys", 1, b_keys}, {"values", 1, b_values}, {"has_key", 2, b_has_key}, {"type_of", 1, b_type_of},
        {"read_file", 1, b_read_file}, {"read_lines", 1, b_read_lines}, {"write_file", 2, b_write_file},
        {"append_file", 2, b_append_file}, {"file_exists", 1, b_file_exists}, {"delete_file", 1, b_delete_file},
        {"clock", 0, b_clock}, {"time_now", 0, b_time_now}, {"date_text", -1, b_date_text}, {"wait", 1, b_wait},
        {"arguments", 0, b_arguments}, {"environment", 1, b_environment}, {"exit", -1, b_exit},
        {"to_json", -1, b_to_json}, {"from_json", 1, b_from_json},
        {"fraction", 1, b_fraction}, {"whole", 1, b_whole}, {"is_a", 2, b_is_a}, {"__sort_keys", 2, b_sort_keys},
        {"integer", 1, b_integer}, {"float", 1, b_float}, {"decimal", 1, b_decimal}, {"quotient", 2, b_quotient},
        {"fixed", 2, b_fixed}, {"is_integer", 1, b_is_integer}, {"is_decimal", 1, b_is_decimal}, {"is_float", 1, b_is_float},
        {"http_get", -1, b_http_get}, {"http_post", -1, b_http_post}, {"http_request", -1, b_http_request},
        {"tcp_connect", 2, b_tcp_connect}, {"tcp_listen", 1, b_tcp_listen}, {"tcp_accept", 1, b_tcp_accept},
        {"tcp_send", 2, b_tcp_send}, {"tcp_receive", -1, b_tcp_receive}, {"tcp_receive_line", 1, b_tcp_receive_line},
        {"tcp_close", 1, b_tcp_close}, {"tcp_port", 1, b_tcp_port}, {"http_serve", -1, b_http_serve},
        {"url_encode", 1, b_url_encode}, {"url_decode", 1, b_url_decode},
    };
    for (const Entry& e : table) prog.define(e.name, Value::obj(new Native(e.name, e.arity, e.fn)));
    registerTaskBuiltins(prog);
    // The prelude's actions behave like built-ins: programs may reuse their names.
    Compiler prelude(prog, PRELUDE, "<built-in>");
    prelude.compileMain();
    prog.funcs.clear();
    std::fill(prog.gdeclared.begin(), prog.gdeclared.end(), 0);
}

}  // namespace plain
