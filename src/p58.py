# ANSWER 26241

"""

For side length n, there are 2n-1 numbers on the diagonals. The numbers at the
corners are n^2 - i(n-1) for i = 0, 1, 2, 3.

"""

from time import time

from .mathfuncs import is_prime


def p58():
    n = 3
    n_primes = 3

    while 10 * n_primes > 2 * n - 1:
        n += 2
        for i in range(1, 4):
            if is_prime((n * n - i * (n - 1))):
                n_primes += 1

    return n


if __name__ == "__main__":
    time_start = time()
    print(p58())
    print("Time: {0:.3f}".format(time() - time_start))
