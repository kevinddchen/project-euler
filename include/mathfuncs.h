#pragma once

#include <vector>

#include <cassert>

/**
 * Given an integer n > 1, returns true if n is prime.
 */
bool is_prime(long n)
{
    assert(n > 1);

    if (n == 2)
    {
        return true;
    }
    if (n % 2 == 0)
    {
        return false;
    }

    for (long i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

/**
 * Creates a prime sieve, i.e. a boolean array where the nth entry, for n > 1,
 * is true when n is prime. (The n = 0 and n = 1 entries are undefined).
 */
std::vector<bool> prime_sieve(uint32_t size)
{
    std::vector<bool> sieve(size);

    // initialize values
    for (int i = 2; i < size; i++)
    {
        sieve[i] = true;
    }

    // sieve
    for (int i = 2; i * i < size; i++)
    {
        if (sieve[i])
        {
            for (int j = i * i; j < size; j += i)
            {
                sieve[j] = false;
            }
        }
    }

    return sieve;
}

struct PrimePower
{
    long base;
    long exp;

    inline bool operator==(const PrimePower &other) const
    {
        return base == other.base && exp == other.exp;
    }
};

/**
 * Prime factorize a positive integer, i.e. if n = p1^a1 * p2^a2 * ... * pk^ak
 * then return the list of {p, a} pairs. The p's are given in ascending order.
 * If n = 1, returns the empty vector.
 */
std::vector<PrimePower> prime_factorize(long n)
{
    assert(n > 0);
    std::vector<PrimePower> facts;

    for (long base = 2; base * base <= n; base++)
    {
        long exp = 0;
        while (n % base == 0)
        {
            n /= base;
            exp++;
        }
        if (exp != 0)
        {
            facts.push_back({base, exp});
        }
    }

    // remaining part may be a prime factor
    if (n > 1)
    {
        facts.push_back({n, 1});
    }

    return facts;
}

/**
 * Given two positive integers, a and b, computes the gcd, r, and Bezout
 * coefficients, s and t, which solve the equation: a*s + b*t = r. Uses the
 * Extended Euclidean algorithm.
 */
void extended_gcd(long a, long b, long &s, long &t, long &r)
{
    assert(a > 0 && b > 0);

    s = 1;
    t = 0;
    r = a;
    long new_s = 0, new_t = 1, new_r = b;
    long q, temp;

    while (new_r != 0)
    {
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
 * Computes the multiplicative inverse of a mod m, as a positive integer. Uses
 * the Extended Euclidean algorithm to compute the inverse. We must have a > 0
 * and m > 1. If a and m are not coprime, returns 0 instead.
 */
long modular_inverse(long a, long m)
{
    assert(a > 0 && m > 1);

    // use `extended_gcd` to solve a*s + m*t = 1. Then s is the inverse.
    long s, t, r;
    extended_gcd(a, m, s, t, r);

    if (r > 1)
    {
        return 0;
    }
    if (s < 0)
    {
        s += m;
    }

    return s;
}

/**
 * Computes a^b mod m, where a and b are non-negative integers and m > 1.
 * (0^0 = 1 in this implementation.)
 */
long modular_power(long a, long b, long m)
{
    assert(a >= 0 && b >= 0 && m > 1);

    long result = 1, base = a % m;
    while (b > 0)
    {
        if (b & 1) // if (b % 2) == 1
        {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        b >>= 1;
    }
    return result;
}
