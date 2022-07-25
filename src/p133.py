# ANSWER 453647705

"""

Similar to Problem 132, R(10^n) is divisible by p iff 10^gcd(10^n, p-1) = 1 mod p.
For for each p, we iterate through n until the gcd does not change.

"""

from math import gcd
from time import time

from .mathfuncs import PrimeSieve, prime_factorize


def totient(x):
    for f, _ in prime_factorize(x):
        x = x * (f - 1) // f
    return x


def possible(p):
    n = 10
    g = (gcd(n, p - 1), -1)
    while g[0] != g[1]:
        if pow(10, g[0], p) == 1:
            return True
        n *= 10
        g = (gcd(n, p - 1), g[0])
    return False


def p133():
    return sum(p for p in PrimeSieve(100000) if p < 7 or not possible(p))


if __name__ == "__main__":
    time_start = time()
    print(p133())
    print("Time: {0:.3f}".format(time() - time_start))
