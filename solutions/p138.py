#!/usr/bin/python
#ANSWER 1118049290473932

"""

See solution explanations.

"""

from time import time

def p138():
    x, y = 2, 1
    S = 0
    for i in xrange(12):
        x, y = 9*x+20*y, 4*x+9*y
        S += y
    return S

if __name__ == '__main__':
    time_start = time()
    print(p138())
    print("Time: {0:.3f}".format(time()-time_start))

