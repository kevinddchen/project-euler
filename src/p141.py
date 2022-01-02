#!/usr/bin/python
#ANSWER 878454337159

"""

n = dq + r where r < d. WLOG we can assume that d < n < q. Then as r, d, q are
part of a geometric sequence with ratio a/b, d = (a/b)r and q = (a^2/b^2)r. Thus
n = (a^3/b^3)r^2 + r. But n is an integer and gcd(a, b) = 1, so r is a multiple
of b^2, and we can replace r -> b^2 * r. Thus n = br(a^3 * r + b). Then we
iterate through a then b then r, testing if n is a perfect square.

"""

from time import time
from math import gcd, isqrt

def p141():
    LIMIT = 10**12
    S = 0

    a = 2
    while a**3 < LIMIT:
        for b in range(1, a):
            if b*(a**3 + b) > LIMIT:
                break
            if gcd(a, b) == 1:
                r = 1
                while True:
                    n = b*r*(r*a**3 + b)
                    if n > LIMIT:
                        break
                    if n == isqrt(n)**2:
                        S += n
                    r += 1
        a += 1
    return S

if __name__ == '__main__':
    time_start = time()
    print(p141())
    print("Time: {0:.3f}".format(time()-time_start))

