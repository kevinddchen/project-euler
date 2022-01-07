#!/usr/bin/python
#ANSWER 1074

"""

Can be solved by hand. See PDF for explanation.

Start from the bottom and work upwards.

"""

from time import time

m=[[75],
[95,64],
[17,47,82],
[18,35,87,10],
[20, 4,82,47,65],
[19, 1,23,75, 3,34],
[88, 2,77,73, 7,63,67],
[99,65, 4,28, 6,16,70,92],
[41,41,26,56,83,40,80,70,33],
[41,48,72,33,47,32,37,16,94,29],
[53,71,44,65,25,43,91,52,97,51,14],
[70,11,33,28,77,73,17,78,39,68,17,57],
[91,71,52,38,17,14,91,43,58,50,27,29,48],
[63,66, 4,68,89,53,67,30,73,16,69,87,40,31],
[ 4,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23]]

def p18():
    for i in range(len(m)-2, -1, -1):
        for j in range(len(m[i])):
            m[i][j] += max(m[i+1][j], m[i+1][j+1])
    return m[0][0]

if __name__ == '__main__':
    time_start = time()
    print(p18())
    print("Time: {0:.3f}".format(time()-time_start))
    
