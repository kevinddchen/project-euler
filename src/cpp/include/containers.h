#pragma once

#include "common.h"

#include <functional>
#include <numeric>

namespace mf
{

/*
 * 2d vector class
 */
template <typename T>
struct Vec2 {
    T x;
    T y;

    inline bool operator==(const Vec2<T>& other) const { return x == other.x && y == other.y; }

    inline bool operator!=(const Vec2<T>& other) const { return !(*this == other); }

    inline Vec2<T> operator+(const Vec2<T>& other) const { return {x + other.x, y + other.y}; }

    inline Vec2<T> operator-() const { return {-x, -y}; }

    inline Vec2<T> operator-(const Vec2<T>& other) const { return *this + -other; }

    inline T dot(const Vec2<T>& other) const { return x * other.x + y * other.y; }

    inline T cross(const Vec2<T>& other) const { return x * other.y - y * other.x; }
};

using Vec2i = Vec2<int>;
using Vec2l = Vec2<long>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

template <typename T>
inline Vec2<T> operator*(T a, const Vec2<T>& v)
{
    return {a * v.x, a * v.y};
}

/*
 * 2x2 matrix class
 */
template <typename T>
struct Mat2 {
    T xx;
    T xy;
    T yx;
    T yy;

    inline bool operator==(const Mat2<T>& other) const
    {
        return xx == other.xx && xy == other.xy && yx == other.yx && yy == other.yy;
    }

    inline bool operator!=(const Mat2<T>& other) const { return !(*this == other); }

    inline Mat2<T> operator+(const Mat2<T>& other) const
    {
        return {xx + other.xx, xy + other.xy, yx + other.yx, yy + other.yy};
    }

    inline Mat2<T> operator-() const { return {-xx, -xy, -yx, -yy}; }

    inline Mat2<T> operator-(const Mat2<T>& other) const { return *this + -other; }

    inline Vec2<T> operator*(const Vec2<T>& v) const { return {xx * v.x + xy * v.y, yx * v.x + yy * v.y}; }

    inline Mat2<T> operator*(const Mat2<T>& other) const
    {
        return {
            xx * other.xx + xy * other.yx,
            xx * other.xy + xy * other.yy,
            yx * other.xx + yy * other.yx,
            yx * other.xy + yy * other.yy};
    }

    inline T det() const { return xx * yy - xy * yx; }

    /*
     * Inverse times determinant, i.e. {{yy, -xy}, {-yx, xx}}
     */
    inline Mat2<T> inv_times_det() const { return {yy, -xy, -yx, xx}; }
};

using Mat2i = Mat2<int>;
using Mat2l = Mat2<long>;
using Mat2f = Mat2<float>;
using Mat2d = Mat2<double>;

template <typename T>
inline Mat2<T> operator*(T a, const Mat2<T>& m)
{
    return {a * m.xx, a * m.xy, a * m.yx, a * m.yy};
}

/**
 * Fraction class. Denominator is always positive.
 */
struct Frac {
    long numer;
    long denom;

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
