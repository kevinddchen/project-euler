#!/usr/bin/python
#ANSWER 1000023

"""

See solution explanations.

"""

from time import time

def A(n):
    ## also used in Problem 130
    k = 1
    R_k = 1
    while R_k != 0:
        R_k = (R_k*10 + 1) % n
        k += 1
    return k

def p129():
    n = 10**6
    while True:
        n += 1
        if n%2==0 or n%5==0:
            continue 
        if A(n) > 10**6:
            return n

if __name__ == '__main__':
    time_start = time()
    print(p129())
    print("Time: {0:.3f}".format(time()-time_start))

