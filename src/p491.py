# ANSWER 194505988824000

"""

Here we use the fact that a number is divisible by 11 iff the alternative sum
of its digits (i.e. 123 -> 1 - 2 + 3) is a multiple of 11. So given our digits,
we break them into two subsets of 10 digits each. If the sum of one of the
subsets is A, then the sum of the other is 90-A. Then,
    A - (90-A) = 11*n.
The only possibilities are A = 23, 34, 45, 46, 56, and 67. So we want to count
the number of subsets of our digits which total up to A. Then to get the
answer, we multiply by (10!)^2 for the number of permutations amongst each
subset, and divide by 2^10 to account for the double-counting as some digits
are repeated. We also have to modify our counting slightly to avoid leading
zeros, but this is the outline of the code.

"""


def foo(lst, target_n, target_tot, index=0, n=0, tot=0, L=[]):

    """Iterates through the number of ways to pick [target_n] elements
    from [lst] which sum up to [target_tot]."""

    if tot == target_tot and n == target_n:
        yield L
    elif (index < len(lst)) and (tot <= target_tot) and (n < target_n):
        L.append(lst[index])
        for x in foo(lst, target_n, target_tot, index + 1, n + 1, tot + lst[index], L):
            yield x
        L.pop()
        for x in foo(lst, target_n, target_tot, index + 1, n, tot, L):
            yield x


def p491():
    digits = list(range(10)) * 2
    count = 0

    for x in [23, 34, 45, 56, 67]:
        for L in foo(digits, 10, x):
            count += 10 - L.count(0)
    return count * (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10) ** 2 // (2**10) // 10
