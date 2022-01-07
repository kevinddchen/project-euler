#!/usr/bin/python
#ANSWER 2406376.3623

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p389():
    var = 2464129395./1024
    return "{:.4f}".format(var)

if __name__ == '__main__':
    time_start = time()
    print(p389())
    print("Time: {0:.3f}".format(time()-time_start))
