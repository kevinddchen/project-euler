# ANSWER 121313

"""

Generate all primes for a certain number of digits, then generate all patterns.
Find the first pattern that satisifes the conditions in the problem.

"""

from itertools import product

from .mathfuncs import PrimeSieve


def replace(tup, x, y):
    L = []
    for z in tup:
        if z == x:
            L.append(y)
        else:
            L.append(z)
    return L


def test_pattern(pattern, sieve, allowance):
    err = 0
    start = 1 if pattern[0] == "*" else 0
    for d in range(start, 10):
        q = int("".join(replace(pattern, "*", str(d))))
        if not sieve[q]:
            err += 1
        if err > allowance - start:
            return False
    return True


def p51():
    digits = 2
    while True:
        # generate primes up to 10^digits
        ps = PrimeSieve(10**digits)
        for _ in ps:
            pass

        # generate patterns
        for pattern in product("0123456789*", repeat=digits):
            if pattern[0] == "0" or "*" not in pattern:
                continue
            if test_pattern(pattern, ps.sieve, 10 - 8):
                # pattern found, print first prime
                start = 1 if pattern[0] == "*" else 0
                for d in range(start, 10):
                    q = int("".join(replace(pattern, "*", str(d))))
                    if ps.sieve[q]:
                        return q
        digits += 1
