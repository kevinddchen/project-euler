#!/usr/bin/python
#ANSWER 178653872807

"""

The function f(n) is equivalent to the number of ways of expressing n as a
binary string, but also permitting the usage of the digit 2. For instance, f(10)
= f(1010_2) = {1010, 210, 1002, 202, 122} and f(11) = f(1011_2) = {1011, 211}.
We can establish two properties of the function f(n):

    f(2n) = f(n) + f(n-1),      f(2n+1) = f(n).

 > if n is even (i.e. n = 2k) its binary string ends with a 0. Then its binary
string representations are those of k with a 0 digit appended at the end and
those of k-1 with a 2 digit appended. For instance, f(10) = f(1010_2) = {1010,
210, 1002, 202, 122} = {101, 21}0 + {100, 20, 12}2 = f(101_2) + f(100_2) = f(5)
+ f(4). 

 > if n is odd (i.e. n = 2k+1) its binary string ends with a 1. Then its binary
string representations are those of k with a 1 digit appended. For instance,
f(11) = f(1011_2) = {1011, 211} = {101, 21}1 = f(5). 

With this, we can recursively find f(n) for all n.

"""

from time import time
from functools import cache

@cache
def f(n):
    """ As defined in the problem. """
    if n == 0:
        return 1
    elif n % 2 == 0:
        return f(n // 2) + f(n // 2 - 1)
    else:
        return f(n // 2)

def p169():
    return f(10**25)

if __name__ == '__main__':
    time_start = time()
    print(p169())
    print("Time: {0:.3f}".format(time()-time_start))

