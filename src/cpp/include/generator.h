#pragma once

#include "common.h"

/**
 * Abstract class for an infinite sequence generator.
 */
template <typename T>
class _mf_Generator
{
public:
    virtual T next() = 0;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace mf
{

/**
 * Lagged Fibonacci Generator. For the definition, see https://projecteuler.net/problem=149.
 */
class LaggedFibonacci : _mf_Generator<int>
{
    int buffer[55];
    int jmod55;  // j = k-1

public:
    LaggedFibonacci()
    {
        for (int k = 1; k <= 55; k++) {
            buffer[k - 1] = (100003L - 200003L * k + 300007L * k * k * k) % 1000000;
        }
        jmod55 = 0;
    }

    int next()
    {
        const int return_val = buffer[jmod55];
        buffer[jmod55] = (buffer[jmod55] + buffer[(jmod55 + 31) % 55]) % 1000000;
        jmod55 = (jmod55 + 1) % 55;
        return return_val;
    }
};

}  // namespace mf
