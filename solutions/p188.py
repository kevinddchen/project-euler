#!/usr/bin/python
#ANSWER 95962097

"""

See solution explanations.

"""

from time import time
from mathfuncs import prime_factorize

def totient(x):
    for f, _ in prime_factorize(x):
        x = (x//f)*(f-1)
    return x

def p188():
    mod_list = [10**8]
    while mod_list[-1] != 2:
        mod_list.append(totient(mod_list[-1]))
    x = 1
    for mod in mod_list[::-1]:
        x = pow(1777, x, mod)
    return x

if __name__ == '__main__':
    time_start = time()
    print(p188())
    print("Time: {0:.3f}".format(time()-time_start))

