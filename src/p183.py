#!/usr/bin/python
#ANSWER 48861552

"""

For a given N, we want to maximize (N/k)^k. We can do this by differentiating
with respect to k to get (N/k)^k[\ln(N/k) - 1], so the maximum is when k = N/e.
But this is not an integer, so we test the integers above and below for the
larger value of (N/k)^k. Once we know our k, if k/gcd(k, N) contains prime
factors other than 2 or 5, then the decimal does not terminate.

"""

from time import time
from math import e, log, gcd

def terminating_decimal(N):
    k = int(N/e)
    if -k*log(k) < log(N) - (k+1)*log(k+1):
        k += 1

    denom = k//gcd(k, N)
    ## remove multiples of 2 and 5
    while denom%2 == 0:
        denom //= 2
    while denom%5 == 0:
        denom //= 5
    return denom==1

def p183():
    return sum(N*(-1 if terminating_decimal(N) else 1) for N in range(5, 10001))

if __name__ == '__main__':
    time_start = time()
    print(p183())
    print("Time: {0:.3f}".format(time()-time_start))

