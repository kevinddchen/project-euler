#!/usr/bin/python
#ANSWER 5437849

"""

See solution explanations.

Runs in ~2 mins.

"""

from time import time

def func(n):
    return 2*n*n - 1

def filter_multiples(sieve, t, n):
    '''Divide out t from indices t-n, t+n, 2*t-n, 2*t+n, ...'''
    a, b = t-n, t+n
    while a < len(sieve):
        while sieve[a] % t == 0:
            sieve[a] //= t
        a, b = b, a+t

def p216():
    LIMIT = 50_000_000
    sieve = [func(n) for n in range(LIMIT+1)]
    C = 0
    
    for n, t in enumerate(sieve):
        if n <= 1 or t == 1:        ## t(n) has no new factors
            continue
        if t == func(n):            ## t(n) is prime
            C += 1
        ## filter out factors from sieve
        filter_multiples(sieve, t, n)

    return C

if __name__ == '__main__':
    time_start = time()
    print(p216())
    print("Time: {0:.3f}".format(time()-time_start))

