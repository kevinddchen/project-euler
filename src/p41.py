# ANSWER 7652413

from itertools import permutations
from time import time

from mathfuncs import is_prime


def largest_prime(digits):
    for perm in permutations(range(digits, 0, -1)):
        p = int("".join(str(x) for x in perm))
        if is_prime(p):
            return p
    return 0


def p41():
    for d in range(9, 0, -1):
        p = largest_prime(d)
        if p != 0:
            return p


if __name__ == "__main__":
    time_start = time()
    print(p41())
    print("Time: {0:.3f}".format(time() - time_start))
