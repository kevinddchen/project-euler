#!/usr/bin/python
#ANSWER 510510

"""

See solution explanations.

Here we use a sieve to generate totient values.

"""

from time import time

def totient_sieve(limit):
    ## sieve that generates totient values.
    ## also used in Problem 72
    a = [i for i in range(limit+1)]
    for i, tot in enumerate(a):
        if i < 2:
            continue
        if i == tot:        ## is prime
            tot -= 1
            for j in range(i, limit+1, i):  ## i divides j
                a[j] = a[j]*(i-1)//i
        yield i, tot

def p69():
    M = (6, 2) # (n, tot(n))
    for n, tot in totient_sieve(1000000):
        if n*M[1] > tot*M[0]:
            M = (n, tot)
    return M[0]

if __name__ == '__main__':
    time_start = time()
    print(p69())
    print("Time: {0:.3f}".format(time()-time_start))
