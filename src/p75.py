# ANSWER 161667

"""

Generate Pythagorean triples, like in Problem 9. The perimeter is 2km(m+n).
Then iterate through all k values under the limit, and use sets to keep track
of unique perimeters.

"""

from math import gcd, isqrt


def p75():
    MAX_L = 1500000

    good = set()
    bad = set()

    for m in range(2, isqrt(MAX_L // 2) + 1):
        # m, n must have opposite parity
        if m % 2 == 0:
            n_start = 1
        else:
            n_start = 2

        for n in range(n_start, m, 2):
            if gcd(m, n) == 1:
                L = 2 * m * (m + n)
                while L <= MAX_L:
                    if L in good:
                        good.remove(L)
                        bad.add(L)
                    elif L not in bad:
                        good.add(L)
                    L += 2 * m * (m + n)

    return len(good)
