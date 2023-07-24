#pragma once

#include "common.h"

#include <array>
#include <memory>
#include <vector>

#include <cmath>

namespace
{

/**
 * Compute modular product.
 * @param a non-negative integer, less than m.
 * @param b non-negative integer, less than m.
 * @param m integer, greater than 1
 */
long modular_product(long a, long b, long m)
{
    // if mod is small enough, can directly multiply
    if (m <= INT_MAX) {
        return (a * b) % m;
    }

    // otherwise, we have to use an algorithm similar to `modular_power`
    long result = 0;
    while (b > 0) {
        if (b & 1) {  // if (b % 2) == 1
            result = (result + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }
    return result;
}

}  // namespace

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace mf
{

/**
 * Given an integer n > 1, returns true if n is prime.
 */
bool is_prime(long n)
{
    assert(n > 1);

    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

/**
 * Creates a prime sieve, i.e. a boolean array where the nth entry, for n > 1,
 * is true when n is prime. 0 and 1 are not considered prime in the sieve.
 */
std::unique_ptr<bool[]> prime_sieve(int size)
{
    assert(size >= 0);

    // initialize sieve
    auto sieve = std::make_unique<bool[]>(size);
    for (int i = 2; i < size; i++) {
        sieve[i] = true;
    }

    // sieve
    for (int i = 2; i * i < size; i++) {
        if (sieve[i]) {
            for (int j = i * i; j < size; j += i) {
                sieve[j] = false;
            }
        }
    }
    return sieve;
}

/**
 * Creates a sieve where the nth entry, for n > 1, is the smallest prime factor
 * of n. Entries 0 and 1 are '0'.
 */
std::unique_ptr<int[]> prime_factor_sieve(int size)
{
    assert(size >= 0);

    // initialize sieve
    auto sieve = std::make_unique<int[]>(size);
    for (int i = 2; i < size; i++) {
        sieve[i] = i;
    }

    // sieve
    for (int i = 2; i * i < size; i++) {
        if (sieve[i] == i) {
            for (int j = i * i; j < size; j += i) {
                sieve[j] = std::min(i, sieve[j]);
            }
        }
    }
    return sieve;
}


struct PrimePower {
    long base;
    int exp;

    inline bool operator==(const PrimePower& other) const { return base == other.base && exp == other.exp; }
};

/**
 * Prime factorize a positive integer, i.e. if n = p1^a1 * p2^a2 * ... * pk^ak
 * then return the list of {p, a} pairs. The p's are given in ascending order.
 */
std::vector<PrimePower> prime_factorize(long n)
{
    assert(n > 1);
    std::vector<PrimePower> facts;

    for (long base = 2; base * base <= n; base++) {
        int exp = 0;
        while (n % base == 0) {
            n /= base;
            exp++;
        }
        if (exp != 0) {
            facts.push_back({base, exp});
        }
    }

    // remaining part may be a prime factor
    if (n > 1) {
        facts.push_back({n, 1});
    }

    return facts;
}


/**
 * Prime factorize a positive integer, with the speed-up from a prime factor
 * sieve. The p's are given in ascending order.
 */
std::vector<PrimePower> prime_factorize(long n, const int* sieve)
{
    assert(n > 1);
    std::vector<PrimePower> facts;

    int base = sieve[n];
    int exp = 1;
    n /= base;

    while (n != 1) {
        if (sieve[n] == base) {
            exp++;
        } else {
            facts.push_back({base, exp});
            base = sieve[n];
            exp = 1;
        }
        n /= base;
    }

    facts.push_back({base, exp});

    return facts;
}

/**
 * Given two positive integers, a and b, computes the gcd, r, and Bezout
 * coefficients, s and t, which solve the equation: a*s + b*t = r. Uses the
 * Extended Euclidean algorithm.
 */
void extended_gcd(long a, long b, long& s, long& t, long& r)
{
    assert(a > 0);
    assert(b > 0);

    s = 1;
    t = 0;
    r = a;
    long new_s = 0, new_t = 1, new_r = b;
    long q, temp;

    while (new_r != 0) {
        q = r / new_r;

        temp = r;
        r = new_r;
        new_r = temp - q * new_r;

        temp = s;
        s = new_s;
        new_s = temp - q * new_s;

        temp = t;
        t = new_t;
        new_t = temp - q * new_t;
    }
}

/**
 * Computes the multiplicative inverse of a mod m, and returns a positive
 * integer. Uses the Extended Euclidean algorithm to compute the inverse. We
 * must have a > 0 and m > 1. If a and m are not coprime, returns 0 instead.
 */
long modular_inverse(long a, long m)
{
    assert(a > 0);
    assert(m > 1);

    // use `extended_gcd` to solve a*s + m*t = 1. Then s is the inverse.
    long s, t, r;
    extended_gcd(a, m, s, t, r);

    if (r > 1) {
        return 0;
    }
    if (s < 0) {
        s += m;
    }

    return s;
}

/**
 * Computes a^b mod m, where b is a non-negative integer and m > 1.
 * (0^0 = 1 in this implementation.)
 */
long modular_power(long a, long b, long m)
{
    assert(b >= 0);
    assert(m > 1);

    long result = 1;
    a = ((a % m) + m) % m;
    while (b > 0) {
        if (b & 1) {  // if (b % 2) == 1
            result = modular_product(result, a, m);
        }
        a = modular_product(a, a, m);
        b >>= 1;
    }
    return result;
}

/**
 * Computes a^b, where b is a non-negative integer. (0^0 = 1 in this
 * implementation.)
 */
long pow(long a, int b)
{
    assert(b >= 0);

    long result = 1;
    while (b > 0) {
        if (b & 1)  // if (b % 2) == 1
        {
            result = result * a;
        }
        a = a * a;
        b >>= 1;
    }
    return result;
}

/**
 * Round a float to a certain number of decimal places
 */
double round(double arg, uint32_t n_decimals)
{
    const double x = pow(10.0, static_cast<double>(n_decimals));
    return std::round(arg * x) / x;
}

/**
 * Lagged Fibonacci Generator. Used in various problems.
 */
class LaggedFibGen
{
    int buffer[55];
    int jmod55;  // j = k-1

public:
    LaggedFibGen()
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
