#!/usr/bin/python
#ANSWER 137846528820

"""

See solution explanations.

"""

from time import time
from mathfuncs import choose

def p15():
    return choose(40, 20)

if __name__ == '__main__':
    time_start = time()
    print(p15())
    print("Time: {0:.3f}".format(time()-time_start))

