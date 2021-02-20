#!/usr/bin/python
#ANSWER 193060223

"""

Brute force. We can write

    2^j = a1 10^n + a2 10^(n-1) + a3 10^(n-2) + ...

and taking the logarithm,

    j * log(2) / log(10) = n + log( a1 + a2/10 + a3/100 + ... )/log(10)

Just subtract off the integer part to get rid of n, and then just compare with
the values log(1.23)/log(10) and log(1.24)/log(10) to see if the first three
digts are '123'.  

"""

from time import time
from math import log

def p686():

    CONS = log(2)/log(10)
    LOWER = log(1.23)/log(10)
    UPPER = log(1.24)/log(10)

    count = 0
    x = 0
    j = 0
    while count < 678910:
        x = (x+CONS) % 1
        j = j+1
        if (LOWER < x) and (x < UPPER):
            count = count + 1
    return j

if __name__ == '__main__':
    time_start = time()
    print(p686())
    print("Time: {0:.3f}".format(time()-time_start))



