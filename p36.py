#!/usr/bin/python
#ANSWER 872187

from time import time

## only odd numbers can be palindrones in binary
def p36():
    return sum(x for x in range(1, 1000000, 2) if \
        str(x)==str(x)[::-1] and bin(x)[2:]==bin(x)[:1:-1])

if __name__ == '__main__':
    time_start = time()
    print(p36())
    print("Time: {0:.3f}".format(time()-time_start))
