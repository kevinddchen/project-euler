# ANSWER 17427258

"""

Solved using a prime sieve.

"""

from bisect import bisect

from .mathfuncs import PrimeSieve


def p187():
    LIMIT = 10**8
    p_list = []
    C = 0
    for p in PrimeSieve(LIMIT // 2):
        if p * p < LIMIT:
            p_list.append(p)
        j = bisect(p_list, LIMIT // p)  # number of primes p' <= p such that p' * p <= LIMIT
        C += j
    return C
