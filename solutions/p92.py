#!/usr/bin/python
#ANSWER 8581146

from time import time

def chain(x, mem_list):
    x = int(''.join(sorted(str(x))))
    if mem_list[x] > 0:
        return mem_list[x]
    square_sum = sum(int(c)**2 for c in str(x))
    S = chain(square_sum, mem_list)
    mem_list[x] = S 
    return S

def p92():
    LIMIT = 10**7
    mem_list = [0]*LIMIT
    mem_list[1] = 1
    mem_list[89] = 89
    return sum(1 for x in xrange(1, LIMIT) if chain(x, mem_list) == 89)

if __name__ == '__main__':
    time_start = time()
    print(p92())
    print("Time: {0:.3f}".format(time()-time_start))

