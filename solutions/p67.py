#!/usr/bin/python
#ANSWER 7273

"""

Same method as problem 18. Start from the bottom and work upwards.

"""

from time import time

def p67():
    with open('files/triangle.txt', 'r') as fl:
        m = [[int(x) for x in line[:-1].split(' ')] for line in fl.readlines()]

    for i in range(len(m)-2, -1, -1):
        for j in range(len(m[i])):
            m[i][j] += max(m[i+1][j], m[i+1][j+1])
    return m[0][0]

if __name__ == '__main__':
    time_start = time()
    print(p67())
    print("Time: {0:.3f}".format(time()-time_start))

