// Plain - arbitrary-size integers and exact decimals (no external libraries).
#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

namespace plain {

struct BigInt {
    bool neg = false;
    std::vector<uint32_t> mag;  // little-endian limbs; empty means zero

    BigInt() {}
    explicit BigInt(int64_t v) {
        neg = v < 0;
        uint64_t u = neg ? (uint64_t)0 - (uint64_t)v : (uint64_t)v;
        while (u) { mag.push_back((uint32_t)u); u >>= 32; }
    }

    bool isZero() const { return mag.empty(); }
    void trim() {
        while (!mag.empty() && mag.back() == 0) mag.pop_back();
        if (mag.empty()) neg = false;
    }

    bool fitsInt64(int64_t& out) const {
        if (mag.size() > 2) return false;
        uint64_t u = 0;
        if (mag.size() > 0) u = mag[0];
        if (mag.size() > 1) u |= (uint64_t)mag[1] << 32;
        if (neg) {
            if (u > ((uint64_t)1 << 63)) return false;
            out = (int64_t)((uint64_t)0 - u);
            return true;
        }
        if (u > (uint64_t)INT64_MAX) return false;
        out = (int64_t)u;
        return true;
    }

    size_t bitLength() const {
        if (mag.empty()) return 0;
        return (mag.size() - 1) * 32 + (32 - (size_t)__builtin_clz(mag.back()));
    }

    // Correctly rounded conversion to double (may give infinity).
    double toDouble() const {
        if (mag.empty()) return 0;
        size_t L = bitLength();
        double d;
        if (L <= 64) {
            uint64_t u = mag[0];
            if (mag.size() > 1) u |= (uint64_t)mag[1] << 32;
            d = (double)u;
        } else {
            size_t shift = L - 64;
            uint64_t top = 0;
            for (size_t i = 0; i < 64; ++i) {
                size_t bit = shift + i;
                if ((mag[bit / 32] >> (bit % 32)) & 1) top |= (uint64_t)1 << i;
            }
            bool sticky = false;
            for (size_t bit = 0; bit < shift && !sticky; ++bit)
                if ((mag[bit / 32] >> (bit % 32)) & 1) sticky = true;
            if (sticky) top |= 1;
            d = std::ldexp((double)top, (int)std::min<size_t>(shift, 100000));
        }
        return neg ? -d : d;
    }

    // d must be a whole number.
    static BigInt fromDouble(double d) {
        bool n = d < 0;
        d = std::fabs(d);
        BigInt r;
        if (d < 9223372036854775808.0) {
            r = BigInt((int64_t)d);
        } else {
            int e;
            double m = std::frexp(d, &e);  // d = m * 2^e, 0.5 <= m < 1
            uint64_t mant = (uint64_t)std::ldexp(m, 53);
            r = BigInt((int64_t)mant);
            r = shiftLeft(r, (size_t)(e - 53));
        }
        r.neg = n && !r.isZero();
        return r;
    }

    static BigInt shiftLeft(const BigInt& a, size_t bits) {
        if (a.isZero()) return a;
        BigInt r;
        size_t limbs = bits / 32, s = bits % 32;
        r.mag.assign(limbs, 0);
        uint32_t carry = 0;
        for (uint32_t x : a.mag) {
            r.mag.push_back(s ? (uint32_t)((x << s) | carry) : x);
            carry = s ? (x >> (32 - s)) : 0;
        }
        if (carry) r.mag.push_back(carry);
        r.neg = a.neg;
        return r;
    }

    static int cmpMag(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
        for (size_t i = a.size(); i-- > 0;)
            if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
        return 0;
    }
    static int cmp(const BigInt& a, const BigInt& b) {
        if (a.neg != b.neg) return a.neg ? -1 : 1;
        int c = cmpMag(a.mag, b.mag);
        return a.neg ? -c : c;
    }

