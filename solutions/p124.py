#!/usr/bin/python
#ANSWER 21417

"""

Brute force prime factorization.

"""

from time import time
from mathfuncs import primeFactorize

def p124():
    L = []
    for x in xrange(1, 100001):
        P = 1
        for f, i in primeFactorize(x):
            P *= f
        L.append( (P, x) )
    L.sort()
    return L[9999][1]

if __name__ == '__main__':
    time_start = time()
    print(p124())
    print("Time: {0:.3f}".format(time()-time_start))


