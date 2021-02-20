#!/usr/bin/python
#ANSWER 9183

from time import time

def p29():
    return len(set(a**b for a in xrange(2, 101) for b in xrange(2, 101)))

if __name__ == '__main__':
    time_start = time()
    print(p29())
    print("Time: {0:.3f}".format(time()-time_start))

