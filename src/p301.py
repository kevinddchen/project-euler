#!/usr/bin/python
#ANSWER 2178309

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p301():
    a, b = 2, 3
    for _ in range(28):
        a, b = b, a+b
    return b

if __name__ == '__main__':
    time_start = time()
    print(p301())
    print("Time: {0:.3f}".format(time()-time_start))


