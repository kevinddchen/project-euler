#!/usr/bin/python
#ANSWER 168

"""

See solution explanations.

"""

from time import time

def p115():
    L = [2] + [1]*50
    i = 50
    while L[0] <= 1000000:
        i += 1
        L.insert(0, 2*L[0] - L[1] + L.pop())
    return i

if __name__ == '__main__':
    time_start = time()
    print(p115())
    print("Time: {0:.3f}".format(time()-time_start))

