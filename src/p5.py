# ANSWER 232792560

"""

Can be solved by hand. See PDF for explanation.

Below, we prime factorize all integers <= 20, and keep track of the prime
factors needed.

"""

from math import prod
from time import time

from mathfuncs import prime_factorize


def p5():
    # prime factorize numbers
    L = {}
    for x in range(2, 20):
        for f, k in prime_factorize(x):
            if f in L:
                L[f] = max(L[f], k)
            else:
                L[f] = k

    # multiply out factors
    return prod(f**k for f, k in L.items())


if __name__ == "__main__":
    time_start = time()
    print(p5())
    print("Time: {0:.3f}".format(time() - time_start))
