#!/usr/bin/python
#ANSWER 104743

from time import time
from mathfuncs import isPrime

def p7():
    n, i = 1, 1
    while i < 10001: 
        n += 2
        if isPrime(n):
            i += 1
    return n

if __name__ == '__main__':
    time_start = time()
    print(p7())
    print("Time: {0:.3f}".format(time()-time_start))

