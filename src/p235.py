#!/usr/bin/python
#ANSWER 1.002322108633

"""

See solution explanations.

"""

from time import time
import decimal
decimal.getcontext().prec = 13
decimal.getcontext().rounding = decimal.ROUND_HALF_UP

def sum_arithgeo_series(a, d, r, n):
    A = a + (d-a)*r - (a+n*d)*r**n + (a+n*d-d)*r**(n+1)
    return A/(1-r)**2

def p235():
    TARGET = decimal.Decimal("-600000000000")
    r_bounds = [decimal.Decimal(1), decimal.Decimal(1.01)]
    prev = 0
    while True:
        r = (r_bounds[1] + r_bounds[0])/2
        s = sum_arithgeo_series(897, -3, r, 5000)
        if r == prev:
            return str(r)
        elif s < TARGET:
            r_bounds[1] = r
        else:
            r_bounds[0] = r
        prev = r

if __name__ == '__main__':
    time_start = time()
    print(p235())
    print("Time: {0:.3f}".format(time()-time_start))

