#!/usr/bin/python
#ANSWER 661

"""

This Diophantine equation is called Pell's equation. A minimal solution for x
exists for some fractional convergent sqrt(D). So if we generate its continued
fraction coefficients using the method from problem 64, then iterate through
the fractional approximations using the method from problem 65, and we will
eventually find a solution to Pell's equation for that D.

"""

from time import time
import sys
sys.dont_write_bytecode = True
import p64

def minimalPell(D):
    G = p64.generateSqrtContFrac(D) 
    a_0 = next(G)
    a_1 = next(G)
    p = (a_0*a_1+1, a_0)
    q = (a_1, 1)

    if a_1 == 2*a_0:    ## period 1
        return p[0], q[0]

    i = 2
    while True:
        a = next(G)
        if a == 2*a_0 and i%2 == 0:
            return p[0], q[0]
        p = (a*p[0]+p[1], p[0])
        q = (a*q[0]+q[1], q[0])
        i += 1

def p66():
    M = (9, 5)
    for D in xrange(2, 1001):
        if D == int(D**0.5)**2:     ## D is perfect square
            continue
        x, y = minimalPell(D)
        if x > M[0]:
            M = (x, D)
    return M[1]

if __name__ == '__main__':
    time_start = time()
    print(p66())
    print("Time: {0:.3f}".format(time()-time_start))

