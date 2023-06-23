# ANSWER 282771304

"""

First, note that f(k) = k * g(k) where g(k) is the number of 1s in the binary
representation of k.

Next, let us define S_{ij}(n) = sum_{k=1}^n k^i g(k)^j. We want to find
S_{22}(10^16). However, we can note that S_{22}(n) obeys the following
recurrence relation:

    S_{22}(2n+1) = 8 S_{22}(n) + 8 S_{21}(n) + 4 S_{12}(n) + 8 S_{11}(n)
                   + S_{02}(n) + 2 S_{01}(n) + (2n+1)(2n+3)(n+1)/3

Similar recurrence relations can be derived for the other S_{ij}(2n+1).
In the end, if we define the vector S(n) to be the vector
    S(n) = { S_{22}(n), S_{21}(n), S_{12}(n), S_{11}(n), S_{02}(n), S_{01}(n) }

then the recurrence relation for S(n) can be written as

    S(2n+1) = M @ S(n) + V(n)

where M is a 6x6 matrix and V(n) is a vector that depends on n, defined in the
code below. The only thing remaining is to subtract the appropriate quantities
to calculate S(2n) so that we can calculate S(10^16) in the end.

"""

import numpy as np


def _get_bits(n: int) -> list[int]:
    """Get the bits of n."""
    L = []
    while n > 0:
        L.append(n & 1)
        n >>= 1
    L.reverse()
    return L


"""The matrix M as defined above."""
M = np.array(
    [
        [8, 8, 4, 8, 1, 2],
        [0, 8, 0, 4, 0, 1],
        [0, 0, 4, 4, 1, 2],
        [0, 0, 0, 4, 0, 1],
        [0, 0, 0, 0, 2, 2],
        [0, 0, 0, 0, 0, 2],
    ],
    dtype=np.int64,
)


def V(k: int, mod: int) -> np.ndarray:
    """Return the vector V(i) as defined above."""

    a = ((k + 1) * (2 * k + 1) * (2 * k + 3) // 3) % mod
    b = ((k + 1) * (k + 1)) % mod
    c = (k + 1) % mod
    return np.array([a, a, b, b, c, c], dtype=np.int64)


def last_term(k: int, mod: int) -> np.ndarray:
    """Return the last term in the sums for S(k)."""

    n_bits = sum(_get_bits(k))

    return np.array(
        [
            (k * k * n_bits * n_bits) % mod,
            (k * k * n_bits) % mod,
            (k * n_bits * n_bits) % mod,
            (k * n_bits) % mod,
            (n_bits * n_bits) % mod,
            n_bits,
        ],
        dtype=np.int64,
    )


def p759() -> int:
    n = 10_000_000_000_000_000
    mod = 1_000_000_007

    bits = _get_bits(n)
    bits.pop(0)  # first bit is always 1

    S = np.array([1, 1, 1, 1, 1, 1], dtype=np.int64)
    k = 1  # keeps track of the current value, will equal n at the end

    for bit in bits:
        S = (M @ S + V(k, mod)) % mod
        k = (k << 1) + 1

        if bit == 0:
            S = (S - last_term(k, mod)) % mod
            k -= 1

    return S[0]
