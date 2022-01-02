#!/usr/bin/python
#ANSWER 296962999629

"""

It is faster to generate 4-digit primes, go through permutations for a larger
prime, then find the next term in the arithmetic sequence and check that it is
a prime and permutation.

"""

from time import time
from itertools import permutations
from mathfuncs import prime_sieve

def is_permutation(a, b):
    return set(str(a))==set(str(b))

def p49():
    sieve = []
    prime_generator = prime_sieve(10000, sieve)
    for _ in prime_generator: 
        pass

    for p, isprime in enumerate(sieve):
        ## search for 4 digit primes
        if p < 1000 or not isprime: 
            continue
        ## cycle through permutations for prime
        for perm in permutations(str(p)):
            q = int(''.join(perm))
            if q>p and 10000>q and sieve[q]:
                ## get next prime in sequence, check is permutation
                r = q+(q-p)
                if 10000>r and sieve[r] and is_permutation(r, p):
                    ## not first one
                    if p != 1487:
                        return str(p)+str(q)+str(r)

if __name__ == '__main__':
    time_start = time()
    print(p49())
    print("Time: {0:.3f}".format(time()-time_start))

