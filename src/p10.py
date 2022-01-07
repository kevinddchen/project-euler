#!/usr/bin/python
#ANSWER 142913828922

"""

A very fast way of generating prime numbers up to some N is to use a Sieve of
Eratosthenes. Create a list of the first N numbers, and cross-out 0 and 1. The
first uncrossed integer is 2, which is the first prime. Next, cross-out all
multiples of 2. The next uncrossed integer is 3, which is the second prime.
Next, cross-out all multiples of 3. Continuing in this way for all integers up
to sqrt(N), we generate all primes less than or equal to N.

"""

from time import time
from mathfuncs import prime_sieve

def p10():
    return sum(n for n in prime_sieve(2000000))

if __name__ == '__main__':
    time_start = time()
    print(p10())
    print("Time: {0:.3f}".format(time()-time_start))

