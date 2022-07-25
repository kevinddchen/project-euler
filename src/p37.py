# ANSWER 748317

from time import time

from mathfuncs import is_prime


def check_trunc(x):
    x_l, x_r = str(x)[1:], str(x)[:-1]
    while len(x_l) > 0:
        int_l, int_r = int(x_l), int(x_r)
        if int_l < 2 or int_r < 2 or not is_prime(int_l) or not is_prime(int_r):
            return False
        x_l, x_r = x_l[1:], x_r[:-1]
    return True


def p37():
    count = 0
    S = 0
    x = 11
    while count < 11:
        if is_prime(x) and check_trunc(x):
            count += 1
            S += x
        x += 2
    return S


if __name__ == "__main__":
    time_start = time()
    print(p37())
    print("Time: {0:.3f}".format(time() - time_start))
