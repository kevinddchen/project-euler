#!/usr/bin/python
#ANSWER 2240

"""

See solution explanation.

"""

from time import time
from math import sqrt, asin, pi

def xn(n):
    return (n + 1 - sqrt(2*n)) / (n*n + 1)

def area(n):
    x = xn(n)
    return ((1-x)*sqrt(1-(1-x)**2) + asin(1-x) - n*x*x + 2*x - pi/2)/(2-pi/2)

def p587():
    n = 1
    while area(n) > 0.001:
        n += 1
    return n

if __name__ == '__main__':
    time_start = time()
    print(p587())
    print("Time: {0:.3f}".format(time()-time_start))

