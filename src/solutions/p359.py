# ANSWER 40632119

"""

If we make a large grid of P(f, r) values, we can note three properties:

1.  P(f, 1) follows the following pattern: 1, 2, 4, 8, 12, 18, 24, 32, 40, ...
    which, excluding the first term, equals (f * f) // 2.

2.  P(f, 1) + P(f, 2) follows the following pattern: 2^2, 3^2, 3^2, 5^2, 5^2,
    7^2, 7^2, ... which, excluding the first term, equals (f // 2) * 2 + 1.

3.  If P(f, r) + P(f, r+1) = n^2, then P(f, r+1) + P(f, r+2) = (n + 1)^2, i.e.
    we iterate over increasing perfect squares with increasing r.

With these two observations, we can compute P(f, r) in constant time. We then
are able to exploit Python's arbitrarily large integers to make handling large
integers easy.

"""


def P(f: int, r: int) -> int:
    """Compute P(f, r)."""

    # a = P(f, 1)
    # this follows from observation (1)
    a = (f * f) // 2 if f > 1 else 1

    # s = sqrt(P(f, 1) + P(f, 2))
    # this follows from observation (2)
    s = (f // 2) * 2 + 1 if f > 1 else 2

    # b = P(f, r)
    # since we know P(f, 1), we can use observation (3) to arrive at a formula
    # for P(f, r). This is not too difficult to do by hand.
    if r % 2 == 1:  # r is odd
        b = (r - 1) * s + a
    else:  # r is even
        b = (r - 2) * s + s * s - a
    b += ((r - 1) * (r - 2)) // 2

    return b


def p359() -> int:
    total = 0

    # can iterate over all f, r using the known prime factorization:
    # 71328803586048 = 2^27 * 3^12
    for exp_2 in range(27 + 1):
        for exp_3 in range(12 + 1):
            f = 2**exp_2 * 3**exp_3
            r = 71328803586048 // f

            total += P(f, r)

    return total % 10**8
