#!/usr/bin/python
#ANSWER 17427258

"""

Solved using a prime sieve.

"""

from time import time
from mathfuncs import prime_sieve

def binary_search(x, lst):
    '''Find a slice i where x should be inserted into lst, which has been sorted
    in increasing order. If lst contains x, returns the largest slice.'''
    a, b = 0, len(lst)
    while a != b:
        mid = (a + b) // 2
        if lst[mid] > x:
            b = mid
        else:
            a = mid+1
    return a

def p187():
    LIMIT = 10**8
    p_list = []
    C = 0
    for p in prime_sieve(LIMIT//2):
        if p*p < LIMIT:
            p_list.append(p)
        j = binary_search(LIMIT//p, p_list) # number of primes p' <= p such that p' * p <= LIMIT
        C += j
    return C

if __name__ == '__main__':
    time_start = time()
    print(p187())
    print("Time: {0:.3f}".format(time()-time_start))


