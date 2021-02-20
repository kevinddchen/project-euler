#!/usr/bin/python
#ANSWER 748317

from time import time
from mathfuncs import isPrime

def check_trunc(x):
    x_l, x_r = str(x)[1:], str(x)[:-1]
    while len(x_l) > 0:
        if not isPrime(int(x_l)) or not isPrime(int(x_r)): 
            return False
        x_l, x_r = x_l[1:], x_r[:-1]
    return True

def p37():
    count = 0
    S = 0
    x = 11
    while count < 11:
        if isPrime(x) and check_trunc(x):
            count += 1
            S += x
        x += 2
    return S

if __name__ == '__main__':
    time_start = time()
    print(p37())
    print("Time: {0:.3f}".format(time()-time_start))
        
