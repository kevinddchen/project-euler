#!/usr/bin/python
#ANSWER 134043

from time import time
from mathfuncs import primeFactorize

def p47():
    L = [len([f for f, i in primeFactorize(x)]) for x in [2, 3, 4, 5]]
    j = 2
    while L != [4, 4, 4, 4]:
        L.pop(0)
        L.append( len([f for f, i in primeFactorize(j+4)]) )
        j += 1
    return j


if __name__ == '__main__':
    time_start = time()
    print(p47())
    print("Time: {0:.3f}".format(time()-time_start))

