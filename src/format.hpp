// Plain - "plain format": rewrite a program into the one documented style.
//
// The style: four-space indents; comparisons and logic in words (is, is not,
// is less than, is at most, and, or, not); arithmetic in symbols (+ - * / % ^);
// items as list[i]; map entries with fixed names as person's age; "say" for
// showing; f(x) for calling; "#" for comments; "list contains x" for membership.
// The formatter only changes how a program is written, never what it does.
#pragma once
#include <string>
#include <vector>

#include "lexer.hpp"

namespace plain {

struct FormatResult {
    std::string text;
    std::vector<std::string> warnings;
    int changedLines = 0;
};

namespace fmtimpl {

using Toks = std::vector<Token>;
static const size_t NPOS = (size_t)-1;

inline Token mk(Token::K k, const std::string& text) {
    Token t;
    t.k = k;
    t.text = text;
    return t;
}
inline bool isSym(const Token& t, const char* s) { return t.k == Token::Sym && t.text == s; }
inline bool isKw(const Token& t, const char* s) { return t.k == Token::Kw && t.text == s; }
inline bool isOpen(const Token& t) { return t.k == Token::Sym && (t.text == "(" || t.text == "[" || t.text == "{"); }
inline bool isClose(const Token& t) { return t.k == Token::Sym && (t.text == ")" || t.text == "]" || t.text == "}"); }

inline size_t matchClose(const Toks& t, size_t i) {
    int d = 0;
    for (size_t j = i; j < t.size(); ++j) {
        if (isOpen(t[j])) ++d;
        else if (isClose(t[j]) && --d == 0) return j;
    }
    return NPOS;
}
inline size_t matchOpenBack(const Toks& t, size_t i) {
    int d = 0;
    for (size_t j = i + 1; j-- > 0;) {
        if (isClose(t[j])) ++d;
        else if (isOpen(t[j]) && --d == 0) return j;
    }
    return NPOS;
}
inline bool valueKw(const Token& a) {
    return a.k == Token::Kw && (a.text == "me" || a.text == "true" || a.text == "false" || a.text == "nothing");
}
// A value followed by any number of (...), [...] and 's name. Returns the index after it.
inline size_t chainEnd(const Toks& t, size_t i) {
    if (i >= t.size()) return NPOS;
    const Token& a = t[i];
    if (a.k == Token::Word || a.k == Token::Num || a.k == Token::Str || valueKw(a)) {
        ++i;
    } else if (isOpen(a)) {
        size_t c = matchClose(t, i);
        if (c == NPOS) return NPOS;
        i = c + 1;
    } else {
        return NPOS;
    }
    for (;;) {
        if (i < t.size() && (isSym(t[i], "(") || isSym(t[i], "["))) {
            size_t c = matchClose(t, i);
            if (c == NPOS) return NPOS;
            i = c + 1;
        } else if (i + 1 < t.size() && t[i].k == Token::Poss && (t[i + 1].k == Token::Word || t[i + 1].k == Token::Kw)) {
            i += 2;
        } else {
            break;
        }
    }
    return i;
}
// The start of the chain that ends just before 'end'.
inline size_t chainStart(const Toks& t, size_t end) {
    size_t j = end;
    for (;;) {
        if (j == 0) return NPOS;
        const Token& a = t[j - 1];
        if (isClose(a)) {
            size_t k = matchOpenBack(t, j - 1);
            if (k == NPOS) return NPOS;
            j = k;
            if ((isSym(t[j], "(") || isSym(t[j], "[")) && j > 0) {
                const Token& p = t[j - 1];
                bool kwName = p.k == Token::Kw && j >= 2 && t[j - 2].k == Token::Poss;
                if (p.k == Token::Word || isClose(p) || kwName) continue;
            }
            return j;
        }
        bool kwName = a.k == Token::Kw && !valueKw(a) && j >= 2 && t[j - 2].k == Token::Poss;
        if (a.k == Token::Word || a.k == Token::Num || a.k == Token::Str || valueKw(a) || kwName) {
            if (kwName) { j -= 2; continue; }
            --j;
            if (j > 0 && t[j - 1].k == Token::Poss) { --j; continue; }
            return j;
        }
        return NPOS;
    }
}

// item i of xs  ->  xs[i]
inline void rewriteItems(Toks& t) {
    for (;;) {
        size_t at = NPOS;
        for (size_t i = t.size(); i-- > 0;) {
            if (isKw(t[i], "item") && !(i + 1 < t.size() && (isKw(t[i + 1], "to") || isKw(t[i + 1], "by")))) { at = i; break; }
        }
        if (at == NPOS) return;
        size_t of = NPOS;
        int d = 0;
        for (size_t j = at + 1; j < t.size(); ++j) {
            if (isOpen(t[j])) ++d;
            else if (isClose(t[j])) --d;
            else if (d == 0 && isKw(t[j], "of")) { of = j; break; }
        }
        size_t end = of == NPOS ? NPOS : chainEnd(t, of + 1);
        if (of == NPOS || end == NPOS || of == at + 1) {
            t[at].k = Token::Word;  // leave this one alone; stop it being found again
            t[at].text = "\x01item";
            continue;
        }
        Toks out(t.begin(), t.begin() + (long)at);
        out.insert(out.end(), t.begin() + (long)of + 1, t.begin() + (long)end);
        out.push_back(mk(Token::Sym, "["));
        out.insert(out.end(), t.begin() + (long)at + 1, t.begin() + (long)of);
        out.push_back(mk(Token::Sym, "]"));
        out.insert(out.end(), t.begin() + (long)end, t.end());
        t = out;
    }
}
inline void restoreItems(Toks& t) {
    for (Token& x : t)
        if (x.k == Token::Word && x.text == "\x01item") { x.k = Token::Kw; x.text = "item"; }
}

// x is in xs  ->  xs contains x      x is not in xs  ->  not xs contains x
inline void rewriteMembership(Toks& t) {
    for (size_t i = 1; i + 1 < t.size(); ++i) {
        if (!isKw(t[i], "is")) continue;
        size_t k = i + 1;
        bool neg = false;
        if (isKw(t[k], "not")) { neg = true; ++k; }
        if (k >= t.size() || !isKw(t[k], "in")) continue;
        size_t rEnd = chainEnd(t, k + 1);
        size_t lStart = chainStart(t, i);
        if (rEnd == NPOS || lStart == NPOS) continue;
        if (rEnd < t.size()) {
            const Token& n = t[rEnd];
            bool ok = isClose(n) || isSym(n, ",") || isKw(n, "then") || isKw(n, "and") || isKw(n, "or");
            if (!ok) continue;
        }
        if (lStart > 0) {
            const Token& p = t[lStart - 1];
            bool ok = isOpen(p) || isSym(p, ",") || isSym(p, ":") || p.k == Token::Kw;
            if (p.k == Token::Kw && (p.text == "plus" || p.text == "minus" || p.text == "multiplied" || p.text == "divided" ||
                                     p.text == "modulo" || p.text == "by" || p.text == "of"))
                ok = false;
            if (!ok) continue;
        }
        Toks out(t.begin(), t.begin() + (long)lStart);
        if (neg) out.push_back(mk(Token::Kw, "not"));
        out.insert(out.end(), t.begin() + (long)k + 1, t.begin() + (long)rEnd);
        out.push_back(mk(Token::Kw, "contains"));
        out.insert(out.end(), t.begin() + (long)lStart, t.begin() + (long)i);
        out.insert(out.end(), t.begin() + (long)rEnd, t.end());
        t = out;
        i = lStart;
    }
}

inline bool identifierLike(const std::string& s) {
    if (s.empty() || !isIdStart(s[0])) return false;
    for (char c : s)
        if (!isIdChar(c)) return false;
    return true;
}

// Everything that can be rewritten one token at a time.
inline void rewriteTokens(Toks& t) {
    // call f with a, b  ->  f(a, b)
    if (t.size() >= 2 && t[0].k == Token::Word && t[0].text == "call" && t[1].k == Token::Word) {
        Toks out;
        out.push_back(t[1]);
        out.push_back(mk(Token::Sym, "("));
        size_t from = 2;
        if (t.size() > 2 && isKw(t[2], "with")) from = 3;
        out.insert(out.end(), t.begin() + (long)from, t.end());
        out.push_back(mk(Token::Sym, ")"));
        t = out;
    }
    if (!t.empty() && (isKw(t[0], "print") || isKw(t[0], "show"))) t[0].text = "say";
    rewriteItems(t);
    rewriteMembership(t);
    restoreItems(t);
    Toks out;
    for (size_t i = 0; i < t.size(); ++i) {
        const Token& a = t[i];
        if (a.k == Token::Sym) {
            if (a.text == "==" || a.text == "=") { out.push_back(mk(Token::Kw, "is")); continue; }
            if (a.text == "!=") { out.push_back(mk(Token::Kw, "is")); out.push_back(mk(Token::Kw, "not")); continue; }
            if (a.text == "<") { for (const char* w : {"is", "less", "than"}) out.push_back(mk(Token::Kw, w)); continue; }
            if (a.text == ">") { for (const char* w : {"is", "greater", "than"}) out.push_back(mk(Token::Kw, w)); continue; }
            if (a.text == "<=") { for (const char* w : {"is", "at", "most"}) out.push_back(mk(Token::Kw, w)); continue; }
            if (a.text == ">=") { for (const char* w : {"is", "at", "least"}) out.push_back(mk(Token::Kw, w)); continue; }
            // person["age"]  ->  person's age
            if (a.text == "[" && i + 2 < t.size() && t[i + 1].k == Token::Str && isSym(t[i + 2], "]") && identifierLike(t[i + 1].text) &&
                !out.empty() && (out.back().k == Token::Word || isClose(out.back()) || isKw(out.back(), "me"))) {
                out.push_back(mk(Token::Poss, "'s"));
                out.push_back(mk(Token::Word, t[i + 1].text));
                i += 2;
                continue;
            }
        }
        if (a.k == Token::Kw) {
            if (a.text == "is" && i + 1 < t.size()) {
                size_t k = i + 1;
                bool neg = isKw(t[k], "not");
                if (neg) ++k;
                if (k < t.size() && isKw(t[k], "equal")) {
                    ++k;
                    if (k < t.size() && isKw(t[k], "to")) ++k;
                    out.push_back(mk(Token::Kw, "is"));
                    if (neg) out.push_back(mk(Token::Kw, "not"));
                    i = k - 1;
                    continue;
                }
            }
            if (a.text == "plus") { out.push_back(mk(Token::Sym, "+")); continue; }
            if (a.text == "minus") { out.push_back(mk(Token::Sym, "-")); continue; }
            if (a.text == "modulo") { out.push_back(mk(Token::Sym, "%")); continue; }
            if ((a.text == "multiplied" || a.text == "divided") && i + 1 < t.size() && isKw(t[i + 1], "by")) {
                out.push_back(mk(Token::Sym, a.text == "multiplied" ? "*" : "/"));
                ++i;
                continue;
            }
        }
        out.push_back(a);
    }
    t = out;
}

inline std::string tokenText(const Token& t, const std::string& code) {
    if ((t.k == Token::Str || t.k == Token::Num) && t.end > t.pos && t.end <= code.size()) return code.substr(t.pos, t.end - t.pos);
    if (t.k == Token::Str) return quote(t.text);
    return t.text;
}

inline bool binaryOp(const Token& t) {
    return t.k == Token::Sym && (t.text == "+" || t.text == "-" || t.text == "*" || t.text == "/" || t.text == "%" || t.text == "^");
}

// Lay the tokens out with the standard spacing.
inline std::string layOut(const Toks& t, const std::string& code) {
    std::string out;
    std::vector<char> unary(t.size(), 0);
    for (size_t i = 0; i < t.size(); ++i) {
        if (!isSym(t[i], "-")) continue;
        if (i == 0) { unary[i] = 1; continue; }
        const Token& p = t[i - 1];
        if (isOpen(p) || isSym(p, ",") || isSym(p, ":") || (binaryOp(p) && !unary[i - 1] ) || (binaryOp(p) && unary[i - 1]) ||
            (p.k == Token::Kw && !valueKw(p)))
            unary[i] = 1;
    }
    for (size_t i = 0; i < t.size(); ++i) {
        const Token& a = t[i];
        if (i > 0) {
            const Token& p = t[i - 1];
            bool space = true;
            bool pKwName = p.k == Token::Kw && i >= 2 && t[i - 2].k == Token::Poss;
            if (isOpen(p) || isClose(a) || isSym(a, ",") || isSym(a, ":") || a.k == Token::Poss) space = false;
            else if (unary[i - 1]) space = false;
            else if (isSym(a, "(") && (p.k == Token::Word || isClose(p) || pKwName)) space = false;
            else if (isSym(a, "[") && (p.k == Token::Word || isClose(p) || pKwName || isKw(p, "me"))) space = false;
            out += space ? " " : "";
        }
        out += tokenText(a, code);
    }
    return out;
}

// Split a line into the code and its "#" comment (text after the mark, trimmed).
inline void splitComment(const std::string& line, std::string& code, std::string& comment, bool& hasComment) {
    hasComment = false;
    bool inStr = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (inStr) {
            if (c == '\\' && i + 1 < line.size()) ++i;
            else if (c == '"') inStr = false;
        } else if (c == '"') {
            inStr = true;
        } else if (c == '#') {
            code = line.substr(0, i);
            comment = line.substr(i + 1);
            hasComment = true;
            break;
        }
    }
    if (!hasComment) code = line;
    auto trim = [](std::string& s) {
        size_t a = s.find_first_not_of(" \t\r"), b = s.find_last_not_of(" \t\r");
        s = a == std::string::npos ? "" : s.substr(a, b - a + 1);
    };
    trim(code);
    {   // keep the comment's own indentation (it may hold a code sample); only drop trailing spaces
        size_t b = comment.find_last_not_of(" \t\r");
        comment = b == std::string::npos ? "" : comment.substr(0, b + 1);
        if (comment.find_first_not_of(" \t") == std::string::npos) comment.clear();
    }
    if (!hasComment && code.size() >= 5) {
        std::string head = code.substr(0, 5);
        for (char& h : head) h = (char)tolower((unsigned char)h);
        if (head == "note:") {
            comment = code.substr(5);
            trim(comment);
            code.clear();
            hasComment = true;
        }
    }
}

inline bool opensBlock(const Toks& t, bool inClass) {
    if (t.empty()) return false;
    const Token& f = t[0];
    if (f.k == Token::Kw && (f.text == "if" || f.text == "repeat" || f.text == "while" || f.text == "for" || f.text == "define" || f.text == "class"))
        return true;
    if (f.k == Token::Word && f.text == "try" && t.size() == 1) return true;
    if (f.k == Token::Word && f.text == "init" && inClass) return true;
    for (size_t i = 0; i < t.size(); ++i) {
        if (!isKw(t[i], "action")) continue;
        bool gives = false;
        for (size_t j = i + 1; j < t.size(); ++j)
            if (isKw(t[j], "gives")) gives = true;
        if (!gives) return true;
    }
    return false;
}

}  // namespace fmtimpl

