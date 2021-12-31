#!/usr/bin/python
#ANSWER 8581146

from time import time
from functools import cache

def sort_digits(x):
    return int(''.join(sorted(str(x))))

@cache
def chain(x):
    if x == 1:
        return 1
    elif x == 89:
        return 89
    square_sum = sum(int(c)**2 for c in str(x))
    return chain(sort_digits(square_sum))

def p92():
    return sum(1 for x in range(1, 10**7) if chain(sort_digits(x)) == 89)

if __name__ == '__main__':
    time_start = time()
    print(p92())
    print("Time: {0:.3f}".format(time()-time_start))

