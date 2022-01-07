#!/usr/bin/python
#ANSWER 608720

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p145():
    a_1 = sum(1 for i in range(10) for j in range(10) if (i+j)%2==1 and i+j<10)
    a_2 = sum(1 for i in range(1, 10) for j in range(1, 10) if (i+j)%2==1 and i+j<10)
    b = sum(1 for i in range(10) for j in range(10) if (i+j)%2==1 and i+j>10)
    return a_2 + b*5 + a_2*a_1 + a_2*a_1**2 + b**2*5**3 + a_2*a_1**3

if __name__ == '__main__':
    time_start = time()
    print(p145())
    print("Time: {0:.3f}".format(time()-time_start))
