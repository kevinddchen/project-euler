#!/usr/bin/python
#ANSWER 538319652

"""

We use the fact that 
    
    B(n) = B(n-1) * n^n / n!

So we recursively keep track of the prime factorization of B(n), which can
compute the sum of divisors efficiently. We do need to worry about overflow
when multiplying two large numbers (a * b) % N, which is handled by the 'mult'
routine.

The program runs in ~8 mins, but a speedup can be achieved using C++.

"""

from time import time
import numpy as np


def gen_sieve(N):
    """ Produce sieve giving 1 if prime, else a prime factor. """
    sieve = np.ones(N+1, dtype=int)
    sieve[0] = 0
    sieve[1] = 0
    for i in xrange(2, N+1):
        if i <= np.sqrt(N) and sieve[i] == 1:
            n = i*i
            while n <= N:
                sieve[n] = i
                n = n+i
    return sieve

def gen_sieve_map(sieve):
    """ Given sieve, L[i] is the ith prime, and M is the inverse map. """
    M = np.zeros(len(sieve), dtype=int)
    L = np.empty(len(sieve), dtype=int)
    i = 0
    for p, isPrime in enumerate(sieve):
        if isPrime == 1:
            M[p] = i
            L[i] = p
            i = i+1

    return M, L[:i], i

def gen_factors(x, sieve):
    """ Generate prime factors of x. """
    while sieve[x] != 1:
        yield sieve[x]
        x = x/sieve[x]
    yield x

def mult(a, b, P):
    """ Return (a * b) % P. """
    res = 0
    while b > 0:
        if (b % 2) == 1:
            res = (res + a) % P
        a = (a * 2) % P
        b = b // 2
    return res


def p650():

    N = 20000
    P = 1000000007
    S = 1

    sieve = gen_sieve(N)
    p_map, p_invmap, p_num = gen_sieve_map(sieve)

    # Calculate (p-1) % P for all primes 
    inverses = np.empty(p_num, dtype=int)
    for p_i in xrange(p_num):
        p = int(p_invmap[p_i])
        inverses[p_i] = pow(p-1, P-2, P)

    # curr_f keeps track of prime factorization of B(n)
    # sub_f keeps track of prime factorization of n!
    curr_f = np.zeros(p_num, dtype=int)
    sub_f = np.zeros(p_num, dtype=int)

    for n in xrange(2, N+1):

        curr_f = curr_f - sub_f

        for p in gen_factors(n, sieve):
            p_i = p_map[p]
            curr_f[p_i] = curr_f[p_i] + (n-1)
            sub_f[p_i] = sub_f[p_i] + 1

        d = 1
        for p_i, e in enumerate(curr_f):
            p = int(p_invmap[p_i])
            if e != 0:
                a = pow(p, int(e+1), P)-1
                d = mult(d, mult(a, int(inverses[p_i]), P), P)

        S = (S + d) % P

    return S



if __name__ == '__main__':
    time_start = time()
    print(p650())
    print("Time: {0:.3f}".format(time()-time_start))



