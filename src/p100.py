#!/usr/bin/python
#ANSWER 756872327473

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p100():
    x, y = 1, 1
    while True:
        x, y = 3*x+4*y, 2*x+3*y
        if x%2==0 or y%2==0:
            continue
        b = (y+1)//2
        t = (x+1)//2
        if t > 10**12:
            break
    return b

if __name__ == '__main__':
    time_start = time()
    print(p100())
    print("Time: {0:.3f}".format(time()-time_start))

