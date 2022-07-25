# ANSWER 249

from time import time


def is_lychrel(x):
    x += int(str(x)[::-1])
    t = 1
    while t < 50:
        if str(x) == str(x)[::-1]:
            return False
        x += int(str(x)[::-1])
        t += 1
    return True


def p55():
    return sum(1 for x in range(10000) if is_lychrel(x))


if __name__ == "__main__":
    time_start = time()
    print(p55())
    print("Time: {0:.3f}".format(time() - time_start))
