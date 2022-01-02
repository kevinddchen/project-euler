#!/usr/bin/python
#ANSWER 906609

from time import time

def p4():
    maxproduct = 0
    a, b = 999, 999
    while a*b > maxproduct:
        while a*b > maxproduct:
            if str(a*b) == str(a*b)[::-1]:
                maxproduct = a*b
                break
            b -= 1
        a -= 1
        b = a
    return maxproduct

if __name__ == '__main__':
    time_start = time()
    print(p4())
    print("Time: {0:.3f}".format(time()-time_start))

