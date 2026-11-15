// Plain - stage 1: turn source text into tokens.
#pragma once
#include <unordered_set>

#include "value.hpp"

namespace plain {

struct Token {
    enum K { Num, Str, Word, Kw, Sym, Poss, NL, End };
    K k;
    std::string text;
    int numKind = 0;  // for Num: 0 whole, 1 float, 2 decimal
    int line = 0;
    int depth = 0;    // for NL: how many brackets are open here
    size_t pos = 0, end = 0;  // where the token sits in the source text
};

inline const std::unordered_set<std::string>& keywords() {
    static const std::unordered_set<std::string> kw = {
        "set", "to", "say", "show", "print", "ask", "into", "add", "remove", "from",
        "increase", "decrease", "by", "if", "then", "otherwise", "end", "repeat",
        "times", "while", "for", "each", "in", "define", "with", "give", "back",
        "stop", "skip", "is", "not", "and", "or", "greater", "less", "than", "at",
        "least", "most", "equal", "contains", "plus", "minus", "multiplied",
        "divided", "modulo", "length", "of", "item", "true", "false", "nothing",
        "action", "gives", "class", "extends", "new", "me", "parent",
    };
    return kw;
}

inline bool isIdStart(char c) { return isalpha((unsigned char)c) || c == '_' || (unsigned char)c >= 0x80; }
inline bool isIdChar(char c) { return isIdStart(c) || isdigit((unsigned char)c); }

inline std::vector<Token> tokenize(const std::string& src) {
    std::vector<Token> toks;
    int line = 1, depth = 0;
    size_t i = 0, n = src.size();
    bool lineStart = true;
    size_t curStart = 0, counted = 0;
    auto push = [&](Token::K k, std::string text, int numKind = 0) {
        Token t;
        t.k = k;
        t.text = std::move(text);
        t.numKind = numKind;
        t.line = line;
        t.depth = depth;
        t.pos = curStart;
        toks.push_back(std::move(t));
    };
    auto skipLine = [&]() {
        while (i < n && src[i] != '\n') ++i;
    };
    while (i < n) {
        if (toks.size() > counted) { toks.back().end = i; counted = toks.size(); }
        curStart = i;
        char c = src[i];
        if (c == '\n') {
            if (!toks.empty() && toks.back().k != Token::NL) push(Token::NL, "");
            ++line;
            ++i;
            lineStart = true;
            continue;
        }
        if (c == ' ' || c == '\t' || c == '\r') {
            ++i;
            continue;
        }
        if (c == '#') {
            skipLine();
            continue;
        }
        if (lineStart && i + 5 <= n) {
            std::string head = src.substr(i, 5);
            for (char& h : head) h = (char)tolower((unsigned char)h);
            if (head == "note:") {
                skipLine();
                continue;
            }
        }
        lineStart = false;
        if (isdigit((unsigned char)c)) {
            size_t j = i;
            int kind = 0;
            while (j < n && isdigit((unsigned char)src[j])) ++j;
            if (j + 1 < n && src[j] == '.' && isdigit((unsigned char)src[j + 1])) {
                kind = 1;
                ++j;
                while (j < n && isdigit((unsigned char)src[j])) ++j;
            }
            if (j < n && (src[j] == 'e' || src[j] == 'E')) {
                size_t k = j + 1;
                if (k < n && (src[k] == '+' || src[k] == '-')) ++k;
                if (k < n && isdigit((unsigned char)src[k])) {
                    kind = 1;
                    while (k < n && isdigit((unsigned char)src[k])) ++k;
                    j = k;
                }
            }
            std::string text = src.substr(i, j - i);
            if (j < n && src[j] == 'd' && (j + 1 >= n || !isIdChar(src[j + 1]))) {
                kind = 2;
                ++j;
            }
            push(Token::Num, text, kind);
            i = j;
            continue;
        }
        if (c == '"') {
            std::string s;
            size_t j = i + 1;
            for (;; ++j) {
                if (j >= n || src[j] == '\n') fail("This text starts with a \" but never closes it.", line);
                if (src[j] == '"') break;
                if (src[j] == '\\' && j + 1 < n) {
                    char e = src[++j];
                    if (e == 'n') s += '\n';
                    else if (e == 't') s += '\t';
                    else if (e == 'r') s += '\r';
                    else if (e == '"') s += '"';
                    else if (e == '\\') s += '\\';
                    else { s += '\\'; s += e; }
                    continue;
                }
                s += src[j];
            }
            push(Token::Str, s);
            i = j + 1;
            continue;
        }
        if (isIdStart(c)) {
            size_t j = i;
            while (j < n && isIdChar(src[j])) ++j;
            std::string text = src.substr(i, j - i), lower = text;
            for (char& h : lower) h = (char)tolower((unsigned char)h);
            if (keywords().count(lower)) push(Token::Kw, lower);
            else push(Token::Word, text);
            i = j;
            continue;
        }
        if (c == '\'' && i + 1 < n && src[i + 1] == 's' && (i + 2 >= n || !isIdChar(src[i + 2]))) {
            push(Token::Poss, "'s");
            i += 2;
            continue;
        }
        if (i + 1 < n) {
            std::string two = src.substr(i, 2);
            if (two == "<=" || two == ">=" || two == "!=" || two == "==") {
                push(Token::Sym, two);
                i += 2;
                continue;
            }
        }
        if (strchr("+-*/%()[]{},<>=:^", c)) {
            if (c == '(' || c == '[' || c == '{') ++depth;
            if ((c == ')' || c == ']' || c == '}') && depth > 0) --depth;
            push(Token::Sym, std::string(1, c));
            ++i;
            continue;
        }
        fail(std::string("I don't understand the character '") + c + "'.", line);
    }
    if (toks.size() > counted) toks.back().end = i;
    if (!toks.empty() && toks.back().k != Token::NL) push(Token::NL, "");
    push(Token::End, "");
    return toks;
}

}  // namespace plain
