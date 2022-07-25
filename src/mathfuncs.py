from __future__ import annotations

from typing import Iterable


def is_prime(x: int) -> bool:
    """Checks if input is a prime number. Runs in O(sqrt(x)) time.

    Args:
        x: Integer greater than or equal to 2.

    Returns:
        True if x is prime.
    """
    if x == 2:
        return True
    if x % 2 == 0:
        return False
    y = 3
    while y * y <= x:
        if x % y == 0:
            return False
        y += 2
    return True


class PrimeSieve:
    """Sieve of Eratosthenes; generates all primes up to (but not including) N.
    The list of booleans itself can be accessed via the `.sieve` attribute.

    Args:
        N: Integer greater than or equal to 2.
    """

    def __init__(self, N: int) -> None:
        self.N = N
        self.sieve = [True for _ in range(N)]
        self.sieve[0] = False
        self.sieve[1] = False

    def __iter__(self) -> Iterable[int]:
        for n, isprime in enumerate(self.sieve):
            if isprime:
                for y in range(n * n, self.N, n):  # sieve out all multiples
                    self.sieve[y] = False
                yield n


def prime_factorize(x: int) -> Iterable[tuple[int, int]]:
    """Find prime factorization of x = p_1^(a_1) * p_2^(a_2) * ... * p_k^(a_k).
    Returns tuples (p_i, a_i) for each prime p_i in ascending order. Runs in
    O(sqrt(x)) time.

    Args:
        x: Integer greater than or equal to 2.

    Return:
        List of tuples (p_i, a_i).
    """

    def divide_out(x: int, p: int) -> tuple[int, int]:
        """Divide out p from x as many times as possible. In other words, finds
        the largest value i such that x = y * p^i (where every variable is a
        positive integer) and returns the tuple (y, i)."""
        i = 0
        while x % p == 0:
            i += 1
            x //= p
        return x, i

    x, i = divide_out(x, 2)  # divide out multiples of 2
    if i != 0:
        yield 2, i
    y = 3
    while y * y <= x:
        x, i = divide_out(x, y)  # divide out multiples of 2
        if i != 0:
            yield y, i
        y += 2
    if x != 1:
        yield x, 1  # remainder of x is prime


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
