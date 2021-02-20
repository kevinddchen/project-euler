#!/usr/bin/python
#ANSWER 1217

"""

The scope of this problem is small enough to use brute force and generate all
dice combinations.

"""

from time import time
from itertools import combinations

square_list = [(0,1), (0,4), (0,6), (1,6), (1,8), (2,5), (3,6), (4,6)] 
def check_dice(d1, d2):
    for sq1, sq2 in square_list:
        if not ((sq1 in d1 and sq2 in d2) or (sq1 in d2 and sq2 in d1)):
            return False
    return True

def p90():
    count = 0
    for d1 in combinations(xrange(10), 6):
        if 9 in d1:
            d1 += (6,)
        for d2 in combinations(xrange(10), 6):
            if 9 in d2:
                d2 += (6,)
            if check_dice(d1, d2):
                count += 1

    return count/2     ## divide by 2 for doublecounting

if __name__ == '__main__':
    time_start = time()
    print(p90())
    print("Time: {0:.3f}".format(time()-time_start))

