#!/usr/bin/python
#ANSWER 333082500

"""

See solution explanations.

"""

from time import time

def p120():
    return sum(a*a - (1 if a%2==1 else 2)*a for a in xrange(3, 1001))

if __name__ == '__main__':
    time_start = time()
    print(p120())
    print("Time: {0:.3f}".format(time()-time_start))

