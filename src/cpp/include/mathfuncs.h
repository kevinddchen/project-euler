#pragma once

#include "common.h"

#include <vector>

namespace mf
{

/**
 * Returns true if n is prime.
 * @param n integer.
 */
bool is_prime(long n)
{
    if (n <= 1) {
        return false;
    } else if (n == 2) {
        return true;
    } else if (n % 2 == 0) {
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
 * Create a prime sieve, i.e. a boolean array where the nth entry is `true`
 * when n is prime. Note: entries n=0 and n=1 are `false` in this sieve.
 * @param size non-negative integer; size of sieve.
 */
std::vector<bool> prime_sieve(int size)
{
    assert(size >= 0);

    // initialize sieve
    std::vector<bool> sieve(size);
    for (int i = 2; i < size; i++) {
        sieve[i] = true;
    }

    // sieve
    for (int i = 2; i * i < size; i++) {
        if (!sieve[i]) {  // skip if not prime
            continue;
        }
        for (int j = i * i; j < size; j += i) {
            sieve[j] = false;
        }
    }
    return sieve;
}

/**
 * Create a sieve where the nth entry is the smallest prime factor of n. Note:
 * entries n=0 and n=1 are equal to `0`.
 * @param size non-negative integer; size of sieve.
 */
std::vector<int> prime_factor_sieve(int size)
{
    assert(size >= 0);

    // initialize sieve
    std::vector<int> sieve(size);
    for (int i = 2; i < size; i++) {
        sieve[i] = i;
    }

    // sieve
    for (int i = 2; i * i < size; i++) {
        if (sieve[i] != i) {  // skip if not prime
            continue;
        }
        for (int j = i * i; j < size; j += i) {
            if (i < sieve[j]) {
                sieve[j] = i;
            }
        }
    }
    return sieve;
}

/**
 * Simple struct containing a prime and its exponent.
 */
struct PrimePower {
    long base;
    int exp;

    inline bool operator==(const PrimePower& other) const { return base == other.base && exp == other.exp; }
};

/**
 * Prime factorize an integer, i.e. if n = p1^a1 * p2^a2 * ... * pk^ak then
 * returns the list of {p, a} pairs. The factorization given in ascending order
 * of p.
 * @param n integer, greater than 1.
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
 * Prime factorize a positive integer with the speed-up from a prime factor
 * sieve. The factorization is given in ascending order of p.
 * @param n integer, greater than 1.
 */
std::vector<PrimePower> prime_factorize(long n, const std::vector<int>& sieve)
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
 * Merge two lists of prime factors, each given in ascending order of p.
 * @param facts1 first list of prime factors.
 * @param facts2 second list of prime factors.
 */
std::vector<mf::PrimePower> merge_prime_factors(
    const std::vector<mf::PrimePower>& facts1, const std::vector<mf::PrimePower>& facts2)
{
    auto fact1 = facts1.begin();
    auto fact2 = facts2.begin();
    std::vector<mf::PrimePower> out_facts;

    while (fact1 != facts1.end() && fact2 != facts2.end()) {
        if (fact1->base < fact2->base) {
            out_facts.push_back({fact1->base, fact1->exp});
            fact1++;
        } else if (fact1->base == fact2->base) {
            out_facts.push_back({fact1->base, fact1->exp + fact2->exp});
            fact1++;
            fact2++;
        } else {
            out_facts.push_back({fact2->base, fact2->exp});
            fact2++;
        }
    }

    // push remaining elements
    out_facts.insert(out_facts.end(), fact1, facts1.end());
    out_facts.insert(out_facts.end(), fact2, facts2.end());

    return out_facts;
}

/**
 * Given two positive integers, a and b, computes the gcd, r, and Bezout
 * coefficients, s and t, which solve the equation: a*s + b*t = r. Uses the
 * Extended Euclidean algorithm.
 * @param a positive integer.
 * @param b positive integer.
 * @param s output parameter.
 * @param t output parameter.
 * @param r output parameter.
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
 * Computes the multiplicative inverse of a mod m. If a and m are not coprime,
 * returns 0 instead. Uses the Extended Euclidean algorithm to compute the
 * inverse.
 * @param a positive integer.
 * @param m integer, greater than 1.
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
 * Computes the modular product (a * b) mod m.
 * @param a non-negative integer, less than m.
 * @param b non-negative integer, less than m.
 * @param m integer, greater than 1.
 */
long modular_product(long a, long b, long m)
{
    assert(0 <= a && a < m);
    assert(0 <= b && b < m);
    assert(1 < m);

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

/**
 * Computes the modular power a^b mod m. Note: 0^0 = 1 in this implementation.
 * @param a non-negative integer, less than m.
 * @param b non-negative integer.
 * @param m integer, greater than 1.
 */
long modular_power(long a, long b, long m)
{
    assert(0 <= a && a < m);
    assert(0 <= b);
    assert(1 < m);

    long result = 1;
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
 * Computes a^b. No checks for overflow are performed. Note: 0^0 = 1 in this
 * implementation.
 * @param a integer.
 * @param b non-negative integer.
 */
long pow(long a, int b)
{
    assert(b >= 0);

    long result = 1;
    while (b > 0) {
        if (b & 1) {  // if (b % 2) == 1
            result = result * a;
        }
        a = a * a;
        b >>= 1;
    }
    return result;
}

/**
 * Round a float to a certain number of decimal places.
 * @param arg float to round.
 * @param n_decimals number of decimal places to round to.
 */
double round(double arg, uint32_t n_decimals)
{
    const double x = pow(10.0, static_cast<double>(n_decimals));
    return std::round(arg * x) / x;
}

}  // namespace mf
