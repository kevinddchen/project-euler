#!/usr/bin/python
#ANSWER 76576500

"""

See solution explanations.

"""

from time import time
from mathfuncs import primeFactorize

def triangle_gen():
    """Generates triangle numbers. """
    x, i = 1, 1
    while True:
        yield x
        i += 1
        x += i

def p12():
    for tri in triangle_gen():
        n_divisors = 1
        for f, i in primeFactorize(tri):
            n_divisors *= i+1
        if n_divisors > 500:
            return tri

if __name__ == '__main__':
    time_start = time()
    print(p12())
    print("Time: {0:.3f}".format(time()-time_start))

