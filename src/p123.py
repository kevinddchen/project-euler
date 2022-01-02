#!/usr/bin/python
#ANSWER 21035

"""

Just like in Problem 120, the remainder for odd n is 2*n*p_n mod (p_n)^2. For
large n, p_n > 2*n so the remainder is just simply 2*n*p_n. So we are just
finding the smallest odd n such that n*p_n > 5e9

"""

from time import time
from mathfuncs import is_prime

def p123():
    p, n = 3, 2
    while True:
        p += 2
        if is_prime(p):
            n += 1
            if n%2==1 and n*p > 5e9:
                return n

if __name__ == '__main__':
    time_start = time()
    print(p123())
    print("Time: {0:.3f}".format(time()-time_start))

