#!/usr/bin/python
#ANSWER CAGBKHJEFID 

"""

The maximix arrangements for n carridges generate the maximix arrangements for
n+1 carriges.  After that, it is pretty much brute force.  Here I use a
depth-first tree search through all maximix arrangements to save space, keeping
track of the smallest 2048 arrangements (be sure to use binary search -- this
was the slowest part of the first program).  Doesn't take long at all, as there
are only 362,800 maximix arrangements to go search through. 

"""

from time import time

def reverse(L, a, b):
    """ In-place reversal indices a through b of list L. """
    while a < b:
        L[a], L[b] = L[b], L[a]
        a += 1
        b -= 1

def insert_in_order(L, x):
    """ Inserts x into ordered list L (first element minimum) of fixed length.
    Uses binary search. """

    if x > L[-1]:
        return

    elif x < L[0]:
        L.insert(0, x)
    else:
        a, b = 0, len(L)-1
        while b - a > 1:
            mid = (b+a)//2
            if L[mid] >= x:
                b = mid
            else:
                a = mid
        L.insert(b, x)
    L.pop()

def list_to_number(L, b):
    """ Turns list for this problem into the arrangement, as a number. """
    n = 0
    for x in L[::-1]:
        n = n*b + (b-x-1)
    return n

def number_to_alpha(n, b):
    """ Turns arrangement as number into alphabetical representation. """
    char_set = 'ABCDEFGHIJK'
    s = ''
    for count in xrange(b):
        digit = n%b
        s = char_set[digit] + s
        n //= b
    return s

def recurse(L, depth, size):

    if depth == size:
        N = list_to_number(L, size)
        insert_in_order(min_list, N)
    else:
        
        reverse(L, 0, depth)
        for i in xrange(1, depth):
            reverse(L, 0, i)
            recurse(L, depth+1, size)
            reverse(L, 0, i)
        reverse(L, 0, depth)

def p336():
    global min_list
    min_list = [float('inf')]*2048
    N = 11
    L = range(N)
    reverse(L, 0, 1)
    recurse(L, 2, N)
    return number_to_alpha(min_list[2010], N)

if __name__ == '__main__':
    time_start = time()
    print(p336())
    print("Time: {0:.3f}".format(time()-time_start))

