#!/usr/bin/python
#ANSWER 1856532.8455

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time
from math import pi

def p317():
    volume = 2 * pi * (20*20 / (2*9.81)) * (100 + 20*20 / (2*9.81))**2
    return "{:.4f}".format(volume)

if __name__ == '__main__':
    time_start = time()
    print(p317())
    print("Time: {0:.3f}".format(time()-time_start))
