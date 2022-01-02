#!/usr/bin/python
#ANSWER 1.710637717

"""

See solution explanations.

"""

from time import time

def f(x):
    return int(2**(30.403243784-x**2)) * 1e-9

def p197():
    u = -1
    for _ in range(1000):
        u = f(u)
    return '{0:.9f}'.format(u+f(u))

if __name__ == '__main__':
    time_start = time()
    print(p197())
    print("Time: {0:.3f}".format(time()-time_start))
