#!/usr/bin/python
#ANSWER 5437849

"""

See solution explanations.

"""

from time import time

def p216():
    size = 50000000
    truth_arr = [True for n in xrange(size)]
    divisor_arr = [2*n*n - 1 for n in xrange(size)]
    truth_arr[0] = False
    truth_arr[1] = False

    for n in xrange(2, size):
        tn = divisor_arr[n]      ## t(n)
        if tn != 1:

            m = n + tn                  ## t(n + k*t(n)) is divisible by t(n)
            while m < size:
                truth_arr[m] = False
                new_tn = divisor_arr[m]
                while new_tn % tn == 0:
                    new_tn /= tn
                divisor_arr[m] = new_tn
                m += tn

            m = (n//tn + 1)*tn - n      ## t(-n + k*t(n)) is divisible by t(n)
            while m < size:
                truth_arr[m] = False
                new_tn = divisor_arr[m]
                while new_tn % tn == 0:
                    new_tn /= tn
                divisor_arr[m] = new_tn
                m += tn
   
    return sum(truth_arr) 



if __name__ == '__main__':
    time_start = time()
    print(p216())
    print("Time: {0:.3f}".format(time()-time_start))

