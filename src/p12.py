# ANSWER 76576500

"""

There is a fast way to count the divisors of an integer. Given an integer and
its prime factorization, n = p1^a1 * p2^a2 * ... * pk^ak, the number of ways we
can multiply the primes together gives the number of divisors. Thus the number
of divisors of n is (a_1 + 1)(a_2 + 1)...(a_k+1).

"""

from math import prod

from .mathfuncs import prime_factorize


def num_divisors(n):
    return prod(i + 1 for _, i in prime_factorize(n))


def p12():
    # generate triangle numbers
    x, i = 3, 2
    while True:
        if num_divisors(x) > 500:
            return x
        i += 1
        x += i
