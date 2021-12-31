#!/usr/bin/python
#ANSWER 100

"""

Only possiblities are diagonal cancellations, and not cancelling just the tens
digits or just the units digits.

"""

from time import time
from math import gcd

def p33():
    ans = [1, 1]
    for num in range(10, 100):
        for den in range(num+1, 100):
            x_0, x_1 = num // 10, num % 10 
            y_0, y_1 = den // 10, den % 10
            if x_0 == x_1:  ## ignore trivial
                continue
            if x_1 == y_0 and num*y_1 == den*x_0:
                ans[0] *= x_0
                ans[1] *= y_1
            if x_0 == x_1 and num*y_0 == den*x_1:
                ans[0] *= x_1
                ans[1] *= y_0
    g = gcd(ans[0], ans[1])
    return ans[1]//g

if __name__ == '__main__':
    time_start = time()
    print(p33())
    print("Time: {0:.3f}".format(time()-time_start))

