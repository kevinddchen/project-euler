#pragma once

#include "common.h"

#include <functional>
#include <numeric>

namespace mf
{

/**
 * Fraction class. Denominator is always positive.
 */
struct Frac {
    long numer;
    long denom;

    Frac() : numer(0), denom(1) {}

    Frac(long a) : numer(a), denom(1) {}

    Frac(long a, long b) : numer(a), denom(b)
    {
        assert(denom != 0);
        if (denom < 0) {
            numer *= -1;
            denom *= -1;
        }
        const long d = std::gcd(numer, denom);
        numer /= d;
        denom /= d;
    };

    inline bool operator==(const Frac& other) const { return numer == other.numer && denom == other.denom; }

    inline bool operator!=(const Frac& other) const { return !(*this == other); }

    inline Frac operator+(const Frac& other) const
    {
        const long d = std::lcm(denom, other.denom);
        return {numer * (d / denom) + other.numer * (d / other.denom), d};
    }

    inline Frac operator-() const { return {-numer, denom}; }

    inline Frac operator-(const Frac& other) const { return *this + -other; }

    inline Frac operator*(const Frac& other) const { return {numer * other.numer, denom * other.denom}; }

    inline Frac reciprocal() const { return {denom, numer}; }

    inline double fp() const { return (double)numer / (double)denom; }
};

}  // namespace mf

// Since our fractions are always reduced, we can just hash the floating point value
template <>
struct std::hash<mf::Frac> {
    inline std::size_t operator()(const mf::Frac& frac) const { return std::hash<double>{}(frac.fp()); }
};
