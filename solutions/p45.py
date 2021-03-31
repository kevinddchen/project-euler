#!/usr/bin/python
#ANSWER 1533776805

"""

See solution explanations.

"""

from time import time

def p45():
    x, y = 6*165-1, 4*143-1 
    while True:
        x, y = 2*x + 3*y, x + 2*y
        if x%6 == 5 and y%4 == 3:
            n = (y+1)/4
            return n*(2*n-1)


if __name__ == '__main__':
    time_start = time()
    print(p45())
    print("Time: {0:.3f}".format(time()-time_start))

