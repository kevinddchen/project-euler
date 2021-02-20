#!/usr/bin/python
#ANSWER 142913828922

from time import time
from mathfuncs import primeSieve

def p10():
    return sum(x for x in primeSieve(2000000))

if __name__ == '__main__':
    time_start = time()
    print(p10())
    print("Time: {0:.3f}".format(time()-time_start))

