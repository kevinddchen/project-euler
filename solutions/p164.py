#!/usr/bin/python
#ANSWER 378158756814587

"""

Brute force. My strategy was counting three digits at a time, keep adding
digits and counting all possibilities until you reach 20 digits.

"""

from time import time

def add_dict(dct, key, value):
    if key in dct:
        dct[key] += value
    else:
        dct[key] = value

def initial_seeds():
    dct = {}
    for a in range(1, 10):
        for b in range(10):
            for c in range(10):
                if a+b+c < 10:
                    add_dict(dct, str(b)+str(c), 1)
    return dct

def iterate_seeds(dct):
    new_dct = {}
    for x in dct:
        digit_sum = int(x[0])+int(x[1])
        for i in range(10-digit_sum):
            add_dict(new_dct, x[1]+str(i), dct[x])
    return new_dct

def p164():
    A = initial_seeds()
    for _ in range(17):
        A = iterate_seeds(A)
    return sum(A.values())

if __name__ == '__main__':
    time_start = time()
    print(p164())
    print("Time: {0:.3f}".format(time()-time_start))

