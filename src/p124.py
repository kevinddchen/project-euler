# ANSWER 21417

"""

Brute force prime factorization.

"""

from mathfuncs import prime_factorize


def p124():
    L = [(1, 1)]
    for x in range(2, 100001):
        P = 1
        for pf in prime_factorize(x):
            P *= pf.base
        L.append((P, x))
    L.sort()
    return L[9999][1]
