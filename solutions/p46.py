#!/usr/bin/python
#ANSWER 5777

"""

Because squares grow faster than primes, it is faster to take a number and
subtract the squares from it first, then check that the difference is prime.

"""

from time import time
from mathfuncs import is_prime

def check(x):
    """Checks if condition holds. Vacuously true for 1"""
    y = 1
    while 2*y*y < x:
        if is_prime(x - 2*y*y):
            return True
        y += 1
    return False

def p46():
    x = 1
    while True:
        x += 2
        if is_prime(x):
            continue
        if not check(x):
            return x

if __name__ == '__main__':
    time_start = time()
    print(p46())
    print("Time: {0:.3f}".format(time()-time_start))

