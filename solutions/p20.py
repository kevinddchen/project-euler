#!/usr/bin/python
#ANSWER 648

from time import time
from math import factorial

def p20():
    return sum(int(n) for n in str(factorial(100)))

if __name__ == '__main__':
    time_start = time()
    print(p20())
    print("Time: {0:.3f}".format(time()-time_start))

