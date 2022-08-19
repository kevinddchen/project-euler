# ANSWER 986262

"""

Use a sieve to count number of divisors.

"""


def p179():
    LIMIT = 10**7
    C = 0
    a = [1 for _ in range(LIMIT)]
    for i in range(2, LIMIT):
        for j in range(i, LIMIT, i):
            a[j] += 1
        if a[i] == a[i - 1]:
            C += 1
    return C
