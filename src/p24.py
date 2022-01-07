#!/usr/bin/python
#ANSWER 2783915460

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time
from math import factorial

def p24():
    x = 10**6-1
    digits = list(range(10))

    result = 0
    for i in range(9, 0, -1):
        coeff = x // factorial(i)
        x %= factorial(i)
        result += digits.pop(coeff)*10**i
    return result

if __name__ == '__main__':
    time_start = time()
    print(p24())
    print("Time: {0:.3f}".format(time()-time_start))


