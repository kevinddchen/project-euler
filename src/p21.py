# ANSWER 31626

from math import prod

from .mathfuncs import prime_factorize

"""

There is a fast way to sum the divisors of an integer. Given an integer and its
prime factorization, n = p1^a1 * p2^a2 * ... * pk^ak, note that

    (1+p1+p1^2+...+p1^a1) (1+p2+p2^2+...+p2^a2) ... (1+pk+pk^2+...+pk^ak)

expanded is the sum of all numbers that divide n. This can also be written as

    prod_{i=1}^k (pi^(ai+1)-1) / (pi-1)

"""


def sum_proper_divisors(x):
    # return sum of proper divisors
    # also used in Problem 23 and 95
    if x == 1:
        return 0
    return prod((pf.base ** (pf.exp + 1) - 1) // (pf.base - 1) for pf in prime_factorize(x)) - x


def p21():
    S = 0
    for start in range(2, 10000):
        end = sum_proper_divisors(start)
        if sum_proper_divisors(end) == start and start != end:
            S += start
    return S
