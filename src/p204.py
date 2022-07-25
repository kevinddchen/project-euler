#!/usr/bin/python
#ANSWER 2944730

from time import time
from mathfuncs import PrimeSieve

def recurse(primes, limit, prod=1, i=0):
    C = 1
    for j in range(i, len(primes)):
        if prod*primes[j] > limit:
            break
        C += recurse(primes, limit, prod*primes[j], j)
    return C

def p204():
    primes = [p for p in PrimeSieve(100)]
    return recurse(primes, 10**9)

if __name__ == '__main__':
    time_start = time()
    print(p204())
    print("Time: {0:.3f}".format(time()-time_start))

