#!/usr/bin/python
#ANSWER 37076114526

"""

See solution explanations.

"""

from time import time

def neq_prod(i, k, f):
    """ Compute the product of f(j) for all 1 <= j <= k and j != i """
    p = 1
    for j in range(1, k+1):
        if j != i:
            p *= f(j)
    return p

def P(i, k):
    """ Returns the Lagrange polynomial P_i(x) as defined in the explanation """
    D = neq_prod(i, k, lambda j: i-j)
    return lambda x: neq_prod(i, k, lambda j: x-j) / D

def L(f, k):
    """ Returns the Lagrange interpolation of function f for values 1...k """
    P_set = [P(i, k) for i in range(1, k+1)]
    return lambda x: sum(f(i)*P_set[i-1](x) for i in range(1, k+1))

def p101():
    ## Target function
    f = lambda x: 1-x+x**2-x**3+x**4-x**5+x**6-x**7+x**8-x**9+x**10

    S = 0
    for k in range(1, 11):
        inter = L(f, k)
        n = k+1
        while inter(n) == f(n):
            n += 1
        S += int(inter(n))
    return S

if __name__ == '__main__':
    time_start = time()
    print(p101())
    print("Time: {0:.3f}".format(time()-time_start))

