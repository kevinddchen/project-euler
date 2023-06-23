# ANSWER 248155780267521

"""

Generate a^b and check digital sum is equal to a. For traversing the tree, it
is important to always start with the smallest magnitude of a^b, and when
adding new bases, do not start at 2 but at the smallest b such that a^b has at
least ceil(b/9) digits. For example:

2^2 -> 3^2 -> ... -> 27^2 -> 28^3 -> ...
 |      |              |       |
 V      V              V       V
2^3    3^3
 |      |
 V      V

"""

from math import ceil


def p119():
    L = [(2, 2, 2, True)]
    i = 0
    while i < 30:
        L.sort()
        n, base, exp, first = L.pop(0)

        # generate next numbers
        L.append((n * base, base, exp + 1, False))
        if first:
            (
                n_0,
                base_0,
                exp_0,
            ) = (
                (base + 1) ** 2,
                base + 1,
                2,
            )
            while len(str(n_0)) < ceil(base_0 / 9.0):
                exp_0 += 1
                n_0 *= base_0
            L.append((n_0, base_0, exp_0, True))

        # check
        if n < 10:
            continue
        if sum(int(c) for c in str(n)) == base:
            i += 1

    return n
