# ANSWER 180180

"""

n < x, y so let x = n+a and y = n+b. Then with some algebra we can show that

    1/n = 1/(n+a) + 1/(n+b)  -->  n^2 = ab

Therefore the number of solutions is the number of ways to represent n^2 as the
product of two numbers, or half its number of divisors. This is fast to
calculate, as mentioned in Problem 12.

"""

from .mathfuncs import prime_factorize


def p108():
    n = 4
    while True:
        # count number of diviors of n^2
        n_sols = 1
        for pf in prime_factorize(n):
            n_sols *= 2 * pf.exp + 1
        n_unique_sols = (n_sols + 1) // 2  # +1 as n*n is not over-counted
        if n_unique_sols > 1000:
            return n
        n += 1
