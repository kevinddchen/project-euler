#!/usr/bin/python
#ANSWER 7652413

from time import time
from mathfuncs import isPrime
from itertools import permutations

def largestPrime(digits):
    for perm in permutations(range(digits, 0, -1)):
        p = int(''.join(str(x) for x in perm))
        if isPrime(p):
            return p
    return 0

def p41():
    for d in xrange(9, 0, -1):
        p = largestPrime(d)
        if p != 0:
            return p
        
if __name__ == '__main__':
    time_start = time()
    print(p41())
    print("Time: {0:.3f}".format(time()-time_start))

