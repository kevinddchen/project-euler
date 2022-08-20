# ANSWER 840

from math import gcd, isqrt


def p39():
    # similar to Problem 9.
    # Euclid's formula for generating Pythagorean triples
    # a+b+c = 2km(m+n) <= 1000, so stop m at sqrt(5000)
    ans = [0 for _ in range(1001)]
    for m in range(2, isqrt(500) + 1):
        # m, n opposite parity
        if m % 2 == 0:
            n_start = 1
        else:
            n_start = 2

        for n in range(n_start, m, 2):
            if gcd(m, n) == 1:
                p = 2 * m * (m + n)
                while p <= 1000:
                    ans[p] += 1
                    p += 2 * m * (m + n)
    return max((n, i) for i, n in enumerate(ans))[1]
