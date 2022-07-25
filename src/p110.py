# ANSWER 9350130049860600

"""

From Problem 108, it was observed that in performing the calculation,

    (2a_1 + 1)*(2a_2 + 1)*...*(2a_k + 1)

We were finding the product of k odd numbers that minimally exceeded 2000, that
is to say when we multiplied to a number that exceeded the limit, we stopped.
Then, with the values of a_1...a_k, we calculated the smallest number n using
the first k primes.

Using this approach, the question now changes to a limit of 8000000.

"""

from math import ceil, log, prod
from time import time

from mathfuncs import is_prime


def prime_gen(n):
    x, i = 1, 0
    while i < n:
        x += 1
        if is_prime(x):
            i += 1
            yield x


def calculate_N(coeff, primes):
    """Calculate product of primes from a_1 ... a_k odd numbers"""
    return prod(primes[i] ** ((c - 1) // 2) for i, c in enumerate(coeff))


def min_product_recursive(path, prod, max_factor, primes):
    global LIMIT, MIN

    if prod > LIMIT:

        n = calculate_N(path, primes)
        if n < MIN:
            MIN = n

    else:
        for x in range(3, max_factor + 1, 2):
            if 2**x > MIN:
                break
            path.append(x)
            min_product_recursive(path, prod * x, x, primes)
            path.pop()


LIMIT = 8000000
MIN = 1e99


def p110():
    global MIN
    n_primes = ceil(log(LIMIT, 3))
    primes = list(prime_gen(n_primes))
    MIN = calculate_N([3] * n_primes, primes)
    max_factor = ceil(log(MIN, 2))
    if max_factor % 2 == 0:
        max_factor -= 1
    min_product_recursive([], 1, max_factor, primes)
    return MIN


if __name__ == "__main__":
    time_start = time()
    print(p110())
    print("Time: {0:.3f}".format(time() - time_start))
