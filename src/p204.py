# ANSWER 2944730

from .mathfuncs import PrimeSieve


def recurse(primes, limit, prod=1, i=0):
    C = 1
    for j in range(i, len(primes)):
        if prod * primes[j] > limit:
            break
        C += recurse(primes, limit, prod * primes[j], j)
    return C


def p204():
    primes = [p for p in PrimeSieve(100)]
    return recurse(primes, 10**9)
