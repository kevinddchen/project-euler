#!/usr/bin/python
#ANSWER 1587000

from time import time

def increasing(x):
    s = str(x)
    for i in range(len(s)-1):
        if s[i+1] < s[i]:
            return False
    return True

def decreasing(x):
    s = str(x)
    for i in range(len(s)-1):
        if s[i+1] > s[i]:
            return False
    return True

def p112():
    n_bouncy = 0.0
    x = 100
    while n_bouncy*100 != x*99:
        x += 1
        if not increasing(x) and not decreasing(x):
            n_bouncy += 1
    return x

if __name__ == '__main__':
    time_start = time()
    print(p112())
    print("Time: {0:.3f}".format(time()-time_start))

