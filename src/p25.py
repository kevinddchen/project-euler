#!/usr/bin/python
#ANSWER 4782

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p25():
    n = 1
    a, b = 1, 1
    while len(str(a)) < 1000:
        a, b = b, a+b
        n += 1
    return n

if __name__ == '__main__':
    time_start = time()
    print(p25())
    print("Time: {0:.3f}".format(time()-time_start))

