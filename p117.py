#!/usr/bin/python
#ANSWER 100808458960497

from time import time

def p117():
    L = [1, 0, 0, 0]
    for i in xrange(50):
        L.insert(0, L[0] + L[1] + L[2] + L.pop())
    return L[0]

if __name__ == '__main__':
    time_start = time()
    print(p117())
    print("Time: {0:.3f}".format(time()-time_start))

