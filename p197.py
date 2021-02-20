#!/usr/bin/python
#ANSWER 1.710637717

"""

Here we want to find the stable fixed-points of the given map. We can do this by
iterating until the function oscillates between the stable values. Turns out
there are two values, which we take the sum of.

"""

from time import time

def f(x):
    return int(2**(30.403243784-x**2)) * 1e-9

def p197():
    u = -1
    for i in xrange(1000):
        u = f(u)
    return '{0:.9f}'.format(u+f(u))

if __name__ == '__main__':
    time_start = time()
    print(p197())
    print("Time: {0:.3f}".format(time()-time_start))
