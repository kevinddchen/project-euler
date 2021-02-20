#!/usr/bin/python
#ANSWER 9350130049860600

"""

From Problem 110, it was observed that in performing the calculation,

    (2a_1 + 1)*(2a_2 + 1)*...*(2a_k + 1)

We were finding the a product of k odd numbers that minimally exceeded
2000, that is to say when we multiplied to a number that exceeded the
limit, we stopped. Then, with the values of a_1...a_k, we calculated the
smallest number n using the first k primes.

Using this approach, the question now changes to a limit of 8000000.

"""

from time import time
from math import log, ceil
from mathfuncs import isPrime

def generatePrimes(n):
    x, i = 1, 0
    while i < n:
        x += 1
        if isPrime(x):
            i += 1
            yield x

def calculateN(coeff, primes):
    """ Calculate product of primes from a_1 ... a_k odd numbers """
    prod = 1;
    for i, c in enumerate(coeff):
        prod *= primes[i]**((c-1)//2)
    return prod

def minProductRecursive(path, prod, max_factor, primes):
    global LIMIT, MIN

    if (prod > LIMIT):
        
        n = calculateN(path, primes)
        if (n < MIN):
            MIN = n

    else:
        for x in xrange(3, max_factor+1, 2):
            if (2**x > MIN):
                break
            path.append(x)
            minProductRecursive(path, prod*x, x, primes)
            path.pop()

LIMIT = 8000000
MIN = 1e99
def p110():
    global MIN
    n_primes = int(ceil(log(LIMIT, 3)))
    primes = list(generatePrimes(n_primes))
    MIN = calculateN([3]*n_primes, primes)
    max_factor = int(ceil(log(MIN, 2)))
    if max_factor%2==0: max_factor -= 1
    minProductRecursive([], 1, max_factor, primes)
    return MIN

if __name__ == '__main__':
    time_start = time()
    print(p110())
    print("Time: {0:.3f}".format(time()-time_start))

