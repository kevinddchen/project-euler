#pragma once

#include "common.h"

#include <iterator>

namespace mf
{

/**
 * Lagged Fibonacci Generator. For the definition, see
 * https://projecteuler.net/problem=186.
 */
class LaggedFibonacci
{
public:
    using value_type = int;
    using difference_type = std::ptrdiff_t;

    LaggedFibonacci()
    {
        // k is long to avoid numerical overflow
        for (long k = 1; k <= 55; k++) {
            buffer[k - 1] = (100003 - 200003 * k + 300007 * k * k * k) % 1000000;
        }
        jmod55 = 0;
    }

    LaggedFibonacci& operator++()
    {
        buffer[jmod55] = (buffer[jmod55] + buffer[(jmod55 + 31) % 55]) % 1000000;
        jmod55 = (jmod55 + 1) % 55;
        return *this;
    }

    LaggedFibonacci operator++(int)
    {
        LaggedFibonacci tmp = *this;
        ++*this;
        return tmp;
    }

    value_type operator*() const { return buffer[jmod55]; }

private:
    value_type buffer[55];
    value_type jmod55;  // j = k-1
};

static_assert(std::input_iterator<LaggedFibonacci>);

/**
 * Blum Blum Shub generator. For the definition, see
 * https://projecteuler.net/problem=165. Yields the sequence s0, s1, s2, ... .
 */
class BlumBlumShub
{
public:
    using value_type = long;
    using difference_type = std::ptrdiff_t;

    static const value_type mod = 50'515'093;
    static const value_type s0 = 290'797;

    BlumBlumShub() : s(s0) {}

    BlumBlumShub& operator++()
    {
        s = (s * s) % mod;
        return *this;
    }

    BlumBlumShub operator++(int)
    {
        BlumBlumShub tmp = *this;
        ++*this;
        return tmp;
    }

    value_type operator*() const { return s; }

private:
    value_type s;
};

static_assert(std::input_iterator<BlumBlumShub>);

}  // namespace mf
