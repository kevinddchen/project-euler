#!/usr/bin/python
#ANSWER 4179871

from time import time
from mathfuncs import primeFactorize

def sumDivisors(x):
    prod = 1
    for p, i in primeFactorize(x):
        prod *= (p**(i+1)-1)/(p-1)
    return prod

def p23():
    abundants = []
    for x in xrange(1, 28124):
        if sumDivisors(x) > 2*x:
            abundants.append(x)
    summable = set()
    for i, a in enumerate(abundants): 
        for b in abundants[i:]:
            if a+b < 28124:
                summable.add(a+b)
            else:
                break
    ## sum of all numbers under 28124 minus sum of abundants
    return 28123*28124/2 - sum(summable)

if __name__ == '__main__':
    time_start = time()
    print(p23())
    print("Time: {0:.3f}".format(time()-time_start))

