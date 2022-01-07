#!/usr/bin/python
#ANSWER 1000023

"""

We can generate R(k) mod n by the recurrence relation R(k+1) = 10R(k) + 1 (mod
n) with initial value R(1) = 1. Because n and 10 are coprime, the recurrence
relation creates a cycle. Since 10*0 + 1 = 1 = R(1), so there exists a k
> 0 such that R(k) = 0 (mod n). A(n) denotes the the smallest such k.
Additionally, since the cycle must have length <= n, so we have A(n) <= n.
Therefore, for this problem we can start finding A(n) from n=10^6. 

"""

from time import time

def A(n):
    ## also used in Problem 130
    k = 1
    R_k = 1
    while R_k != 0:
        R_k = (R_k*10 + 1) % n
        k += 1
    return k

def p129():
    n = 10**6
    while True:
        n += 1
        if n%2==0 or n%5==0:
            continue 
        if A(n) > 10**6:
            return n

if __name__ == '__main__':
    time_start = time()
    print(p129())
    print("Time: {0:.3f}".format(time()-time_start))

