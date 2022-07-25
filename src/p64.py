# ANSWER 1322

"""

The continued fraction expansion for an irrational square root sqrt(n) is a
repeating non-terminating sequence [a_0; a_1, a_2, ..., a_p = a_1]. The
coeffcients a_n can be calculated using the recurrence relation,

    m_0 = 0,                m_{n+1} = d_n * a_n - m_n,
    d_0 = 1,                d_{n+1} = (n - m_{n+1}^2) / (d_n),
    a_0 = floor(sqrt(n)),   a_{n+1} = floor( (sqrt(n) + m_{n+1}) / d_{n+1} ).

Then once a_n = 2a_0, one period has passed.

"""

from math import isqrt
from time import time


def continued_fraction_of_sqrt(n):
    # also used in Problem 66 and 192
    m, d = 0, 1
    while True:
        a = int((n**0.5 + m) / d)
        yield a
        m = d * a - m
        d = (n - m * m) // d


def p64():
    C = 0
    for n in range(10001):
        a_0 = isqrt(n)
        if n == a_0 * a_0:  # n is a perfect square
            continue

        for i, a in enumerate(continued_fraction_of_sqrt(n)):
            if a == 2 * a_0:
                break

        if i % 2 == 1:
            C += 1
    return C


if __name__ == "__main__":
    time_start = time()
    print(p64())
    print("Time: {0:.3f}".format(time() - time_start))
