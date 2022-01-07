#!/usr/bin/python
#ANSWER 2269

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def p121():

    N_TURNS = 15

    ## generate Stirling numbers (unsigned, of the first kind)
    L = [1]
    for n in range(N_TURNS+1):
        next_L = [0]
        for k in range(len(L)):
            if k == 0:
                continue
            next_L.append(n*L[k] + L[k-1])
        next_L.append(1)
        L = next_L

    W = sum(L[N_TURNS//2+2:])
    return sum(L) // W

if __name__ == '__main__':
    time_start = time()
    print(p121())
    print("Time: {0:.3f}".format(time()-time_start))

