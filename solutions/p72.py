#!/usr/bin/python
#ANSWER 303963552391

"""

See solution explanations.

"""

from time import time
from p69 import totient_sieve

def p72():
    return sum(tot for _, tot in totient_sieve(1000000))

if __name__ == '__main__':
    time_start = time()
    print(p72())
    print("Time: {0:.3f}".format(time()-time_start))
    
