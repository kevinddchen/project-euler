#!/usr/bin/python
#ANSWER 55374

"""

We can use the exact same methods in problem 76 to solve this one.

"""

from time import time
import sys
sys.dont_write_bytecode = True
import p76

def p78():
    n = 100
    while p76.partition(n)%1000000 != 0:
        n += 1
    return n

if __name__ == '__main__':
    time_start = time()
    print(p78())
    print("Time: {0:.3f}".format(time()-time_start))

