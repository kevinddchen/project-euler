#!/usr/bin/python
#ANSWER 7526965179680

"""

See solution explanations.

"""

from time import time
from mathfuncs import primeSieve

def choose_greatestPower(m, n, p):
    """ Gives greatest integer c for prime p such that p^c divides choose(m, n)."""

    a = max(m-n, n)
    b = min(m-n, n)
    carries = 0
    i = 0
    prev = 0
    while p**i <= a:
        a_digit = (a // p**i) % p
        b_digit = (b // p**i) % p
        if prev + a_digit + b_digit >= p:
            carries += 1
            prev = 1
        else:
            prev = 0
        i += 1
    return carries

def p231():
    m, n = 2*10**7, 5*10**6
    s = 0
    for p in primeSieve(m):
        s += choose_greatestPower(m, n, p)*p
    return s

if __name__ == '__main__':
    time_start = time()
    print(p231())
    print("Time: {0:.3f}".format(time()-time_start))

