# ANSWER 3010983666182123972

"""

s(n) is the smallest integer such that 2^{s(n)} = 1 mod (n-1). So we find all
values of n such that 2^60 = 1 mod (n-1), and 2^d =/= 1 mod (n-1) for all
divisors d of 60.

"""

from time import time

from p44 import divisors


def check(d, bad):
    for b in bad:
        if b % d == 0:
            return False
    return True


def p622():

    divisors_of_60 = [2, 3, 4, 5, 6, 10, 12, 15, 20, 30]
    bad = [pow(2, d) - 1 for d in divisors_of_60]
    S = 0

    N = pow(2, 60) - 1
    for d in divisors(N):
        if check(d, bad):
            S = S + (d + 1)
    return S


if __name__ == "__main__":
    time_start = time()
    print(p622())
    print("Time: {0:.3f}".format(time() - time_start))
