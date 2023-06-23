# ANSWER 4075

from math import comb


def p53():
    C = 0
    for n in range(1, 101):
        # using symmetry C(n, r) = C(n, n-r)
        # skip C(n, 0)=1 and C(n, 1)=n
        for r in range(2, n // 2 + 1):
            if comb(n, r) > 1000000:
                C += 1 if r * 2 == n else 2
    return C
