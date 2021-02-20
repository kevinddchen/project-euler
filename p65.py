#!/usr/bin/python
#ANSWER 272

"""

See solution explanations. 

"""

from time import time

def generateContFrac_e():
    yield 2
    k = 2
    while True:
        yield 1
        yield k
        yield 1
        k += 2

def p65():
    G = generateContFrac_e()
    a_0 = next(G)
    a_1 = next(G)
    p = (a_0*a_1+1, a_0)
    q = (a_1, 1)
    for i in xrange(100-2):    ## starts on second convergent
        a = next(G)
        p = (a*p[0]+p[1], p[0])
        q = (a*q[0]+q[1], q[0])
    return sum(int(c) for c in str(p[0]))

if __name__ == '__main__':
    time_start = time()
    print(p65())
    print("Time: {0:.3f}".format(time()-time_start))

