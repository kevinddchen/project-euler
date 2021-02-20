#!/usr/bin/python
#ANSWER 1322

"""

See solution explanations.

Used by Problem 66

"""

from time import time

def generateSqrtContFrac(n):
    m, d, a = 0, 1, int(n**0.5)
    yield a
    while True:
        m = d*a-m
        d = (n-m*m)/d
        a = int((n**0.5 + m)/d)
        yield a

def p64():
    C = 0
    for n in xrange(10001):
        a_0 = int(n**0.5)
        if n == a_0*a_0:        ## n is a perfect square
            continue

        for i, a in enumerate(generateSqrtContFrac(n)):
            if a == 2*a_0:
                break

        if i%2 == 1:
            C += 1
    return C

if __name__ == '__main__':
    time_start = time()
    print(p64())
    print("Time: {0:.3f}".format(time()-time_start))
        