inline FormatResult formatSource(const std::string& src) {
    using namespace fmtimpl;
    FormatResult res;
    std::vector<std::string> lines;
    {
        size_t at = 0;
        while (at <= src.size()) {
            size_t e = src.find('\n', at);
            if (e == std::string::npos) { if (at < src.size()) lines.push_back(src.substr(at)); break; }
            lines.push_back(src.substr(at, e - at));
            at = e + 1;
        }
    }
    std::vector<char> blocks;  // 'c' for a class, 'b' for any other block
    int bracketDepth = 0;
    bool lastBlank = true;
    std::string out;
    for (size_t ln = 0; ln < lines.size(); ++ln) {
        std::string raw = lines[ln];
        while (!raw.empty() && raw.back() == '\r') raw.pop_back();
        std::string code, comment;
        bool hasComment;
        splitComment(raw, code, comment, hasComment);
        if (code.empty() && !hasComment) {
            if (!lastBlank) out += "\n";
            lastBlank = true;
            continue;
        }
        lastBlank = false;
        Toks t;
        bool ok = true;
        if (!code.empty()) {
            try {
                t = tokenize(code + "\n");
            } catch (PlainError& e) {
                ok = false;
                res.warnings.push_back("Line " + std::to_string(ln + 1) + ": left as it is (" + e.msg + ")");
            }
            if (ok) {
                Toks kept;
                for (const Token& x : t)
                    if (x.k != Token::NL && x.k != Token::End) kept.push_back(x);
                t = kept;
            }
        }
        std::string body;
        if (!ok) {
            body = code;
        } else {
            rewriteTokens(t);
            body = layOut(t, code);
        }
        // Where does the line sit?
        bool inClass = !blocks.empty() && blocks.back() == 'c';
        bool closer = ok && !t.empty() && isKw(t[0], "end");
        bool middle = ok && !t.empty() && (isKw(t[0], "otherwise") || (t[0].k == Token::Word && t[0].text == "on" && t.size() > 1 && t[1].k == Token::Word && t[1].text == "error"));
        int level = (int)blocks.size();
        if (closer && !blocks.empty()) { blocks.pop_back(); level = (int)blocks.size(); }
        else if (middle && level > 0) level -= 1;
        bool continuation = ok && bracketDepth > 0 && !closer;
        if (continuation) level += 1;
        std::string text(std::string((size_t)level * 4, ' '));
        text += body;
        if (hasComment) {
            std::string c = comment.empty() ? "#" : (comment[0] == ' ' ? "#" + comment : "# " + comment);
            text += body.empty() ? c : "  " + c;
        }
        if (ok) {
            for (const Token& x : t) {
                if (isOpen(x)) ++bracketDepth;
                else if (isClose(x) && bracketDepth > 0) --bracketDepth;
            }
            if (!closer && opensBlock(t, inClass) && !(isKw(t[0], "class") && false))
                blocks.push_back(!t.empty() && isKw(t[0], "class") ? 'c' : 'b');
        }
        if (text != raw) ++res.changedLines;
        out += text + "\n";
    }
    while (out.size() >= 2 && out[out.size() - 1] == '\n' && out[out.size() - 2] == '\n') out.pop_back();
    res.text = out;
    return res;
}

}  // namespace plain
