# ANSWER 510510

"""

Can be solved by hand. See PDF for explanation.

Below, we use a sieve to generate totient values.

"""


def totient_sieve(limit):
    # sieve that generates totient values.
    # also used in Problem 72
    a = [i for i in range(limit)]
    for i, tot in enumerate(a):
        if i < 2:
            continue
        if i == tot:  # is prime
            tot -= 1
            for j in range(2 * i, limit, i):  # i divides j
                a[j] = a[j] * (i - 1) // i
        yield i, tot


def p69():
    M = (6, 2)  # (n, tot(n))
    for n, tot in totient_sieve(1_000_001):
        if n * M[1] > tot * M[0]:
            M = (n, tot)
    return M[0]
