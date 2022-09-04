# ANSWER 1097343

"""

If you generate all the primes and create the set of all combinations, it is
quite straightforward to count them all.

"""

from math import isqrt

from .mathfuncs import is_prime


def prime_gen(maxim):
    yield 2
    x = 3
    while x <= maxim:
        if is_prime(x):
            yield x
        x += 2


def power_triple(a, b, c):
    return a**2 + b**3 + c**4


def p87():
    TARGET = 50000000
    max_c = isqrt(TARGET - 2**3 - 2**4)
    primes = list(prime_gen(max_c))
    sum_set = set()

    for c in primes:
        for b in primes:
            if power_triple(2, b, c) > TARGET:
                break
            for a in primes:
                s = power_triple(a, b, c)
                if s < TARGET:
                    sum_set.add(s)
                else:
                    break

    return len(sum_set)
