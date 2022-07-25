# ANSWER 16475640049

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time


def p114():
    L = [2, 1, 1, 1]
    for _ in range(50 - 3):
        L.insert(0, 2 * L[0] - L[1] + L.pop())
    return L[0]


if __name__ == "__main__":
    time_start = time()
    print(p114())
    print("Time: {0:.3f}".format(time() - time_start))
