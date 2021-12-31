#!/usr/bin/python
#ANSWER 997651

"""

Here I generate all the primes under a million, then add every consecutive
run up and check that it is prime.

"""

from time import time
from mathfuncs import prime_sieve

def gen_next_primes(p, sieve):
    p += 1
    while p < len(sieve):
        if sieve[p]:
            yield p
        p += 1

def p50():
    sieve = []
    prime_generator = prime_sieve(1000000, sieve)
    for _ in prime_generator: 
        pass

    M = (0, 0)
    for p, isprime in enumerate(sieve):
        if isprime:
            S = p
            length = 1
            for q in gen_next_primes(p, sieve):
                S += q
                length += 1 
                if S >= 1000000:
                    break
                if sieve[S] and length>M[0]:
                    M = (length, S)
    return M[1]

if __name__ == '__main__':
    time_start = time()
    print(p50())
    print("Time: {0:.3f}".format(time()-time_start))

