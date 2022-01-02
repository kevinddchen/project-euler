#!/usr/bin/python
#ANSWER 76576500

"""

See solution explanations.

"""

from time import time
from math import prod
from mathfuncs import prime_factorize

def num_divisors(n):
    return prod(i+1 for _, i in prime_factorize(n))

def p12():
    ## generate triangle numbers
    x, i = 3, 2
    while True:
        if num_divisors(x) > 500:
            return x
        i += 1
        x += i

if __name__ == '__main__':
    time_start = time()
    print(p12())
    print("Time: {0:.3f}".format(time()-time_start))

