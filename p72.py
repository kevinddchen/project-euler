#!/usr/bin/python
#ANSWER 303963552391

"""

See solution explanations.

"""

from time import time
import sys
sys.dont_write_bytecode = True
import p69

def p72():
    return sum(tot for n, tot in p69.totientSieve(1000000))

if __name__ == '__main__':
    time_start = time()
    print(p72())
    print("Time: {0:.3f}".format(time()-time_start))
    
