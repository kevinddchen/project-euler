#!/usr/bin/python
#ANSWER 3D58725572C62302

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p162():
    S = sum(15*16**n - 43*15**n + 41*14**n - 13**(n+1) for n in range(2, 16))
    return hex(S)[2:-1].upper()

if __name__ == '__main__':
    time_start = time()
    print(p162())
    print("Time: {0:.3f}".format(time()-time_start))

