#!/usr/bin/python
#ANSWER 5482660

"""

Notice that if P_m = P_{n+k} - P_n, then P_m = (n+k)(3n+3k-1)/2 - n(3n-1)/2 =
k(3k+6k-1)/2. Thus we generate pentagonal numbers P_m, find the divisors of
2P_m to find possible values of n and k. Then we check that P_{n+k} + P_n is a
pentagonal number, then we are done.

"""

from time import time
from mathfuncs import primeFactorize

def pent(n):
    """Returns the nth pentagon number."""
    return n*(3*n-1)/2

def checkPent(p):
    """Checks if p is a pentagon number."""
    n = int(((1+24*p)**0.5+1)/6)
    return pent(n) == p

def divisors(x): 
    divs = [1] 
    for f, i in primeFactorize(x):  
        new_divs = [] 
        for d in divs: 
            prod = 1 
            for j in xrange(i): 
                prod *= f 
                new_divs.append(d*prod) 
        divs.extend(new_divs) 
    return divs 

def p44():
    i = 0
    while True:
        i += 1
        p2 = 2*pent(i)
        d_list = sorted(divisors(p2), reverse=True)
        for d in d_list:
            k = p2/d
            n6 = d - 3*k + 1
            if n6 <= 0:
                break
            if n6 % 6 == 0:
                n = n6/6
                if checkPent( pent(n) + pent(n+k) ):
                    return p2/2

if __name__ == '__main__':
    time_start = time()
    print(p44())
    print("Time: {0:.3f}".format(time()-time_start))

