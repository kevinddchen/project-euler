#!/usr/bin/python
#ANSWER 73162890

"""

This problem is best solved by hand. From the key logger we created a graph
that tracked the well-ordering of the characters according to their occurances.
This method is guaranteed to work with non-repeating digits.

"""

from time import time

def popLongestList(d):
    x = max([(len(d[x]), x) for x in d])[1]
    del d[x]
    return x

def p79():
    ## Create graph
    dct = {}
    with open('files/keylog.txt', 'r') as fl:
        for line in fl.readlines():
            a, b, c = [int(x) for x in line.strip('\n')]
            for x in a, b, c:
                if x not in dct:
                    dct[x] = set()
            dct[a].add(b)
            dct[a].add(c)
            dct[b].add(c)
            
    ## Figure out well-ordering
    s = ''
    while len(dct) > 0:
        s += str(popLongestList(dct))
    return s

if __name__ == '__main__':
    time_start = time()
    print(p79())
    print("Time: {0:.3f}".format(time()-time_start))

