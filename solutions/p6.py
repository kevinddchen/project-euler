#!/usr/bin/python
#ANSWER 25164150

"""

See solution explanations.

"""

from time import time

def p6():
    ## brute force
    return sum(x for x in xrange(101))**2 - sum(x*x for x in xrange(101))

if __name__ == '__main__':
    time_start = time()
    print(p6())
    print("Time: {0:.3f}".format(time()-time_start))


