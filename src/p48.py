# ANSWER 9110846700

from time import time


def p48():
    return sum((pow(x, x, 10**10) for x in range(1, 1001))) % 10**10


if __name__ == "__main__":
    time_start = time()
    print(p48())
    print("Time: {0:.3f}".format(time() - time_start))
