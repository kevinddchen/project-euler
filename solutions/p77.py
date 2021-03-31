#!/usr/bin/python
#ANSWER 71

"""

Make a recursive function that counts the number of ways to partition a number
using primes uner a certain maximum prime. Made faster with memoization.

"""

from time import time
from mathfuncs import isPrime

def primeGen():
    yield 2
    x = 3
    while True:
        if isPrime(x):
            yield x
        x += 2

part_dict = {}
def partition_prime(n, p_max):
    if (n, p_max) in part_dict:
        return part_dict[(n, p_max)]
    if n == 0:
        return 1

    S = 0
    for p in primeGen():
        if p > p_max or p > n:
            break
        S += partition_prime(n-p, p)
    part_dict[(n, p_max)] = S
    return S

def p77():
    x = 1
    while partition_prime(x, x) < 5000:
        x += 1
    return x

if __name__ == "__main__":
    time_start = time()
    print(p77())
    print("Time: {0:.3f}".format(time()-time_start))

