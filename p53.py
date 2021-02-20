#!/usr/bin/python
#ANSWER 4075

from time import time
from mathfuncs import choose

def p53():
    C = 0
    for n in xrange(1, 101):
        ## using symmetry C(n, r) = C(n, n-r)
        ## skip C(n, 0)=1 and C(n, 1)=n
        for r in xrange(2, n//2+1):
            if choose(n, r) > 1000000: 
                C += 1 if r*2==n else 2
    return C

if __name__ == '__main__':
    time_start = time()
    print(p53())
    print("Time: {0:.3f}".format(time()-time_start))

