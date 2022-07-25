# ANSWER 2129970655314432

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time


def p148():

    # triangle numbers T_n
    Tn = [n * (n + 1) // 2 for n in range(7)]
    # factorization of 10^9 in base 7, starting from 7^0 digit
    arr = [6, 1, 6, 0, 0, 6, 1, 3, 5, 3, 3]

    total = 0
    for power, digit in enumerate(arr):
        total = Tn[digit] * (28**power) + (digit + 1) * total

    return total


if __name__ == "__main__":
    time_start = time()
    print(p148())
    print("Time: {0:.3f}".format(time() - time_start))
