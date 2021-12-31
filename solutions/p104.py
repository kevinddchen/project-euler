#!/usr/bin/python
#ANSWER 329468

"""

First we generate fibonacci numbers, saving only the last 9 digits, until we
reach one that is pandigital. Then we can calculate the first 9 digits for that
fibonacci number using the approximation F_n ~ phi^n / sqrt(5) for large n. To
prevent overflow errors, we manually exponentiate, keeping only the first 9
digits. Then we check it is pandigital.

"""

from time import time

def fib_last_generator():
    """ Generates fibonacci numbers, keeping only last 9 digits. """
    a, b = 0, 1
    while True:
        yield a
        a, b = b, (a+b)%10**9

def fib_first(n):
    """ Calculates first 9 digits of F_n. Uses exponentiation by squaring.  """
    x = (1+5**0.5)/2
    y = 5**-0.5
    while n > 1:
        if n%2 == 0:
            x *= x
            n /= 2
        else:
            y *= x
            x *= x
            n //= 2
        while x*y > 10**9:
            if x > y: x /= 10
            else: y /= 10
    return int(x*y)

def pandigital(string):
    """ Checks if a string has all digits 1-9. """
    for i in range(1, 10):
        if str(i) not in string:
            return False
    return True

def p104():
    for i, last_9 in enumerate(fib_last_generator()):
        if pandigital(str(last_9)) and pandigital(str(fib_first(i))):
                break
    return i

if __name__ == '__main__':
    time_start = time()
    print(p104())
    print("Time: {0:.3f}".format(time()-time_start))
