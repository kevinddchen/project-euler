#!/usr/bin/python
#ANSWER 232792560

"""

See solution explanations.

"""

from time import time
from mathfuncs import primeFactorize

def p5():
    ## prime factorize numbers
    L = [] 
    for x in xrange(2, 20):
        for f, i in primeFactorize(x):
            L.extend([f]*(i - L.count(f)))

    ## multiply out factors
    return reduce( lambda x, y: x*y , L )

if __name__ == '__main__':
    time_start = time()
    print(p5())
    print("Time: {0:.3f}".format(time()-time_start))

