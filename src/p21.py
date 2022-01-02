#!/usr/bin/python
#ANSWER 31626

from time import time
from math import prod
from mathfuncs import prime_factorize

def sum_proper_divisors(x):
    ## return sum of proper divisors
    ## also used in Problem 23 and 95
    if x == 1:
        return 0
    return prod((p**(i+1)-1) // (p-1) for p, i in prime_factorize(x)) - x



def p21():
    S = 0
    for start in range(2, 10000):
        end = sum_proper_divisors(start)
        if sum_proper_divisors(end) == start and start != end: 
            S += start
    return S

if __name__ == '__main__':
    time_start = time()
    print(p21())
    print("Time: {0:.3f}".format(time()-time_start))

