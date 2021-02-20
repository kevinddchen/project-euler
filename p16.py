#!/usr/bin/python
#ANSWER 1366

from time import time

def p16():
    return sum(int(n) for n in str(2**1000))

if __name__ == '__main__':
    time_start = time()
    print(p16())
    print("Time: {0:.3f}".format(time()-time_start))

