# ANSWER 6857

from time import time


def p3():
    x = 600851475143
    y = 3
    while y * y <= x:
        while x % y == 0:
            x //= y
        y += 2
    return x


if __name__ == "__main__":
    time_start = time()
    print(p3())
    print("Time: {0:.3f}".format(time() - time_start))
