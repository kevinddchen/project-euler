#!/usr/bin/python
#ANSWER 837799

from time import time

chaindict = {}
def checkchain(x):
    """Returns chain length for x; memoized."""
    if x == 1: 
        return 1
    elif x in chaindict: 
        return chaindict[x]
    elif not x%2: 
        chaindict[x] = checkchain(x/2) + 1
    else: 
        chaindict[x] = checkchain(3*x+1) + 1
    return chaindict[x]

def p14():
    return max((checkchain(x), x) for x in xrange(1, 1000000))[1]

if __name__ == '__main__':
    time_start = time()
    print(p14())
    print("Time: {0:.3f}".format(time()-time_start))

