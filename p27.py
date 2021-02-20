#!/usr/bin/python
#ANSWER -59231

"""

We can optimize slightly: n=0 implies b must be positive and prime. n=1 implies
a >= 1-b 

"""

from time import time
from mathfuncs import primeSieve, isPrime

def quadratic_chain(a, b):
    """Returns maximum n where n^2 + a*n + b returns prime numbers."""
    n = 0
    while isPrime(n*n + a*n + b):
        n += 1
    return n

def p27():
    ## (length of chain, product)
    maxim = (0, 0)

    ## b must be positive and prime.
    for b in primeSieve(1000):
        ## a >= 1-b
        for a in xrange(1-b, 1000):
            test = (quadratic_chain(a, b), a*b)
            if test > maxim:
                maxim = test
    return maxim[1]

if __name__ == '__main__':
    time_start = time()
    print(p27())
    print("Time: {0:.3f}".format(time()-time_start))
        
