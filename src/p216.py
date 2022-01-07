#!/usr/bin/python
#ANSWER 5437849

"""

We can use a sieve method to generate all primes. This relies on two claims: 

 1. If d is a non-trivial (i.e. d =/= 1) divisor of t(n) = 2n^2 - 1, then
    (a) d does not divide n, n+1, or n-1. Equivalently, for no integer k will
        n + kd be 0 or +/- 1.
    (b) d divides t(+/- n + k d) for all integer k.

(Proof) For (a), note that d cannot divide 1 and t(n) = 2(n +/- 1)^2 -/+ 4(n +/-1) + 1. 
For (b), note that t(+/- n + k d) = t(n) +/- 4 n k d + 2 k^2 d^2.

 2. Let d be the smallest non-trivial divisor of t(n) = 2n^2 - 1. If d =/= t(n)
    then d divides t(n') for some 2 <= n' < n.

(Proof) First, we prove that d < 2n. Since d is the smallest non-trivial
divisor of t(n) but d =/= t(n), we necessarily have d^2 <= t(n).
    d^2 <= t(n) = 2n^2 - 1 < 2n^2  -->  d < sqrt(2) n < 2 n 
This implies |n - d| < n. From Claim 1a, we also have 2 <= |n - d|. From Claim
1b, d divides t(|n-d|).

The sieve works as follows: starting from n=2, by Claim 2 we know that t(2) = 7
is prime. Then all n = 7-2, 7+2, 14-2, 14+2, ... correspond to composite t(n).
So t(3) and t(4) are prime and t(5) is composite. For each composite we
encounter, if it contains a factor that we have not encountered before, we apply
the same procedure to find more composites. For instance, t(9) = 7 * 23 is
composite and 23 has not been encountered before. Then all n = 23-9, 23+9, 46-9,
46+9, ... correspond to composite t(n). 

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

