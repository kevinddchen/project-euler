#!/usr/bin/python
#ANSWER 16695334890

"""

See solution explanations.

"""

from time import time

def p43():
    return (14+41)*10**8 + 30952867*2 + (1406+1460+4106+4160)*10**6 + 357289*4

if __name__ == '__main__':
    time_start = time()
    print(p43())
    print("Time: {0:.3f}".format(time()-time_start))

