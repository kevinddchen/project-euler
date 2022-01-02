#!/usr/bin/python
#ANSWER 178653872807

"""

See solution explanations. 

"""

from time import time
from functools import cache

@cache
def f(n):
    """ As defined in the problem. """
    if n == 0:
        return 1
    elif n % 2 == 0:
        return f(n // 2) + f(n // 2 - 1)
    else:
        return f(n // 2)

def p169():
    return f(10**25)

if __name__ == '__main__':
    time_start = time()
    print(p169())
    print("Time: {0:.3f}".format(time()-time_start))

