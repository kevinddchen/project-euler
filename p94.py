#!/usr/bin/python
#ANSWER 518408346

"""

See solution explanations.

"""

from time import time

def p94():
    LIMIT = 10**9
    S = 0

    x, y = 4, 2
    while True:
        x, y = 2*x+3*y, x+2*y
        i = 1 if x%3==2 else -1
        a = (x+i)//3
        if 3*a+i > LIMIT:
            break
        S += 3*a + i
    return S

if __name__ == '__main__':
    time_start = time()
    print(p94())
    print("Time: {0:.3f}".format(time()-time_start))

