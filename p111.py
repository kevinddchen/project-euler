#!/usr/bin/python
#ANSWER 612407567715

from time import time
from mathfuncs import isPrime
from itertools import combinations, product

def matchPattern(pattern, d, DIGITS):
    number = [d]*DIGITS
    for prod in product(range(10), repeat=len(pattern)):
        for i, place in enumerate(pattern):
            number[place] = prod[i]
        if number[-1] == 0:
            continue
        x = sum(y*10**i for i, y in enumerate(number))
        if isPrime(x):
            yield x

def p111():
    DIGITS = 10
    S = 0
    for d in xrange(10):
        for M in xrange(DIGITS-1, 0, -1):
            prime_list = []
            for pattern in combinations(range(DIGITS), DIGITS-M):
                prime_list.extend(matchPattern(pattern, d, DIGITS))
            if len(prime_list) != 0:
                break
        S += sum(prime_list)
    return S

if __name__ == '__main__':
    time_start = time()
    print(p111())
    print("Time: {0:.3f}".format(time()-time_start))

