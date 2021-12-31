#!/usr/bin/python
#ANSWER 49

"""

See solution explanations.

"""

from time import time

def p63():
    C = 0
    for a in range(1, 10):
        b = 1
        while len(str(a**b)) == b:
            b += 1
        C += b-1
    return C

if __name__ == '__main__':
    time_start = time()
    print(p63())
    print("Time: {0:.3f}".format(time()-time_start))

