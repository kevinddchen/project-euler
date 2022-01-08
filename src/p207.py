#!/usr/bin/python
#ANSWER 44043947822

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p207():
    return (17*12345+1) * (17*12345+2)

if __name__ == '__main__':
    time_start = time()
    print(p207())
    print("Time: {0:.3f}".format(time()-time_start))
