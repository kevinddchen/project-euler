#!/usr/bin/python
#ANSWER 1389019170

"""

If x^2 has a 0 in the digits place, then x is a multiple of 10, so the tens digit in 
the pattern is a 0. Then we are finding matches of x^2 to the pattern 1_2_3_4_5_6_7_8_9, 
so the units digit of x must be a 3 or 7.

"""

from time import time

def fitPattern(x):
    for i in xrange(9, 0, -1):
        if x%10 != i:
            return False
        x //= 100
    return True

def p206():
    n = int(10203040506070809**0.5)
    n -= n%10   ## remove first digit, which is 3 or 7
    while True:
        if fitPattern((n+3)**2):
            return (n+3)*10
        if fitPattern((n+7)**2):
            return (n+7)*10
        n += 10

if __name__ == '__main__':
    time_start = time()
    print(p206())
    print("Time: {0:.3f}".format(time()-time_start))

