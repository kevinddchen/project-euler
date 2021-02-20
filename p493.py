#!/usr/bin/python
#ANSWER 6.818741802

"""

Here it is important to understand how to count the different possibilities. Let
C(n, k) denote "from n choose k" and [X=k] denote "the number of ways we can
pick exactly k different colored balls". The total number of possibities is

    [X=2] + [X=3] + ... + [X=7] = C(70, 20)

and the expected value is 

    ( 2*[X=2] + 3*[X=3] + ... + 7*[X=7] ) / C(70, 20)

[X=2] is easy to calculate, as it is just 

    [X=2] = C(10, 10)*C(10, 10)*C(7, 2)

(as there are C(7, 2) ways to choose 2 colors from 7). Then it gets more complicated. For [X=3], we count all partitions of 20 into 3 pieces, with each partition being between 1 and 10 in size, making sure we do not double count. Two such partitions are {1, 9, 10} and {6, 6, 7}. For {1, 9, 10} we multiply by 3! to count all permutations, and likewise {6, 6, 7} by 3!/2!. Thus,

    [X=3] = ( C(10, 1)*C(10, 9)*C(10, 10)*3! + C(10, 6)*C(10, 6)*C(10, 7)*3!/2! + ...
                ... ) * C(7, 3)

(as there are C(7, 3) ways to choose 3 colors from 7).

"""

from time import time
from mathfuncs import choose
from math import factorial

def ordered_partitions(size, parts, limit):

    """ Gives all partition of [size] into [parts] number of partitions in
    increasing order, with maximum partition size [limit] """

    if parts == 2:
        start = max((size+1)//2, size-limit)
        end = min(limit, size-1)
        for n1 in range(start, end+1):
            yield [size-n1, n1]
    elif parts > 2:
        for n1 in range(1, limit+1):
            for part in ordered_partitions(size-n1, parts-1, n1):
                part.append(n1)
                yield part

def permutations(lst):

    """ Gives number of unique permutations of a list of numbers [lst] """

    perm = factorial(len(lst))
    s = set(lst)
    for x in s:
        perm /= factorial(lst.count(x))
    return perm

def count_color(n_colors):

    """ Gives the number of possible ways to draw [n_colors] different colors
    of balls"""

    count = 0
    for part in ordered_partitions(20, n_colors, 10):
        product = permutations(part)
        for x in part:
            product *= choose(10, x)
        count += product
    return count

def p493():
    weighted_count = 0      ## value of demonimator for expected value
    for n_colors in range(2, 8):
        weighted_count += count_color(n_colors) * choose(7, n_colors) * n_colors
    total = choose(70, 20)  ## value of numerator for expected value
    return "{0:.9f}".format(weighted_count*1./total)

if __name__ == '__main__':
    time_start = time()
    print(p493())
    print("Time: {0:.3f}".format(time()-time_start))

