#!/usr/bin/python
#ASNWER 1120149658760

"""

See solution explanations.

"""

from time import time

def p137():
    x, y = 1, 1
    i = 0
    while i < 15:
        x, y = (3*x+5*y)//2, (x+3*y)//2
        if x%5 == 1:
            i += 1
    return (x-1)//5

if __name__ == '__main__':
    time_start = time()
    print(p137())
    print("Time: {0:.3f}".format(time()-time_start))

