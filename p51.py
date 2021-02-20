#!/usr/bin/python
#ANSWER 121313

"""

Generate all primes for a certain number of digits, then generate all patterns.
Find the first pattern that satisifes the conditions in the problem. 

"""

from time import time
from itertools import product
from mathfuncs import primeSieve

def replace(tup, x, y):
    L = []
    for z in tup:
        if z == x:  L.append(y)
        else:       L.append(z)
    return L

def test_pattern(pattern, sieve, allowance):
    err = 0
    start = 1 if pattern[0]=='*' else 0
    for d in xrange(start, 10):
        q = int(''.join(replace(pattern, '*', str(d))))
        if not sieve[q]:
            err += 1
        if err > allowance-start:
            return False
    return True

def p51x():
    digits = 2
    while True:
        ## generate primes up to 10^digits
        sieve_ref = [None]
        sieve = primeSieve(10**digits, sieve_ref)
        for p in sieve: pass

        ## generate patterns
        for pattern in product("0123456789*", repeat=digits):
            if pattern[0]=='0' or '*' not in pattern:
                continue
            if test_pattern(pattern, sieve_ref[0], 10-8):
                ## pattern found, print first prime
                start = 1 if pattern[0]=='*' else 0
                for d in xrange(start, 10):
                    q = int(''.join(replace(pattern, '*', str(d))))
                    if sieve_ref[0][q]:
                        return q
        digits += 1


    

def p51():
    x = 1 
    y = check(x)
    while y == False:
        x += 2
        while not isPrime(x):
            x += 2
        y = check(x)
    return y

if __name__ == '__main__':
    time_start = time()
    print(p51x())
    print("Time: {0:.3f}".format(time()-time_start))

