#!/usr/bin/python
#ANSWER 55

from time import time
from mathfuncs import prime_sieve

def circular(n, sieve):
    """Returns True if n is a circular prime."""
    n = str(n)
    for i in range(len(n)):
        if not sieve[int(n[i:]+n[:i])]:
            return False
    return True

def p35():
    sieve = []
    prime_generator = prime_sieve(1000000, sieve)
    for _ in prime_generator:
        pass

    return sum(1 for p, isprime in enumerate(sieve) if isprime and circular(p, sieve))

if __name__ == '__main__':
    time_start = time()
    print(p35())
    print("Time: {0:.3f}".format(time()-time_start))

