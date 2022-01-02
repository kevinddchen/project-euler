#!/usr/bin/python
#ANSWER 843296

"""

See solution explanations.

"""

from time import time
from mathfuncs import is_prime

def p132():
    C, S = 0, 0
    p = 5
    while C < 40:
        p += 2
        if not is_prime(p):
            continue
        if pow(10, pow(10, 9, p-1), p) == 1:
            C += 1
            S += p
    return S

if __name__ == '__main__':
    time_start = time()
    print(p132())
    print("Time: {0:.3f}".format(time()-time_start))

