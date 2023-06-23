from typing import NamedTuple


def is_prime(n: int, /) -> bool:
    """
    Checks if input is a prime number. Runs in O(sqrt(n)) time.

    Args:
        n: Integer greater than 1.

    Returns:
        True if n is prime.
    """
    assert n > 1, "n must be greater than 1"
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    a = 3
    while a * a <= n:
        if n % a == 0:
            return False
        a += 2
    return True


def prime_sieve(size: int, /) -> list[bool]:
    """
    Creates a prime sieve, i.e. a list of boolean values where the nth entry,
    for n > 1, is True when n is prime.

    Note: 0 and 1 are not considered prime in the sieve.

    Args:
        size: Positive integer.

    Returns:
        List of boolean values.
    """
    assert size >= 0, "size must be non-negative"

    sieve = [True for _ in range(size)]
    if size > 0:
        sieve[0] = False
    if size > 1:
        sieve[1] = False

    i = 2
    while i * i < size:
        if sieve[i]:
            for j in range(i * i, size, i):  # sieve out all multiples
                sieve[j] = False
        i += 1
    return sieve


class PrimePower(NamedTuple):
    base: int
    exp: int


def prime_factorize(n: int, /) -> list[PrimePower]:
    """
    Prime factorize a positive integer, i.e. if n = p1^a1 * p2^a2 * ... * pk^ak
    then return the list of {p, a} pairs. The p's are given in ascending order.
    If n = 1, returns the empty vector. Runs in O(sqrt(n)) time.

    Args:
        n: Positive integer

    Return:
        List of {p_i, a_i}.
    """
    assert n > 1, "n must be greater than 1"

    prime_factors: list[PrimePower] = list()

    base = 2
    while base * base <= n:
        exp = 0
        while n % base == 0:
            n //= base
            exp += 1
        if exp != 0:
            prime_factors.append(PrimePower(base=base, exp=exp))
        base += 1
    if n > 1:
        prime_factors.append(PrimePower(base=n, exp=1))  # remainder of x is prime

    return prime_factors


# def extended_gcd(a, b):
#     '''Returns a tuple (s, t, r) containing the Bezout coefficients and gcd,
#     i.e. a*s + b*t = r. '''
#     s, old_s = 0, 1
#     t, old_t = 1, 0
#     r, old_r = b, a
#     while r != 0:
#         q = old_r // r
#         old_r, r = r, old_r - q*r
#         old_s, s = s, old_s - q*s
#         old_t, t = t, old_t - q*t
#     return (old_s, old_t, old_r)

# sum of proper divisors: p21
# iterate through divisors: p44
# totient sieve: p69
# integer partition: p76
# totient: p188
# binary search: p187
