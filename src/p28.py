#!/usr/bin/python
#ANSWER 669171001

"""

See solution explanations.

"""

from time import time

def p28():
    return sum(4*x*x - 6*x + 6 for x in range(3, 1002, 2)) + 1

if __name__ == '__main__':
    time_start = time()
    print(p28())
    print("Time: {0:.3f}".format(time()-time_start))

