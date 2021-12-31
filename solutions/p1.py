#!/usr/bin/python
#ANSWER 233168

"""

See solution explanations.

"""

from time import time

def p1():
    return sum(x for x in range(1000) if x%3==0 or x%5==0)

if __name__ == '__main__':
    time_start = time()
    print(p1())
    print("Time: {0:.3f}".format(time()-time_start))

