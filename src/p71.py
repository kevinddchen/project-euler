#!/usr/bin/python
#ANSWER 428570

"""

For a given q, the largest p such that p/q < 3/7 is given by p =
floor((3q-1)/7). This is because p/q < 3/7 implies 7p <= 3q-1.

We iterate through q in decreasing order to a lower bound that depends on the
current closest fraction. Note that p/q <= 3/7 - 1/7q. This means that if p'/q'
is the current closest fraction, then it is guaranteed to be closer for all q
where 3/7 - p'/q' <= 1/7q.

"""

from time import time
from math import gcd

def p71():
    prev = (2, 5)       ## (p, q)
    for q in range(1000000, 0, -1):
        if q*(3*prev[1] - 7*prev[0]) <= prev[1]:
            break
        p = (q*3-1) // 7    ## p/q just under 3/7
        if p*prev[1] > prev[0]*q:
            prev = (p, q)

    return prev[0] // gcd(prev[0], prev[1])

if __name__ == '__main__':
    time_start = time()
    print(p71())
    print("Time: {0:.3f}".format(time()-time_start))


