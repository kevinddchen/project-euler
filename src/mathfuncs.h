#pragma once

#include <vector>
#include <array>

/* Returns true if x is prime (and > 1). */
template <typename T> bool is_prime(T x);

/* Creates prime sieve, i.e. array where nth entry is true when n is prime 
(and > 1). */
bool * prime_sieve(int size);

/* Prime factorization x = p1^a1 * p2^a2 * ... * pk^ak as a vector of {p, a}
pairs. p's are given in ascending order. If x <= 1, returns empty vector. */
template <typename T> std::vector<std::array<T, 2>> prime_factorize(T x);

/* Bezout coefficients and gcd, which solve a*s + b*t = r. */
template <typename T> void extended_gcd(T a, T b, T &s, T &t, T &r);

/* Multiplicative inverse of a mod m, as a positive integer. If a and m are not
coprime, returns 0 instead. */
template <typename T> T modular_inverse(T a, T m);

/* Returns a^b mod m. Assumes `long` has twice the number of bits as `int`. */
template <typename T> int modular_power(int a, T b, int m);
