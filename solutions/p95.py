#!/usr/bin/python
#ANSWER 14316

"""

This can be done in a fairly straightforward manner, keeping track of integers
you already traversed and using an efficient method of finding sum of divisors.

"""

from time import time
from p21 import sum_proper_divisors

def p95():
    LIMIT = 10**6
    completed = [False]*(LIMIT+1)
    completed[1] = True

    maxim = (0, None)
    for x in range(1, LIMIT):
        if completed[x]: 
            continue
        L = [] 
        while True:
            L.append(x)
            completed[x] = True
            x = sum_proper_divisors(x)
            ## stop if exceeds limit or counted already
            if x >= LIMIT or completed[x]:
                ## if chain created
                if x in L:
                    i_start = L.index(x)
                    length = len(L) - i_start 
                    if length > maxim[0]:
                        maxim = (length, L[i_start:])
                break

    return min(maxim[1])

if __name__ == '__main__':
    time_start = time()
    print(p95())
    print("Time: {0:.3f}".format(time()-time_start))

