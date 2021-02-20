#!/usr/bin/python
#ANSWER 149253

"""

Using A(n) calculation from Problem 129

"""

from time import time
from mathfuncs import isPrime

def A(n):
    k = 1
    R_k = 1
    while R_k != 0:
        R_k = (R_k*10 + 1) % n
        k += 1
    return k


def p130():
    S = 0
    i = 0

    n = 2 
    while i < 25: 
        n += 1
        if n%2==0 or n%5==0 or isPrime(n):
            continue 
        if (n-1) % A(n) == 0:
            S += n
            i += 1
    return S

if __name__ == '__main__':
    time_start = time()
    print(p130())
    print("Time: {0:.3f}".format(time()-time_start))

