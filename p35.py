#!/usr/bin/python
#ANSWER 55

from time import time
from mathfuncs import primeSieve

def circular(n, sieve):
    """Returns True if n is a circular prime, as defined above."""
    n = str(n)
    for i in xrange(len(n)):
        if not sieve[int(n[i:]+n[:i])]:
            return False
    return True

def p35():
    S_ref = [None]
    S = primeSieve(1000000, S_ref)
    for p in S:
        pass
    sieve = S_ref[0]

    return sum(1 for p, isprime in enumerate(sieve) if isprime and circular(p, sieve))

if __name__ == '__main__':
    time_start = time()
    print(p35())
    print("Time: {0:.3f}".format(time()-time_start))

