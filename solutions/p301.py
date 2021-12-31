#!/usr/bin/python
#ANSWER 2178309

"""

See solution explanations

"""

from time import time

def p301():
    a, b = 2, 3
    for _ in range(28):
        a, b = b, a+b
    return b

if __name__ == '__main__':
    time_start = time()
    print(p301())
    print("Time: {0:.3f}".format(time()-time_start))


