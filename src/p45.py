#!/usr/bin/python
#ANSWER 1533776805

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p45():
    x, y = 1, 1
    for _ in range(9):
        x, y = 2*x + 3*y, x + 2*y
    n = (y+1) // 4
    return n*(2*n-1)


if __name__ == '__main__':
    time_start = time()
    print(p45())
    print("Time: {0:.3f}".format(time()-time_start))

