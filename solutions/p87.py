#!/usr/bin/python
#ANSWER 1097343

"""

If you generate all the primes and create the set of all combinations, it is
quite straightforward to count them all.

"""

from time import time
from mathfuncs import isPrime

def primeGen(maxim):
    yield 2
    x = 3
    while x <= maxim:
        if isPrime(x):
            yield x
        x += 2

def power_triple(a, b, c): 
    return a**2 + b**3 + c**4

def p87():
    TARGET = 50000000
    max_c = int((TARGET - 2**3 - 2**4)**0.5)
    primes = list(primeGen(max_c))
    sum_set = set([])

    for c in primes:
        for b in primes:
            if power_triple(2, b, c) > TARGET:
                break
            for a in primes:
                s = power_triple(a, b, c)
                if s < TARGET:
                    sum_set.add(s)
                else:
                    break

    return len(sum_set)
            
if __name__ == '__main__':
    time_start = time()
    print(p87())
    print("Time: {0:.3f}".format(time()-time_start))
