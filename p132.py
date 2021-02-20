#!/usr/bin/python
#ANSWER 843296

"""

See solution explanations.

"""

from time import time
from mathfuncs import isPrime, gcd

def generatePrimes():
    yield 2
    x = 3
    while True:
        if isPrime(x):
            yield x
        x += 2

def p132():
    C, S = 0, 0
    p = 5
    while C < 40:
        p += 2
        if not isPrime(p):
            continue
        if pow(10, pow(10, 9, p-1), p) == 1:
            C += 1
            S += p
    return S

if __name__ == '__main__':
    time_start = time()
    print(p132())
    print("Time: {0:.3f}".format(time()-time_start))

