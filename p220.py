#!/usr/bin/python
#ANSWER 139776,963904

"""

Iteratively determine what "a" and "b" branch out into at some D_n, then use a
long-division like algorithm to determine the 10**12th step.

"""

from time import time

A_STRING = "aRbFR"
B_STRING = "LFaLb"
A_LIST = [(0, 0, 0, 0)]
B_LIST = [(0, 0, 0, 0)]

def rotate(x, y, d):
    """ Rotate vector (x, y) through (d*pi/2) radians clockwise. """
    for i in xrange(d):
        x, y = y, -x
    return x, y

def effect(x, y, d, n, action):
    """ Apply action to (x, y) in direction d for n steps remaning. """
    if action == 'F':
        x_1, y_1 = rotate(0, 1, d)
        return x + x_1, y + y_1, d, n-1
    elif action == 'L':
        return x, y, (d-1)%4, n
    elif action == 'R':
        return x, y, (d+1)%4, n
    else:
        x_0, y_0, d_1, n_1 = action
        x_1, y_1 = rotate(x_0, y_0, d)
        return x + x_1, y + y_1, (d+d_1)%4, n+n_1

def recurse(x, y, d, n, level, s):
    """ Recurse through path. """
    for char in s:
        if n == 0:
            return "{0},{1}".format(x, y)
        if char == 'a':
            action = A_LIST[level]
            if n + action[-1] > 0:
                x, y, d, n = effect(x, y, d, n, action)
            else:
                return recurse(x, y, d, n, level-1, A_STRING)
        elif char == 'b':
            action = B_LIST[level]
            if n + action[-1] > 0:
                x, y, d, n = effect(x, y, d, n, action)
            else:
                return recurse(x, y, d, n, level-1, B_STRING)
        else:
            x, y, d, n = effect(x, y, d, n, char)
    return False

def p220():
    size = 50
    steps = 10**12

    ## initialize a and b branches
    for i in xrange(size):
        for lst, string in [(A_LIST, A_STRING), (B_LIST, B_STRING)]:
            x, y, d, n = 0, 0, 0, 0
            for char in string:
                if char == 'a':
                    action = A_LIST[i]
                elif char == 'b':
                    action = B_LIST[i]
                else:
                    action = char
                x, y, d, n = effect(x, y, d, n, action)
            lst.append( (x, y, d, n) )

    return recurse(0, 0, 0, steps, size, "Fa")

if __name__ == '__main__':
    time_start = time()
    print(p220())
    print("Time: {0:.3f}".format(time()-time_start))

