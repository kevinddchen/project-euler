# ANSWER 7526965179680

"""

Kummer's theorem on binomial coefficients states that given integers n >= m
>= 0 and a prime p that the maximum integer k such that p^k divides (n choose m)
is equal to the number of carries when m is added to n-m in base p.

"""

from mathfuncs import prime_sieve


def choose_greatest_power(m, n, p):
    """Gives greatest integer c for prime p such that p^c divides choose(m, n)."""

    a = max(m - n, n)
    b = min(m - n, n)
    carries = 0
    i = 0
    prev = 0
    while p**i <= a:
        a_digit = (a // p**i) % p
        b_digit = (b // p**i) % p
        if prev + a_digit + b_digit >= p:
            carries += 1
            prev = 1
        else:
            prev = 0
        i += 1
    return carries


def p231():
    m, n = 2 * 10**7, 5 * 10**6
    s = 0
    for p, is_prime in enumerate(prime_sieve(m)):
        if is_prime:
            s += choose_greatest_power(m, n, p) * p
    return s
