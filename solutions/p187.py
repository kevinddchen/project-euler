#!/usr/bin/python
#ANSWER 17427258

"""

Solved using a prime sieve.

"""

from time import time
from mathfuncs import primeSieve

def p187():
    LIMIT = 10**8
    p_list = []
    j = 1
    C = 0
    for i, p in enumerate(primeSieve(LIMIT/2)):
        if p*p < LIMIT:
            p_list.append(p)
        while p*p_list[-j] > LIMIT:
            j += 1
        C += i-j+2
    return C

if __name__ == '__main__':
    time_start = time()
    print(p187())
    print("Time: {0:.3f}".format(time()-time_start))


