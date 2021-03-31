#!/usr/bin/python
#ANSWER 6531031914842725

"""

As the question asks for 16-digit strings, we can assume that 10 lies in
the outer ring. Also as the string starts on the lowest outer ring number, its
maximum possible value is 6. Using these two constraints, we can generate all
5-gon rings in decreasing order, in terms of their string representation. Then
the first valid magic 5-gon is already maximal and is the answer.

"""

from time import time
from itertools import permutations

def generate5Gons():
    """generate all 5-gon rings in decreasing string order"""
    for start in range(6, 0, -1):
        for a in permutations(range(10, start, -1), 4):
            if 10 not in a:     ## we are looking for 16-digit strings
                continue
            a = (start,) + a
            for b in permutations([x for x in range(9, 0, -1) if x not in a]):
                yield a, b

def p68():
    for a, b in generate5Gons():
        # a, b are outer, inner rings, in clockwise order.
        sets = []
        t = True
        for i in xrange(5):
            sets.append((a[i], b[i], b[(i+1)%5]))
            if sum(sets[i])!=sum(sets[0]):
                t = False
                break

        ## t tracks if we have a magic 5-gon. If True, we have answer
        if t:
            string = ''
            for s in sets:
                for x in s:
                    string += str(x)
            return string

if __name__ == '__main__':
    time_start = time()
    print(p68())
    print("Time: {0:.3f}".format(time()-time_start))

