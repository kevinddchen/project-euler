#!/usr/bin/python
#ANSWER 51161058134250 

"""

See solution explanations. 

"""

from time import time
from math import comb

def p113():
    return comb(109, 9) + comb(110, 10) - 1002

if __name__ == '__main__':
    time_start = time()
    print(p113())
    print("Time: {0:.3f}".format(time()-time_start))

