#!/usr/bin/python
#ANSWER 73702

"""

Brute force. Not really any choice.

"""

from time import time

def noEqualSums(lst, s=0, changes=0):
    """ Checks that every linear combination of lst using coefficients in [1,
    -1, 0] doesnt equal to zero (except trivial case). Satisfies (i)."""
    if len(lst) == 0:
        return (changes == 0 or s != 0)
    for x in [1, -1, 0]:
        if not noEqualSums(lst[1:], s+lst[0]*x, changes+abs(x)):
            return False
    return True

def order(lst):
    """ Checks that sum of first n+1 numbers must be greater than sum of last
    n numbers. As long as lst is sorted, satisfies (ii). """
    for x in range((len(lst)-1) // 2):
        if sum(lst[:x+2]) <= sum(lst[-x-1:]):
            return False
    return True
         
def p105():    
    with open('files/sets.txt', 'r') as fl:
        allSets = fl.read().split('\n')

    s = 0
    for raw_set in allSets:
        lst = sorted([int(x) for x in raw_set.split(',')])
        if order(lst) and noEqualSums(lst): 
            s += sum(lst)
    return s

if __name__ == '__main__':
    time_start = time()
    print(p105())
    print("Time: {0:.3f}".format(time()-time_start))

