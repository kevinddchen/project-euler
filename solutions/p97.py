#!/usr/bin/python
#ANSWER 8739992577

"""

Just keep track of the last 10 digits

"""

from time import time

def p97():
    x = 1
    for _ in range(7830457):
        x *= 2
        x %= 10**10
    x = x*28433+1

    return x % 10**10

if __name__ == '__main__':
    time_start = time()
    print(p97())
    print("Time: {0:.3f}".format(time()-time_start))

