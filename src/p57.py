# ANSWER 153

"""

Given a continued fraction expansion [a_0; a_1, a_2, ...], the convergents can
be calculated by the recurrence relation,

    p_{-1} = 1,     p_0 = a_0,      p_n = a_n p_{n-1} + p_{n-2},
    q_{-1} = 0,     q_0 = 1,        q_n = a_n q_{n-1} + q_{n-2}.

Then the fraction p_n/q_n gives the nth convergent.

"""

from time import time


def continued_fraction_of_sqrt2():
    yield 1
    while True:
        yield 2


def p57():
    C = 0
    G = continued_fraction_of_sqrt2()
    a_0 = next(G)
    a_1 = next(G)
    p = (a_0 * a_1 + 1, a_0)
    q = (a_1, 1)
    for _ in range(1000 - 2):  # starts on the second convergent
        if len(str(p[0])) > len(str(q[0])):
            C += 1
        a = next(G)
        p = (a * p[0] + p[1], p[0])
        q = (a * q[0] + q[1], q[0])
    return C


if __name__ == "__main__":
    time_start = time()
    print(p57())
    print("Time: {0:.3f}".format(time() - time_start))
