#pragma once

#include <vector>

/**
 * Given an integer n > 1, returns true if n is prime. 
 */
bool is_prime(long n)
{
    if (n < 2)
    {
        return false;
    }
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
 * Create a prime sieve, i.e. boolean array where nth entry is true when n is
 * prime (for n > 1).
 */
std::vector<bool> prime_sieve(uint32_t size)
{
    std::vector<bool> sieve(size);

    // initialize values
    for (int i = 0; i < size && i < 2; i++)
    {
        sieve[i] = false;
    }
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
            facts.push_back({ base, exp });
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
 * Given two integers a and b, compute the Bezout coefficients and gcd which
 * solve the equation: a*s + b*t = r. 
 */
void extended_gcd(long a, long b, long &s, long &t, long &r)
{
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
 * Compute the multiplicative inverse of a mod m, as a positive integer. If a
 * and m are not coprime, returns 0 instead. 
 */
long modular_inverse(long a, long m)
{
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
 * Compute a^b mod m.
 */
long modular_power(long a, long b, long m)
{
    long result = 1, base = a % m;
    while (b > 0)
    {
        if (b & 1)  // if (b % 2) == 1
        {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        b >>= 1;
    }
    return result;
}
