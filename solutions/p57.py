#!/usr/bin/python
#ANSWER 153

"""

Computing continued fraction convergents like in Problem 65.

"""

from time import time

def generateContFrac_2():
    yield 1
    while True:
        yield 2

def p57():
    C = 0
    G = generateContFrac_2()
    a_0 = next(G)
    a_1 = next(G)
    p = (a_0*a_1+1, a_0)
    q = (a_1, 1)
    for i in xrange(1000-2):    ## starts on the second convergent
        if len(str(p[0])) > len(str(q[0])):
            C += 1
        a = next(G)
        p = (a*p[0]+p[1], p[0])
        q = (a*q[0]+q[1], q[0])
    return C

if __name__ == '__main__':
    time_start = time()
    print(p57())
    print("Time: {0:.3f}".format(time()-time_start))

