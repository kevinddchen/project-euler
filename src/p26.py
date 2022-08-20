# ANSWER 983

"""

If n is not divisible by 2 or 5, then 1/n will have a repeating decimal
representation with periodicity equal to the order of 10 modulo n. This can be
checked using long-division.

"""


def order(x, n):
    prod, count = x, 1
    while prod != 1:
        prod = prod * x % n
        count += 1
    return count


def p26():
    return max((order(10, n), n) for n in range(2, 1000) if (n % 2) * (n % 5) != 0)[1]
