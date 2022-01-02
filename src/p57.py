#!/usr/bin/python
#ANSWER 153

"""

See solution explanations.

"""

from time import time

def continued_fraction_of_sqrt2():
    yield 1
    while True:
        yield 2

def p57():
    C = 0
    G = continued_fraction_of_sqrt2()
    a_0 = next(G)
    a_1 = next(G)
    p = (a_0*a_1+1, a_0)
    q = (a_1, 1)
    for _ in range(1000-2):    ## starts on the second convergent
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

