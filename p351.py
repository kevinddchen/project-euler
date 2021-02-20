#!/usr/bin/python

N = 20
arr = [0]*N
S = 0

from mathfuncs import gcd

for n in xrange(2, N):
    X = 0
    for m in xrange(1, min(n, N-n+1)):
        if gcd(n, m) == 1:
            X += 1

    print n, X
    S += X

print S
print (N*(N-1)/2 - 2*S + N - 2)*6







