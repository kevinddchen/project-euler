# ANSWER 168

"""

Nearly identical to Problem 114, but generalized. Now
F(m, n) = 2F(m, n-1) - F(m, n-2) + F(m, n-m-1) where F(m, n) = 1 when n < m and
F(m, m) = 2.

"""

from time import time


def p115():
    L = [2] + [1] * 50
    i = 50
    while L[0] <= 1000000:
        i += 1
        L.insert(0, 2 * L[0] - L[1] + L.pop())
    return i


if __name__ == "__main__":
    time_start = time()
    print(p115())
    print("Time: {0:.3f}".format(time() - time_start))
