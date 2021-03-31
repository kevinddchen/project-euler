#!/usr/bin/python
#ANSWER 983

"""

See solution explanations.

"""

from time import time
from mathfuncs import gcd

def order(x, n):
    prod, count = x, 1
    while prod != 1:
        prod = prod*x % n
        count += 1
    return count

def p26():
    return max((order(10, n), n) for n in xrange(2, 1000) if (n%2)*(n%5)!=0)[1]

if __name__ == '__main__':
    time_start = time()
    print(p26())
    print("Time: {0:.3f}".format(time()-time_start))

