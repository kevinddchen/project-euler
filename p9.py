#!/usr/bin/python
#ANSWER 31875000

"""

See solution explanations.

"""

from time import time
from mathfuncs import gcd

def p9():
    ## Euler's formula for generating Pythagorean triples.
    ## a+b+c = 2m(m+n) = 1000, so stop m at sqrt(500)
    for m in xrange(2, int(500**0.5)):
        ## m, n opposite parity
        n_1 = 1 if m%2==0 else 2
        for n in xrange(n_1, m, 2):
            if gcd(m, n) == 1:
                a = m*m - n*n
                b = 2*m*n
                c = m*m+n*n
                if 1000%(a+b+c) == 0:
                    return a*b*c*(1000//(a+b+c))**3

if __name__ == '__main__':
    time_start = time()
    print(p9())
    print("Time: {0:.3f}".format(time()-time_start))

