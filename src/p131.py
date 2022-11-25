# ANSWER: 173

"""

We claim that n is a perfect cube. Assume for a contradiction that n = x * y^3
where x =/= 1 and is cubefree. As n^3 + n^2 p = n^2(n+p) is a perfect cube, so
x | n+p. But x|n, so x|p and x=p as p is prime. But then n^2(n+p) = 2 p^3 y^6
which is not a perfect cube. Therefore n is a perfect cube, which implies that
n+p is a perfect cube as well. Therefore p is the difference of two perfect
cubes. But if p = k^3 - (k-a)^3 = a(3k^2 - 3ka + a^2), we require a=1 and p is
the difference of two consecutive cubes. What remains is to generate consecutive
cubes and test for primality.

"""

from mathfuncs import is_prime


def p131():
    return sum(1 for k in range(2, 578) if is_prime(3 * k * (k - 1) + 1))
