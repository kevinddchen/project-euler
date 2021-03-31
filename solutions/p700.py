#!/usr/bin/python
#ANSWER 1517926517777556

"""

Let E1 be the first Eulercoin and P be the large prime. The other Eulercoins can be determined using long division:

    E2 = ( 3 * E1 ) % P
    E3 = ( 2 * E1 + 168 * E2 ) % P
    E4 = ( 2 * E1 + 167 * E2 + 4 * E3 ) % P
    ...

"""

from time import time


def p700():

    a = 4503599627370517
    b = 1504170715041707
    S = b

    while b != 1:

        d = a // b
        r = (b * (d+1)) - a

        a, b = a - d*b, r
        S = S + b

    return S


if __name__ == '__main__':
    time_start = time()
    print(p700())
    print("Time: {0:.3f}".format(time()-time_start))



