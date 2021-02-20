#!/usr/bin/python
#ANSWER 2906969179

from time import time

LIMIT = 10**8

def isPalindrome(n): 
    n = str(n)
    for i in xrange(len(n)//2):
        if n[i] != n[-i-1]:
            return False
    return True

def p125():
    LIMIT = 10**8
    L = set()
    for a in xrange(1, int(LIMIT**0.5)):
        S = a*a
        for b in xrange(a+1, int(LIMIT**0.5)):
            S += b*b
            if S >= LIMIT:
                break
            if isPalindrome(S):
                L.add(S)
    return sum(L)

if __name__ == '__main__':
    time_start = time()
    print(p125())
    print("Time: {0:.3f}".format(time()-time_start))


