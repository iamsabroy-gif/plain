// Plain - arithmetic across integers (any size), decimals and floats.
//
// integer + integer -> integer (grows to any size instead of overflowing)
// decimal + integer/decimal -> decimal (exact)
// float with integer -> float
// decimal with float -> an error, because it would silently lose exactness
#pragma once
#include "value.hpp"

namespace plain {

// ------------------------------------------------------------- conversions
inline Value fromBig(BigInt b) {
    int64_t small;
    if (b.fitsInt64(small)) return Value::integer(small);
    return Value::obj(new BigNum(std::move(b)));
}
inline Value fromDec(Dec d) { return Value::obj(new DecNum(std::move(d))); }

inline BigInt toBig(const Value& v) { return v.tag == Value::Int ? BigInt(v.i) : asBig(v); }
inline Dec toDec(const Value& v) {
    if (isDec(v)) return asDec(v);
    return decFromBig(toBig(v));
}
inline double toDouble(const Value& v) {
    switch (v.tag) {
        case Value::Int: return (double)v.i;
        case Value::Float: return v.n;
        default: break;
    }
    if (isBig(v)) return asBig(v).toDouble();
    return decToDouble(asDec(v));
}
inline bool isZeroNum(const Value& v) {
    switch (v.tag) {
        case Value::Int: return v.i == 0;
        case Value::Float: return v.n == 0;
        default: break;
    }
    return isDec(v) && asDec(v).u.isZero();
}

// A float that holds a whole number becomes an integer (of any size).
inline Value wholeFloatToInteger(double x) {
    if (std::fabs(x) < 9.2e18) return Value::integer((int64_t)x);
    return fromBig(BigInt::fromDouble(x));
}

[[noreturn]] inline void mixFail() {
    fail("I can't mix a decimal and a float in one calculation - it would quietly lose exactness. "
         "Use decimal(x) or float(x) to choose which one you want.");
}
inline void checkMix(const Value& a, const Value& b) {
    if ((a.tag == Value::Float && isDec(b)) || (b.tag == Value::Float && isDec(a))) mixFail();
}

// Value of a whole number as int64 (integers, and floats/decimals without a fraction).
inline bool wholeValue(const Value& v, int64_t& out) {
    if (v.tag == Value::Int) { out = v.i; return true; }
    if (v.tag == Value::Float) {
        if (v.n != std::floor(v.n) || std::fabs(v.n) >= 9.2e18) return false;
        out = (int64_t)v.n;
        return true;
    }
    if (isDec(v)) {
        if (!decIsWhole(asDec(v))) return false;
        return decTrunc(asDec(v)).fitsInt64(out);
    }
    return false;
}

// ---------------------------------------------------------------- compare
// -1, 0, 1, or 2 when the numbers cannot be ordered (not-a-number).
inline int numCompare(const Value& a, const Value& b) {
    if (a.tag == Value::Int && b.tag == Value::Int) return a.i < b.i ? -1 : (a.i > b.i ? 1 : 0);
    if (a.tag == Value::Float || b.tag == Value::Float) {
        double x = toDouble(a), y = toDouble(b);
        if (std::isnan(x) || std::isnan(y)) return 2;
        return x < y ? -1 : (x > y ? 1 : 0);
    }
    if (isDec(a) || isDec(b)) return decCmp(toDec(a), toDec(b));
    return BigInt::cmp(toBig(a), toBig(b));
}

inline size_t hashValue(const Value& v) {
    auto hi = [](int64_t x) { return std::hash<int64_t>()(x); };
    auto hd = [](double d) { uint64_t u; memcpy(&u, &d, 8); return std::hash<uint64_t>()(u); };
    switch (v.tag) {
        case Value::Int: return hi(v.i);
        case Value::Float: {
            int64_t w;
            if (wholeValue(v, w)) return hi(w);
            return hd(v.n);
        }
        case Value::Bool: return v.b ? 0x9e3779b9 : 0x7f4a7c15;
        default: break;
    }
    if (isStr(v)) return std::hash<std::string>()(asStr(v));
    if (isBig(v)) return hd(asBig(v).toDouble());
    if (isDec(v)) {
        int64_t w;
        if (wholeValue(v, w)) return hi(w);
        if (decIsWhole(asDec(v))) return hd(decToDouble(asDec(v)));
        return hd(decToDouble(asDec(v)));
    }
    return 0;
}

// ------------------------------------------------------------- arithmetic
// All of these expect two numbers; the caller has checked.
inline Value numAdd(const Value& a, const Value& b) {
    if (a.tag == Value::Int && b.tag == Value::Int) {
        int64_t r;
        if (!__builtin_add_overflow(a.i, b.i, &r)) return Value::integer(r);
        return fromBig(BigInt::add(BigInt(a.i), BigInt(b.i)));
    }
    if (a.tag == Value::Float || b.tag == Value::Float) { checkMix(a, b); return Value::real(toDouble(a) + toDouble(b)); }
    if (isDec(a) || isDec(b)) return fromDec(decAdd(toDec(a), toDec(b)));
    return fromBig(BigInt::add(toBig(a), toBig(b)));
}
inline Value numSub(const Value& a, const Value& b) {
    if (a.tag == Value::Int && b.tag == Value::Int) {
        int64_t r;
        if (!__builtin_sub_overflow(a.i, b.i, &r)) return Value::integer(r);
        return fromBig(BigInt::sub(BigInt(a.i), BigInt(b.i)));
    }
    if (a.tag == Value::Float || b.tag == Value::Float) { checkMix(a, b); return Value::real(toDouble(a) - toDouble(b)); }
    if (isDec(a) || isDec(b)) return fromDec(decSub(toDec(a), toDec(b)));
    return fromBig(BigInt::sub(toBig(a), toBig(b)));
}
inline Value numMul(const Value& a, const Value& b) {
    if (a.tag == Value::Int && b.tag == Value::Int) {
        int64_t r;
        if (!__builtin_mul_overflow(a.i, b.i, &r)) return Value::integer(r);
        return fromBig(BigInt::mul(BigInt(a.i), BigInt(b.i)));
    }
    if (a.tag == Value::Float || b.tag == Value::Float) { checkMix(a, b); return Value::real(toDouble(a) * toDouble(b)); }
    if (isDec(a) || isDec(b)) return fromDec(decMul(toDec(a), toDec(b)));
    return fromBig(BigInt::mul(toBig(a), toBig(b)));
}
// Exact when it divides evenly, otherwise a float (or a decimal, for decimals).
inline Value numDiv(const Value& a, const Value& b) {
    if (isZeroNum(b)) fail("I can't divide by zero.");
    if (a.tag == Value::Float || b.tag == Value::Float) { checkMix(a, b); return Value::real(toDouble(a) / toDouble(b)); }
    if (isDec(a) || isDec(b)) return fromDec(decDiv(toDec(a), toDec(b)));
    if (a.tag == Value::Int && b.tag == Value::Int) {
        if (!(a.i == INT64_MIN && b.i == -1)) {
            if (a.i % b.i == 0) return Value::integer(a.i / b.i);
            return Value::real((double)a.i / (double)b.i);
        }
    }
    BigInt q, r;
    BigInt::divmodTrunc(toBig(a), toBig(b), q, r);
    if (r.isZero()) return fromBig(q);
    return Value::real(decToDouble(decDiv(decFromBig(toBig(a)), decFromBig(toBig(b)))));
}
// Remainder with the sign of the divisor.
inline Value numMod(const Value& a, const Value& b) {
    if (isZeroNum(b)) fail("I can't divide by zero.");
    if (a.tag == Value::Int && b.tag == Value::Int) {
        if (b.i == -1) return Value::integer(0);
        int64_t r = a.i % b.i;
        if (r != 0 && ((r < 0) != (b.i < 0))) r += b.i;
        return Value::integer(r);
    }
    if (a.tag == Value::Float || b.tag == Value::Float) {
        checkMix(a, b);
        double x = toDouble(a), y = toDouble(b);
        double r = std::fmod(x, y);
        if (r != 0 && ((r < 0) != (y < 0))) r += y;
        return Value::real(r);
    }
    if (isDec(a) || isDec(b)) return fromDec(decMod(toDec(a), toDec(b)));
    BigInt q, r;
    BigInt::divmodFloor(toBig(a), toBig(b), q, r);
    return fromBig(r);
}
// Whole-number division, rounding down.
inline Value numQuotient(const Value& a, const Value& b) {
    if (isZeroNum(b)) fail("I can't divide by zero.");
    if (a.tag == Value::Float || b.tag == Value::Float) {
        checkMix(a, b);
        double q = std::floor(toDouble(a) / toDouble(b));
        if (!std::isfinite(q)) fail("That quotient is too large to be a whole number.");
        return wholeFloatToInteger(q);
    }
    if (isDec(a) || isDec(b)) return fromBig(decFloorDiv(toDec(a), toDec(b)));
    BigInt q, r;
    BigInt::divmodFloor(toBig(a), toBig(b), q, r);
    return fromBig(q);
}
inline Value numNeg(const Value& a) {
    if (a.tag == Value::Int) {
        if (a.i == INT64_MIN) return fromBig(BigInt(a.i).negated());
        return Value::integer(-a.i);
    }
    if (a.tag == Value::Float) return Value::real(-a.n);
    if (isDec(a)) return fromDec(decNeg(asDec(a)));
    return fromBig(asBig(a).negated());
}
inline Value numAbs(const Value& a) {
    return numCompare(a, Value::integer(0)) == -1 ? numNeg(a) : a;
}

inline Value numPow(const Value& a, const Value& b) {
    int64_t e = 0;
    bool wholeExp = b.tag == Value::Int;
    if (wholeExp) e = b.i;
    if (a.tag == Value::Float || b.tag == Value::Float) {
        checkMix(a, b);
        return Value::real(std::pow(toDouble(a), toDouble(b)));
    }
    if (isDec(b) || isBig(b)) {
        if (isDec(a) || isDec(b)) fail("A decimal can only be raised to a whole-number power. Use float(x) ^ y for other powers.");
        return Value::real(std::pow(toDouble(a), toDouble(b)));
    }
    if (isDec(a)) {
        const Dec& d = asDec(a);
        uint64_t n = e < 0 ? (uint64_t)(-(e + 1)) + 1 : (uint64_t)e;
        if ((double)d.scale * (double)n > DEC_MAX_SCALE || (double)d.u.bitLength() * (double)n > 4000000.0)
            fail("That power is too large for me to work out.");
        Dec p;
        p.u = BigInt::pow(d.u, n);
        p.scale = (int)(d.scale * (int64_t)n);
        if (e >= 0) return fromDec(p);
        return fromDec(decDiv(decFromBig(BigInt(1)), p));
    }
    // integer ^ integer
    if (e < 0) return Value::real(std::pow(toDouble(a), (double)e));
    BigInt base = toBig(a);
    if (base.isZero() || (base.mag.size() == 1 && base.mag[0] == 1)) {
        if (e == 0) return Value::integer(1);
        if (base.isZero()) return Value::integer(0);
        return Value::integer(base.neg && (e & 1) ? -1 : 1);
    }
    if ((double)base.bitLength() * (double)e > 4000000.0) fail("That power is too large for me to work out.");
    return fromBig(BigInt::pow(base, (uint64_t)e));
}

// -------------------------------------------------------------- conversions
// Number text -> number: whole text becomes an integer, text with a point a float.
inline bool parseNumberText(const std::string& text, Value& out) {
    if (text.empty()) return false;
    size_t i = (text[0] == '-' || text[0] == '+') ? 1 : 0;
    if (i >= text.size()) return false;
    int dots = 0, digits = 0;
    for (size_t j = i; j < text.size(); ++j) {
        if (text[j] == '.') ++dots;
        else if (isdigit((unsigned char)text[j])) ++digits;
        else return false;
    }
    if (dots > 1 || digits == 0) return false;
    if (dots == 0) {
        BigInt b;
        if (!BigInt::fromString(text, b)) return false;
        out = fromBig(b);
    } else {
        out = Value::real(strtod(text.c_str(), nullptr));
    }
    return true;
}

// What the user typed in answer to 'ask': a number when it looks like one.
inline Value parseInput(std::string line) {
    size_t a = line.find_first_not_of(" \t\r\n"), b = line.find_last_not_of(" \t\r\n");
    line = a == std::string::npos ? "" : line.substr(a, b - a + 1);
    Value n;
    if (parseNumberText(line, n)) return n;
    return mkstr(line);
}

// Literal in a program: kind 0 whole, 1 float (point or exponent), 2 decimal (ends in d).
inline Value numberLiteral(const std::string& text, int kind, bool negate) {
    std::string t = negate ? "-" + text : text;
    if (kind == 0) {
        BigInt b;
        BigInt::fromString(t, b);
        return fromBig(b);
    }
    if (kind == 1) return Value::real(strtod(t.c_str(), nullptr));
    Dec d;
    if (!decFromString(t, d)) fail("I can't read '" + text + "' as a decimal number.");
    return fromDec(d);
}

inline Value toInteger(const Value& v) {
    if (v.tag == Value::Int || isBig(v)) return v;
    if (v.tag == Value::Float) {
        if (!std::isfinite(v.n)) fail("I can't turn " + fmt(v) + " into an integer.");
        return wholeFloatToInteger(std::trunc(v.n));
    }
    if (isDec(v)) return fromBig(decTrunc(asDec(v)));
    if (isStr(v)) {
        Dec d;
        const std::string& s = asStr(v);
        size_t a = s.find_first_not_of(" \t\r\n"), b = s.find_last_not_of(" \t\r\n");
        std::string t = a == std::string::npos ? "" : s.substr(a, b - a + 1);
        if (decFromString(t, d)) return fromBig(decTrunc(d));
        fail("I can't turn " + quote(s) + " into an integer.");
    }
    if (v.tag == Value::Bool) return Value::integer(v.b ? 1 : 0);
    fail("I can't turn " + describe(v) + " into an integer.");
}
inline Value toFloat(const Value& v) {
    if (isNumber(v)) return Value::real(toDouble(v));
    if (isStr(v)) {
        const std::string& s = asStr(v);
        char* end = nullptr;
        double d = strtod(s.c_str(), &end);
        while (end && *end && isspace((unsigned char)*end)) ++end;
        if (!s.empty() && end && *end == 0 && end != s.c_str()) return Value::real(d);
        fail("I can't turn " + quote(s) + " into a float.");
    }
    if (v.tag == Value::Bool) return Value::real(v.b ? 1 : 0);
    fail("I can't turn " + describe(v) + " into a float.");
}
inline Value toDecimal(const Value& v) {
    if (isDec(v)) return v;
    if (v.tag == Value::Int || isBig(v)) return fromDec(decFromBig(toBig(v)));
    if (v.tag == Value::Float) {
        Dec d;
        if (!decFromDouble(v.n, d)) fail("I can't turn " + fmt(v) + " into a decimal.");
        return fromDec(d);
    }
    if (isStr(v)) {
        Dec d;
        const std::string& s = asStr(v);
        size_t a = s.find_first_not_of(" \t\r\n"), b = s.find_last_not_of(" \t\r\n");
        std::string t = a == std::string::npos ? "" : s.substr(a, b - a + 1);
        if (decFromString(t, d)) return fromDec(d);
        fail("I can't turn " + quote(s) + " into a decimal.");
    }
    fail("I can't turn " + describe(v) + " into a decimal.");
}

// Round to a number of places after the point (half away from zero).
inline Value numRound(const Value& v, long places) {
    if (v.tag == Value::Int || isBig(v)) {
        if (places >= 0) return v;
        return fromBig(decRound(decFromBig(toBig(v)), places).u);
    }
    if (isDec(v)) return fromDec(decRound(asDec(v), places));
    double x = v.n, scale = std::pow(10.0, (double)places);
    if (!std::isfinite(x) || !std::isfinite(scale) || scale == 0) return v;
    return Value::real(std::round(x * scale) / scale);
}

// Text with exactly this many digits after the point.
inline std::string fixedText(const Value& v, long places) {
    if (places < 0) places = 0;
    if (places > 1000) fail("'fixed' can show at most 1000 digits after the point.");
    if (v.tag == Value::Float) {
        char buf[1500];
        snprintf(buf, sizeof buf, "%.*f", (int)places, v.n);
        return buf;
    }
    Dec d = decRound(toDec(v), places);
    return decToString(d);
}

}  // namespace plain
