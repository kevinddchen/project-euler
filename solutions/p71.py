#!/usr/bin/python
#ANSWER 428570

"""

For a given q, the largest p such that p/q < 3/7 is given by p = (3q-1)/7. This
is because p/q < 3/7 implies 7p <= 3q-1.

Then we iterate through q in decreasing order. We can also let a lower bound
for q, relative to the previously found minimum. If we define a distance from
3/7 as d(p/q) = 3/7 - p/q = (3q - 7p)/(7q) > 1/(7q), then d(p'/q') < d(p/q) 
implies 1/(7q') < (3q - 7p)/(7q) or q' > q/(3q - 7p).

"""

from time import time
from mathfuncs import gcd

def p71():
    prev = (2, 5)
    for q in xrange(1000000, 0, -1):
        ## stop
        if q*(3*prev[1] - 7*prev[0]) <= prev[1]:
            break
        p = int((q*3-1.)/7)     ## p/q just under 3/7
        if p*prev[1] > prev[0]*q:
            prev = (p, q)

    return prev[0] / gcd(prev[0], prev[1])

if __name__ == '__main__':
    time_start = time()
    print(p71())
    print("Time: {0:.3f}".format(time()-time_start))


