#!/usr/bin/python
#ANSWER 837799

"""

See solution explanations.

"""

from time import time
from functools import cache

@cache
def checkchain(x):
    """Returns chain length for x."""
    if x == 1: 
        return 1
    elif x%2 == 0: 
        return checkchain(x//2) + 1
    else: 
        return checkchain(3*x+1) + 1

def p14():
    return max((checkchain(x), x) for x in range(1, 1000000))[1]

if __name__ == '__main__':
    time_start = time()
    print(p14())
    print("Time: {0:.3f}".format(time()-time_start))

