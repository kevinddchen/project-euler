#!/usr/bin/python
#ANSWER 142857

"""

Very direct approach; check each integer with no repeating digits that its
multiples are permutations. In fact, the answer is the repeating decimal part
of 1/7, which has the property stated in the question. 

"""

from time import time

def p52():
    x = 0
    d = 1
    while True:
        ## increment x
        x += 1
        if len(str(6*x)) > d:
            x = 10**d
            d += 1

        digit_set = set(str(x))
        ## check no repeated digits
        if len(digit_set) < d:
            continue

        ## check multiples are permutations
        for i in xrange(2, 7):
            if digit_set != set(str(i*x)): 
                break
            if i == 6:
                return x

if __name__ == '__main__':
    time_start = time()
    print(p52())
    print("Time: {0:.3f}".format(time()-time_start))

