# ANSWER 232792560

"""

Can be solved by hand. See PDF for explanation.

Below, we prime factorize all integers <= 20, and keep track of the prime
factors needed.

"""

from math import prod

from .mathfuncs import prime_factorize


def p5():
    # prime factorize numbers
    L = {}
    for x in range(2, 20):
        for pf in prime_factorize(x):
            if pf.base in L:
                L[pf.base] = max(L[pf.base], pf.exp)
            else:
                L[pf.base] = pf.exp

    # multiply out factors
    return prod(f**k for f, k in L.items())
