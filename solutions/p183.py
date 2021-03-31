#!/usr/bin/python
#ANSWER 48861552

"""

See solution explanations.

"""

from time import time
from math import e, log
from mathfuncs import gcd

def terminatingDecimal(N):
    k = int(N/e)
    if -k*log(k) < log(N) - (k+1)*log(k+1):
        k += 1

    denom = k/gcd(k, N)
    ## remove multiples of 2 and 5
    while denom%2 == 0:
        denom /= 2
    while denom%5 == 0:
        denom /= 5
    return denom==1

def p183():
    return sum(N*(-1 if terminatingDecimal(N) else 1) for N in xrange(5, 10001))

if __name__ == '__main__':
    time_start = time()
    print(p183())
    print("Time: {0:.3f}".format(time()-time_start))