    static std::vector<uint32_t> addMag(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
        std::vector<uint32_t> r;
        r.reserve(std::max(a.size(), b.size()) + 1);
        uint64_t carry = 0;
        for (size_t i = 0; i < std::max(a.size(), b.size()); ++i) {
            uint64_t s = carry + (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
            r.push_back((uint32_t)s);
            carry = s >> 32;
        }
        if (carry) r.push_back((uint32_t)carry);
        return r;
    }
    // requires a >= b
    static std::vector<uint32_t> subMag(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
        std::vector<uint32_t> r;
        r.reserve(a.size());
        int64_t borrow = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            int64_t d = (int64_t)a[i] - borrow - (i < b.size() ? (int64_t)b[i] : 0);
            borrow = d < 0 ? 1 : 0;
            r.push_back((uint32_t)d);
        }
        while (!r.empty() && r.back() == 0) r.pop_back();
        return r;
    }

    static BigInt add(const BigInt& a, const BigInt& b) {
        BigInt r;
        if (a.neg == b.neg) {
            r.mag = addMag(a.mag, b.mag);
            r.neg = a.neg;
        } else {
            int c = cmpMag(a.mag, b.mag);
            if (c == 0) return r;
            if (c > 0) { r.mag = subMag(a.mag, b.mag); r.neg = a.neg; }
            else { r.mag = subMag(b.mag, a.mag); r.neg = b.neg; }
        }
        r.trim();
        return r;
    }
    BigInt negated() const {
        BigInt r = *this;
        if (!r.isZero()) r.neg = !r.neg;
        return r;
    }
    static BigInt sub(const BigInt& a, const BigInt& b) { return add(a, b.negated()); }

    static BigInt mul(const BigInt& a, const BigInt& b) {
        BigInt r;
        if (a.isZero() || b.isZero()) return r;
        r.mag.assign(a.mag.size() + b.mag.size(), 0);
        for (size_t i = 0; i < a.mag.size(); ++i) {
            uint64_t carry = 0;
            for (size_t j = 0; j < b.mag.size(); ++j) {
                uint64_t cur = (uint64_t)a.mag[i] * b.mag[j] + r.mag[i + j] + carry;
                r.mag[i + j] = (uint32_t)cur;
                carry = cur >> 32;
            }
            size_t k = i + b.mag.size();
            while (carry) {
                uint64_t cur = (uint64_t)r.mag[k] + carry;
                r.mag[k] = (uint32_t)cur;
                carry = cur >> 32;
                ++k;
            }
        }
        r.neg = a.neg != b.neg;
        r.trim();
        return r;
    }

    static uint32_t divSmall(std::vector<uint32_t>& a, uint32_t d) {  // in place, returns remainder
        uint64_t rem = 0;
        for (size_t i = a.size(); i-- > 0;) {
            uint64_t cur = (rem << 32) | a[i];
            a[i] = (uint32_t)(cur / d);
            rem = cur % d;
        }
        while (!a.empty() && a.back() == 0) a.pop_back();
        return (uint32_t)rem;
    }

    // Truncating division of magnitudes (Knuth, algorithm D). b must not be zero.
    static void divmodMag(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b,
                          std::vector<uint32_t>& q, std::vector<uint32_t>& r) {
        if (cmpMag(a, b) < 0) { q.clear(); r = a; return; }
        if (b.size() == 1) {
            q = a;
            uint32_t rr = divSmall(q, b[0]);
            r.clear();
            if (rr) r.push_back(rr);
            return;
        }
        int s = __builtin_clz(b.back());
        std::vector<uint32_t> v(b.size()), u(a.size() + 1);
        for (size_t i = b.size(); i-- > 0;)
            v[i] = (b[i] << s) | (s && i > 0 ? (b[i - 1] >> (32 - s)) : 0);
        u[a.size()] = s ? (a.back() >> (32 - s)) : 0;
        for (size_t i = a.size(); i-- > 0;)
            u[i] = (a[i] << s) | (s && i > 0 ? (a[i - 1] >> (32 - s)) : 0);
        size_t n = v.size(), m = a.size() - n;
        q.assign(m + 1, 0);
        for (size_t j = m + 1; j-- > 0;) {
            uint64_t num = ((uint64_t)u[j + n] << 32) | u[j + n - 1];
            uint64_t qhat = num / v[n - 1], rhat = num % v[n - 1];
            while (qhat >= ((uint64_t)1 << 32) || qhat * v[n - 2] > ((rhat << 32) | u[j + n - 2])) {
                --qhat;
                rhat += v[n - 1];
                if (rhat >= ((uint64_t)1 << 32)) break;
            }
            int64_t borrow = 0;
            uint64_t carry = 0;
            for (size_t i = 0; i < n; ++i) {
                uint64_t p = qhat * v[i] + carry;
                carry = p >> 32;
                int64_t t = (int64_t)u[i + j] - borrow - (int64_t)(p & 0xFFFFFFFFu);
                u[i + j] = (uint32_t)t;
                borrow = t < 0 ? 1 : 0;
            }
            int64_t t = (int64_t)u[j + n] - borrow - (int64_t)carry;
            u[j + n] = (uint32_t)t;
            if (t < 0) {
                --qhat;
                uint64_t c = 0;
                for (size_t i = 0; i < n; ++i) {
                    uint64_t sum = (uint64_t)u[i + j] + v[i] + c;
                    u[i + j] = (uint32_t)sum;
                    c = sum >> 32;
                }
                u[j + n] += (uint32_t)c;
            }
            q[j] = (uint32_t)qhat;
        }
        r.assign(n, 0);
        for (size_t i = 0; i < n; ++i)
            r[i] = (u[i] >> s) | (s ? (uint32_t)((uint64_t)u[i + 1] << (32 - s)) : 0);
        while (!q.empty() && q.back() == 0) q.pop_back();
        while (!r.empty() && r.back() == 0) r.pop_back();
    }

