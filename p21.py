#!/usr/bin/python
#ANSWER 31626

from time import time
from mathfuncs import primeFactorize

def sumDivisors(x):
    prod = 1
    for p, i in primeFactorize(x):
        prod *= (p**(i+1)-1)/(p-1)
    return prod


def p21():
    S = 0
    for start in xrange(2,10000):
        end = sumDivisors(start)-start
        if sumDivisors(end)-end == start and start!=end: 
            S += start
    return S

if __name__ == '__main__':
    time_start = time()
    print(p21())
    print("Time: {0:.3f}".format(time()-time_start))

