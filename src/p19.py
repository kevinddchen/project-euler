#!/usr/bin/python
#ANSWER 171

"""

See solution explanations.

"""

from time import time

def p19():
    ## use John Conway's Doomsday algorithm
    count = 0
    ## for each month, first day that is a doomsday
    doomsday_table = [3, 7, 7, 4, 2, 6, 4, 1, 5, 3, 7, 5]
    for y in range(1901, 2001):
        doomsday = (2 + y + y//4 - y//100 + y//400)%7
        leap = True if y%400==0 or (y%4==0 and y%100!=0) else False
        for m in range(0, 12):
            d = doomsday_table[m]
            if (m==0 or m==1) and leap:
                d += 1
            if (doomsday-d+1)%7 == 0:   ## if Sunday
                count += 1
    return count

if __name__ == '__main__':
    time_start = time()
    print(p19())
    print("Time: {0:.3f}".format(time()-time_start))

