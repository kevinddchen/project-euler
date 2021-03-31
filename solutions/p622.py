#!/usr/bin/python
#ANSWER 3010983666182123972

"""

s(n) is the smallest integer such that 2^{s(n)} = 1 mod (n-1). So we find all
values of n such that 2^60 = 1 mod (n-1), and 2^d =/= 1 mod (n-1) for all
divisors d of 60.

"""

from time import time

def factorize(x):
    """ Prime factorize. Returns list of tuples (prime, exponent). """
    L = []
    p = 2
    while p*p <= x:
        i = 0
        while x%p == 0:
            x = x/p
            i = i+1
        if i > 0:
            L.append( (p, i) )
        p = p+1
    if x > 1:
        L.append( (x, 1) )
    return L



def gen_divisors(f, prod=1, layer=0):
    """ Generate divisors, given prime factorization. """ 
    if layer == len(f):
        yield prod
    else:
        p, n = f[layer]
        for i in xrange(n+1):
            for d in gen_divisors(f, prod, layer+1):
                yield d
            prod = prod*p

def check(d, bad):
    for b in bad:
        if b%d == 0:
            return False
    return True


def p622():

    divisors = [2, 3, 4, 5, 6, 10, 12, 15, 20, 30]
    bad = [pow(2, d) - 1 for d in divisors]
    S = 0

    N = pow(2, 60) - 1
    f = factorize(N)
    for d in gen_divisors(f):
        if check(d, bad):
            S = S + (d+1)
    return S

if __name__ == '__main__':
    time_start = time()
    print(p622())
    print("Time: {0:.3f}".format(time()-time_start))



