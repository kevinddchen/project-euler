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
    int buffer[55];
    int jmod55;  // j = k-1

public:
    using value_type = int;
    using difference_type = int;
    using iterator_category = std::input_iterator_tag;

    LaggedFibonacci()
    {
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

    int operator*() const { return buffer[jmod55]; }
};

/**
 * Blum Blum Shub generator. For the definition, see
 * https://projecteuler.net/problem=165. Yields the sequence s0, s1, s2, ... .
 */
class BlumBlumShub
{
    long s;

public:
    static const long mod = 50'515'093;

    BlumBlumShub() : s(290'797) {}

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

    int operator*() const { return s; }
};

}  // namespace mf