    // Truncating division (rounds toward zero), like C.
    static void divmodTrunc(const BigInt& a, const BigInt& b, BigInt& q, BigInt& r) {
        std::vector<uint32_t> qm, rm;
        divmodMag(a.mag, b.mag, qm, rm);
        q.mag = qm; q.neg = a.neg != b.neg; q.trim();
        r.mag = rm; r.neg = a.neg; r.trim();
    }
    // Floor division (rounds toward minus infinity), like Plain's 'modulo'.
    static void divmodFloor(const BigInt& a, const BigInt& b, BigInt& q, BigInt& r) {
        divmodTrunc(a, b, q, r);
        if (!r.isZero() && r.neg != b.neg) {
            q = sub(q, BigInt(1));
            r = add(r, b);
        }
    }

    static BigInt pow(BigInt base, uint64_t e) {
        BigInt result(1);
        while (e) {
            if (e & 1) result = mul(result, base);
            e >>= 1;
            if (e) base = mul(base, base);
        }
        return result;
    }
    static const BigInt& pow10(size_t n) {
        static std::vector<BigInt> table(1, BigInt(1));
        while (table.size() <= n) table.push_back(mul(table.back(), BigInt(10)));
        return table[n];
    }

    std::string toString() const {
        if (mag.empty()) return "0";
        std::vector<uint32_t> t = mag;
        std::vector<uint32_t> chunks;
        while (!t.empty()) chunks.push_back(divSmall(t, 1000000000u));
        std::string s = neg ? "-" : "";
        char buf[16];
        snprintf(buf, sizeof buf, "%u", chunks.back());
        s += buf;
        for (size_t i = chunks.size() - 1; i-- > 0;) {
            snprintf(buf, sizeof buf, "%09u", chunks[i]);
            s += buf;
        }
        return s;
    }
    size_t digits() const {
        std::string s = toString();
        return s.size() - (neg ? 1 : 0);
    }

