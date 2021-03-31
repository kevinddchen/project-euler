#!/usr/bin/python
#ANSWER 40886

"""

Use Newton's method to generate a good rational approximation of the the
square root (error < 1e-110). Then, use long division to get the digits.

"""

from time import time

def genSqrt(p):
    """ Rational approximation from Newton's method. """
    a, b = int(p**0.5), 1
    while True:
        yield a, b
        a, b = a*a + p*b*b, 2*a*b

def error(p, a, b):
    """ Gives error between p and (a/b)^2. """
    return abs((a*a - p*b*b)/(1.*b*b))

def longDivision(a, b):
    """ Iterates through decimal digits from long division. """
    while True:
        c = a // b
        yield c
        a -= c*b
        a *= 10

def p80():
    S = 0
    ERROR_THRESHOLD = 1e-110
    for i in xrange(2, 100):
        ## if square, skip 
        if int(i**0.5)**2 == i:
            continue
        ## generate good decimal approximation of sqrt(i)
        G = genSqrt(i)
        a, b = next(G)
        while error(i, a, b) > ERROR_THRESHOLD:
            a, b = next(G)
        ## long division to get digits
        H = longDivision(a, b)
        for j in xrange(100):
            S += next(H)
    return S

if __name__ == '__main__':
    time_start = time()
    print(p80())
    print("Time: {0:.3f}".format(time()-time_start))

