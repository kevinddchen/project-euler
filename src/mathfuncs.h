#pragma once

#include <vector>
#include <array>

/* Return True if x is prime (and > 1). */
template <typename T> bool is_prime(T x);

/* Create prime sieve, i.e. array where nth entry is True iff n is prime (and > 1). */
bool * prime_sieve(int size);

/* Return prime factorization x = p1^a1 * p2^a2 * ... * pk^ak as a vector of (p,
a) tuples. p's are given in ascending order. If x <= 1, returns empty vector. */
template <typename T> std::vector<std::array<T, 2>> prime_factorize(T x);

/* Greatest common divisor. */
template <typename T> T gcd(T a, T b);

/* Multiplicative inverse of a mod m, as a positive integer. If a and m are not
coprime, returns 0 instead. */
template <typename T> T modular_inverse(T a, T m);

/* Return a^b mod m. Assumes `long` has twice the number of bits as `int`. */
int powmod(int a, int b, int m);
