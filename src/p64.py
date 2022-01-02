#!/usr/bin/python
#ANSWER 1322

"""

See solution explanations.

"""

from time import time
from math import isqrt

def continued_fraction_of_sqrt(n):
    ## also used in Problem 66
    m, d = 0, 1
    while True:
        a = int((n**.5 + m)/d)
        yield a
        m = d*a-m
        d = (n-m*m) // d

def p64():
    C = 0
    for n in range(10001):
        a_0 = isqrt(n)
        if n == a_0*a_0:        ## n is a perfect square
            continue

        for i, a in enumerate(continued_fraction_of_sqrt(n)):
            if a == 2*a_0:
                break

        if i%2 == 1:
            C += 1
    return C

if __name__ == '__main__':
    time_start = time()
    print(p64())
    print("Time: {0:.3f}".format(time()-time_start))
        
