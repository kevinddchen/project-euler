#!/usr/bin/python
#ANSWER 40730

"""

Similar to Problem 30 with the condition n*9! <= 10^(n-1) satisfied by n <= 7.

"""

from time import time
from math import factorial

def generator(digits_left, initial, curr_sum):
    if digits_left == 0:
        if curr_sum == initial and initial not in [0, 1, 2]:
            yield initial
    else:
        for i in range(10):
            f = factorial(i) if not (i==0 and initial==0) else 0
            for x in generator(digits_left-1, initial*10+i, curr_sum+f):
                yield x

def p34():
    return sum(x for x in generator(7, 0, 0))

if __name__ == '__main__':
    time_start = time()
    print(p34())
    print("Time: {0:.3f}".format(time()-time_start))