    // Optional sign followed by digits only.
    static bool fromString(const std::string& text, BigInt& out) {
        size_t i = 0;
        bool n = false;
        if (i < text.size() && (text[i] == '-' || text[i] == '+')) { n = text[i] == '-'; ++i; }
        if (i >= text.size()) return false;
        BigInt r;
        for (size_t j = i; j < text.size(); ++j)
            if (text[j] < '0' || text[j] > '9') return false;
        while (i < text.size()) {
            size_t take = std::min<size_t>(9, text.size() - i);
            uint32_t chunk = 0, scale = 1;
            for (size_t k = 0; k < take; ++k) { chunk = chunk * 10 + (uint32_t)(text[i + k] - '0'); scale *= 10; }
            // r = r * scale + chunk
            uint64_t carry = chunk;
            for (size_t k = 0; k < r.mag.size(); ++k) {
                uint64_t cur = (uint64_t)r.mag[k] * scale + carry;
                r.mag[k] = (uint32_t)cur;
                carry = cur >> 32;
            }
            if (carry) r.mag.push_back((uint32_t)carry);
            i += take;
        }
        r.neg = n;
        r.trim();
        out = r;
        return true;
    }
};

// ---------------------------------------------------------------- decimals
// value = u / 10^scale, with scale >= 0. The scale is kept, so 2.50 stays 2.50.
struct Dec {
    BigInt u;
    int scale = 0;
};

static const int DEC_PRECISION = 28;
static const int DEC_MAX_SCALE = 100000;

inline Dec decFromBig(const BigInt& b) { Dec d; d.u = b; return d; }

inline bool decFromString(const std::string& text, Dec& out) {
    size_t i = 0, n = text.size();
    bool neg = false;
    if (i < n && (text[i] == '-' || text[i] == '+')) { neg = text[i] == '-'; ++i; }
    std::string digits;
    int frac = 0;
    bool seenDot = false, any = false;
    for (; i < n; ++i) {
        char c = text[i];
        if (c >= '0' && c <= '9') { digits += c; any = true; if (seenDot) ++frac; }
        else if (c == '.' && !seenDot) seenDot = true;
        else break;
    }
    if (!any) return false;
    long exp = 0;
    if (i < n && (text[i] == 'e' || text[i] == 'E')) {
        ++i;
        bool en = false;
        if (i < n && (text[i] == '-' || text[i] == '+')) { en = text[i] == '-'; ++i; }
        if (i >= n) return false;
        for (; i < n; ++i) {
            if (text[i] < '0' || text[i] > '9') return false;
            exp = exp * 10 + (text[i] - '0');
            if (exp > 100000) return false;
        }
        if (en) exp = -exp;
    }
    if (i != n) return false;
    BigInt u;
    BigInt::fromString(digits, u);
    long scale = frac - exp;
    if (scale < 0) {
        u = BigInt::mul(u, BigInt::pow10((size_t)-scale));
        scale = 0;
    }
    if (scale > DEC_MAX_SCALE) return false;
    u.neg = neg && !u.isZero();
    out.u = u;
    out.scale = (int)scale;
    return true;
}

inline std::string decToString(const Dec& d) {
    std::string s = d.u.toString();
    bool neg = !s.empty() && s[0] == '-';
    if (neg) s.erase(0, 1);
    if (d.scale > 0) {
        if ((int)s.size() <= d.scale) s = std::string((size_t)(d.scale - (int)s.size() + 1), '0') + s;
        s.insert(s.size() - (size_t)d.scale, ".");
    }
    return neg ? "-" + s : s;
}

inline Dec decRescale(const Dec& d, int scale) {  // scale >= d.scale
    Dec r;
    r.u = scale == d.scale ? d.u : BigInt::mul(d.u, BigInt::pow10((size_t)(scale - d.scale)));
    r.scale = scale;
    return r;
}
inline int decCmp(const Dec& a, const Dec& b) {
    int s = std::max(a.scale, b.scale);
    return BigInt::cmp(decRescale(a, s).u, decRescale(b, s).u);
}
inline Dec decAdd(const Dec& a, const Dec& b) {
    int s = std::max(a.scale, b.scale);
    Dec r;
    r.u = BigInt::add(decRescale(a, s).u, decRescale(b, s).u);
    r.scale = s;
    return r;
}
inline Dec decNeg(const Dec& a) { Dec r = a; r.u = a.u.negated(); return r; }
inline Dec decSub(const Dec& a, const Dec& b) { return decAdd(a, decNeg(b)); }
inline Dec decMul(const Dec& a, const Dec& b) {
    Dec r;
    r.u = BigInt::mul(a.u, b.u);
    r.scale = a.scale + b.scale;
    return r;
}

// Divide the magnitude by 10^n, rounding half away from zero.
inline BigInt roundDivPow10(const BigInt& x, size_t n) {
    if (n == 0) return x;
    BigInt mag = x;
    mag.neg = false;
    BigInt q, r;
    BigInt::divmodTrunc(mag, BigInt::pow10(n), q, r);
    BigInt twice = BigInt::mul(r, BigInt(2));
    if (BigInt::cmp(twice, BigInt::pow10(n)) >= 0) q = BigInt::add(q, BigInt(1));
    q.neg = x.neg && !q.isZero();
    return q;
}

// Round to a number of digits after the point (negative rounds to tens, hundreds...).
inline Dec decRound(const Dec& d, long places) {
    Dec r;
    long shift = (long)d.scale - places;
    if (shift > 0) {
        BigInt q = roundDivPow10(d.u, (size_t)shift);
        if (places >= 0) { r.u = q; r.scale = (int)places; }
        else { r.u = BigInt::mul(q, BigInt::pow10((size_t)-places)); r.scale = 0; }
    } else if (places >= 0) {
        if (places > DEC_MAX_SCALE) places = DEC_MAX_SCALE;
        r = decRescale(d, (int)places);
    } else {
        r = d;
    }
    return r;
}

// Division to 28 significant digits (exact results keep their natural scale). b must not be zero.
inline Dec decDiv(const Dec& a, const Dec& b) {
    BigInt n = a.u, dd = b.u;
    bool neg = n.neg != dd.neg;
    n.neg = dd.neg = false;
    if (n.isZero()) { Dec z; z.scale = std::max(a.scale - b.scale, 0); return z; }
    long diff = (long)n.digits() - (long)dd.digits();
    long k = std::max(0L, (long)DEC_PRECISION + 3 - diff);
    BigInt q, r;
    BigInt::divmodTrunc(BigInt::mul(n, BigInt::pow10((size_t)k)), dd, q, r);
    long scale = (long)a.scale + k - (long)b.scale;
    if (scale < 0) {
        q = BigInt::mul(q, BigInt::pow10((size_t)-scale));
        scale = 0;
    }
    size_t qd = q.digits();
    while (qd > (size_t)DEC_PRECISION && scale > 0) {
        long drop = std::min<long>((long)qd - DEC_PRECISION, scale);
        q = roundDivPow10(q, (size_t)drop);
        scale -= drop;
        qd = q.digits();
    }
    if (r.isZero()) {
        long ideal = std::max(a.scale - b.scale, 0);
        while (scale > ideal) {
            BigInt q2, r2;
            BigInt::divmodTrunc(q, BigInt(10), q2, r2);
            if (!r2.isZero()) break;
            q = q2;
            --scale;
        }
    }
    q.neg = neg && !q.isZero();
    Dec out;
    out.u = q;
    out.scale = (int)scale;
    return out;
}

// Remainder with the sign of the divisor (like 'modulo'). b must not be zero.
inline Dec decMod(const Dec& a, const Dec& b) {
    int s = std::max(a.scale, b.scale);
    BigInt q, r;
    BigInt::divmodFloor(decRescale(a, s).u, decRescale(b, s).u, q, r);
    Dec out;
    out.u = r;
    out.scale = s;
    return out;
}

// Floor of the quotient as a whole number.
inline BigInt decFloorDiv(const Dec& a, const Dec& b) {
    int s = std::max(a.scale, b.scale);
    BigInt q, r;
    BigInt::divmodFloor(decRescale(a, s).u, decRescale(b, s).u, q, r);
    return q;
}
inline BigInt decFloor(const Dec& d) {
    BigInt q, r;
    BigInt::divmodFloor(d.u, BigInt::pow10((size_t)d.scale), q, r);
    return q;
}
inline BigInt decTrunc(const Dec& d) {
    BigInt q, r;
    BigInt::divmodTrunc(d.u, BigInt::pow10((size_t)d.scale), q, r);
    return q;
}
inline bool decIsWhole(const Dec& d) {
    BigInt q, r;
    BigInt::divmodTrunc(d.u, BigInt::pow10((size_t)d.scale), q, r);
    return r.isZero();
}
inline double decToDouble(const Dec& d) { return strtod(decToString(d).c_str(), nullptr); }

// The shortest text that reads back as the same double, as a decimal ("0.1" for 0.1).
inline bool decFromDouble(double x, Dec& out) {
    if (!std::isfinite(x)) return false;
    char buf[64];
    for (int p = 1; p <= 17; ++p) {
        snprintf(buf, sizeof buf, "%.*g", p, x);
        if (strtod(buf, nullptr) == x) break;
    }
    return decFromString(buf, out);
}

}  // namespace plain
