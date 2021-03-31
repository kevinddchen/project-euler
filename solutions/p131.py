#!/usr/bin/python
#ANSWER: 173

"""

See solution explanations.

"""

from time import time
from mathfuncs import isPrime

def p131():
    return sum(1 for k in xrange(1, 578) if isPrime(3*k*(k-1)+1))

if __name__ == '__main__':
    time_start = time()
    print(p131()) 
    print("Time: {0:.3f}".format(time()-time_start))

