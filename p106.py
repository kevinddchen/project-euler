#!/usr/bin/python
#ANSWER 21384

"""

See solution explanations.

"""

from time import time
from mathfuncs import choose

def p106():
    return sum(choose(12, 2*k)*choose(2*k, k)*(k-1)/(k+1) for k in xrange(2, 7))/2

if __name__ == '__main__':
    time_start = time()
    print(p106())
    print("Time: {0:.3f}".format(time()-time_start))

