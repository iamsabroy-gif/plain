// Plain - JSON reading and writing.
#pragma once
#include "numeric.hpp"

namespace plain {

inline Value mklist(std::vector<Value> items) {
    List* l = new List;
    l->items = std::move(items);
    return Value::obj(l);
}

inline void toJson(const Value& v, std::string& out, int depth, int indent = -1, int level = 0) {
    if (depth > 200) fail("This value is nested too deeply to turn into JSON.");
    auto newline = [&](int lv) {
        if (indent < 0) return;
        out += '\n';
        out.append((size_t)(lv * indent), ' ');
    };
    if (v.tag == Value::Int) { out += std::to_string(v.i); return; }
    if (v.tag == Value::Float) { out += std::isfinite(v.n) ? fmtNum(v.n) : "null"; return; }
    if (v.tag == Value::Bool) { out += v.b ? "true" : "false"; return; }
    if (isNumber(v)) { out += fmt(v); return; }
    if (isStr(v)) {
        out += '"';
        for (unsigned char c : asStr(v)) {
            if (c == '"') out += "\\\"";
            else if (c == '\\') out += "\\\\";
            else if (c == '\n') out += "\\n";
            else if (c == '\r') out += "\\r";
            else if (c == '\t') out += "\\t";
            else if (c < 0x20) { char b[8]; snprintf(b, sizeof b, "\\u%04x", c); out += b; }
            else out += (char)c;
        }
        out += '"';
        return;
    }
    if (isList(v)) {
        auto& items = asList(v)->items;
        if (items.empty()) { out += "[]"; return; }
        out += '[';
        for (size_t i = 0; i < items.size(); ++i) {
            if (i) out += ',';
            newline(level + 1);
            toJson(items[i], out, depth + 1, indent, level + 1);
        }
        newline(level);
        out += ']';
        return;
    }
    const Map* m = nullptr;
    Value fieldsKeep;
    if (isMap(v)) m = asMap(v);
    else if (isInstance(v)) { fieldsKeep = asInstance(v)->fields; m = asMap(fieldsKeep); }
    if (m) {
        if (m->entries.empty()) { out += "{}"; return; }
        out += '{';
        bool first = true;
        for (const auto& e : m->entries) {
            if (!first) out += ',';
            first = false;
            newline(level + 1);
            toJson(mkstr(fmt(e.first)), out, depth + 1);
            out += indent >= 0 ? ": " : ":";
            toJson(e.second, out, depth + 1, indent, level + 1);
        }
        newline(level);
        out += '}';
        return;
    }
    out += "null";
}

struct JsonReader {
    const std::string& s;
    size_t i = 0;
    [[noreturn]] void bad() { fail("This isn't valid JSON (the problem is near position " + std::to_string(i + 1) + ")."); }
    void ws() { while (i < s.size() && strchr(" \t\r\n", s[i])) ++i; }
    bool lit(const char* w) {
        size_t n = strlen(w);
        if (s.compare(i, n, w) == 0) { i += n; return true; }
        return false;
    }
    static void utf8(std::string& out, unsigned cp) {
        if (cp < 0x80) out += (char)cp;
        else if (cp < 0x800) { out += (char)(0xC0 | (cp >> 6)); out += (char)(0x80 | (cp & 0x3F)); }
        else if (cp < 0x10000) { out += (char)(0xE0 | (cp >> 12)); out += (char)(0x80 | ((cp >> 6) & 0x3F)); out += (char)(0x80 | (cp & 0x3F)); }
        else { out += (char)(0xF0 | (cp >> 18)); out += (char)(0x80 | ((cp >> 12) & 0x3F)); out += (char)(0x80 | ((cp >> 6) & 0x3F)); out += (char)(0x80 | (cp & 0x3F)); }
    }
    unsigned hex4() {
        if (i + 4 > s.size()) bad();
        unsigned v = 0;
        for (int k = 0; k < 4; ++k) {
            char c = s[i++];
            v <<= 4;
            if (c >= '0' && c <= '9') v |= (unsigned)(c - '0');
            else if (c >= 'a' && c <= 'f') v |= (unsigned)(c - 'a' + 10);
            else if (c >= 'A' && c <= 'F') v |= (unsigned)(c - 'A' + 10);
            else bad();
        }
        return v;
    }
    std::string str() {
        std::string out;
        ++i;
        for (;;) {
            if (i >= s.size()) bad();
            char c = s[i++];
            if (c == '"') return out;
            if (c != '\\') { out += c; continue; }
            if (i >= s.size()) bad();
            char e = s[i++];
            switch (e) {
                case 'n': out += '\n'; break;
                case 't': out += '\t'; break;
                case 'r': out += '\r'; break;
                case 'b': out += '\b'; break;
                case 'f': out += '\f'; break;
                case 'u': {
                    unsigned cp = hex4();
                    if (cp >= 0xD800 && cp < 0xDC00 && s.compare(i, 2, "\\u") == 0) {
                        i += 2;
                        cp = 0x10000 + ((cp - 0xD800) << 10) + (hex4() - 0xDC00);
                    }
                    utf8(out, cp);
                    break;
                }
                default: out += e;
            }
        }
    }
    Value value(int depth) {
        if (depth > 200) bad();
        ws();
        if (i >= s.size()) bad();
        char c = s[i];
        if (c == '"') return mkstr(str());
        if (c == '[') {
            ++i;
            std::vector<Value> items;
            ws();
            if (i < s.size() && s[i] == ']') { ++i; return mklist(std::move(items)); }
            for (;;) {
                items.push_back(value(depth + 1));
                ws();
                if (i < s.size() && s[i] == ',') { ++i; continue; }
                if (i < s.size() && s[i] == ']') { ++i; return mklist(std::move(items)); }
                bad();
            }
        }
        if (c == '{') {
            ++i;
            Map* m = new Map;
            Value out = Value::obj(m);
            ws();
            if (i < s.size() && s[i] == '}') { ++i; return out; }
            for (;;) {
                ws();
                if (i >= s.size() || s[i] != '"') bad();
                Value key = mkstr(str());
                ws();
                if (i >= s.size() || s[i] != ':') bad();
                ++i;
                m->set(key, value(depth + 1));
                ws();
                if (i < s.size() && s[i] == ',') { ++i; continue; }
                if (i < s.size() && s[i] == '}') { ++i; return out; }
                bad();
            }
        }
        if (lit("true")) return Value::boolean(true);
        if (lit("false")) return Value::boolean(false);
        if (lit("null")) return Value();
        if (!(c == '-' || isdigit((unsigned char)c))) bad();
        size_t j = i + 1;
        bool isFloat = false;
        while (j < s.size() && (isdigit((unsigned char)s[j]) || strchr(".eE+-", s[j]))) {
            if (strchr(".eE", s[j])) isFloat = true;
            ++j;
        }
        std::string text = s.substr(i, j - i);
        i = j;
        if (!isFloat) {
            BigInt b;
            if (!BigInt::fromString(text, b)) bad();
            return fromBig(b);
        }
        char* end = nullptr;
        double d = strtod(text.c_str(), &end);
        if (end == text.c_str() || *end) bad();
        return Value::real(d);
    }
};

inline Value jsonParse(const std::string& text) {
    JsonReader r{text};
    Value v = r.value(0);
    r.ws();
    if (r.i != r.s.size()) r.bad();
    return v;
}

}  // namespace plain
