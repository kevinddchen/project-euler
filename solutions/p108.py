#!/usr/bin/python
#ANSWER 180180

"""

See solution explanations.

"""

from time import time
from mathfuncs import prime_factorize

def p108():
    n = 4
    while True:
        ## count number of diviors of n^2
        n_sols = 1
        for _, i in prime_factorize(n):
            n_sols *= 2*i + 1
        n_unique_sols = (n_sols+1) // 2   ## +1 as n*n is not over-counted
        if n_unique_sols > 1000:
            return n 
        n += 1

if __name__ == '__main__':
    time_start = time()
    print(p108())
    print("Time: {0:.3f}".format(time()-time_start))

