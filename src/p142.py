#!/usr/bin/python
#ANSWER 1006193

"""

Note that x is the midpoint between two pairs of squares: x+y and x-y, and x+z
and x-z. So generate all pairs of squares, keeping track of midpoints.  When
two pairs have the same midpoints, check that y+z and y-z are squares.

"""

from time import time
from math import isqrt

def is_square(n):
    """ Returns True if n is a perfect square. """
    return n == isqrt(n)**2

def p142():
    target = 1e99
    mid_dict = {}       # dictionary to keep track of midpoints

    a = 1       # a*a = x+y
    while a*a < target:
        parity = 2 - (a % 2)
        for b in range(parity, a, 2):       # b*b = x-y
            mid = (a*a + b*b) // 2             # mid = x

            if mid in mid_dict:

                for c in mid_dict[mid]:
                    y = a*a - mid
                    z = c*c - mid
                    if is_square(y+z) and is_square(y-z):
                        target = a*a + z    # target is minimum x+y+z so far

                mid_dict[mid].append(a)

            else:

                mid_dict[mid] = [a]

        a += 1

    return target

if __name__ == '__main__':
    time_start = time()
    print(p142())
    print("Time: {0:.3f}".format(time()-time_start))

