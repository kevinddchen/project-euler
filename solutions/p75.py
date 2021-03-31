#!/usr/bin/python
#ANSWER 161667

"""

Generate Pythagorean triples, like in Problem 9. The perimeter is 2km(m+n).
Then iterate through all k values under the limit, and use sets to keep track
of unique perimeters.

"""

from time import time
from mathfuncs import gcd

def p75():

    MAX_L = 1500000

    good = set()
    bad = set()

    for m in xrange(2, int((MAX_L/2)**0.5)):
        n_1 = 1 if m%2==0 else 2
        for n in xrange(n_1, m, 2):
            if gcd(m, n) == 1:
                L = 2*m*(m+n)
                while L <= MAX_L:
                    if L in good:
                        good.remove(L)
                        bad.add(L)
                    elif L not in bad:
                        good.add(L)
                    L += 2*m*(m+n)

    return len(good)

if __name__ == '__main__':
    time_start = time()
    print(p75())
    print("Time: {0:.3f}".format(time()-time_start))

