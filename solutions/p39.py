#!/usr/bin/python
#ANSWER 840

from time import time
from mathfuncs import gcd

def p39():
    ## Euler's formula for generating Pythagorean triples
    ## a+b+c = 2m(m+n) <= 1000, so stop m at sqrt(5000)
    ans = [0]*1001
    for m in xrange(2, int(500**0.5)):
        ## m, n opposite parity
        n_1 = 1 if m%2==0 else 2
        for n in xrange(n_1, m, 2):
            if gcd(m, n) == 1:
                p = 2*m*(m+n)
                while p <= 1000:
                    ans[p] += 1
                    p += 2*m*(m+n)
    return max( (n, i) for i, n in enumerate(ans) )[1]

if __name__ == '__main__':
    time_start = time()
    print(p39())
    print("Time: {0:.3f}".format(time()-time_start))

