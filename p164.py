#!/usr/bin/python
#ANSWER 378158756814587

"""

Brute force. My strategy was counting three digits at a time, keep adding
digits and counting all possibilities until you reach 20 digits.

"""

from time import time

def addDict(dct, key, value):
    if key in dct:
        dct[key] += value
    else:
        dct[key] = value

def initialSeeds():
    dct = {}
    for a in xrange(1, 10):
        for b in xrange(10):
            for c in xrange(10):
                if a+b+c < 10:
                    addDict(dct, str(b)+str(c), 1)
    return dct

def iterateSeeds(dct):
    new_dct = {}
    for x in dct:
        digit_sum = int(x[0])+int(x[1])
        for i in xrange(10-digit_sum):
            addDict(new_dct, x[1]+str(i), dct[x])
    return new_dct

def p164():
    A = initialSeeds()
    for i in xrange(17):
        A = iterateSeeds(A)
    return sum(A.values())

if __name__ == '__main__':
    time_start = time()
    print(p164())
    print("Time: {0:.3f}".format(time()-time_start))

