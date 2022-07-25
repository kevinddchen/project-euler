# ANSWER 25164150

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time


def p6():
    return sum(x for x in range(101)) ** 2 - sum(x * x for x in range(101))


if __name__ == "__main__":
    time_start = time()
    print(p6())
    print("Time: {0:.3f}".format(time() - time_start))
