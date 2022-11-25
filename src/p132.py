# ANSWER 843296

"""

R(k) = (10^k-1)/9, so if we are checking divisibility of R(k) by some prime p,
(10^k-1)/9 = 0 (mod p) if and only if  10^k = 1 (mod p), for p =/= 3. Therefore
all we need to test is that 10^{10^9} = 1 (mod p). We can simplify a little more
using Fermat's little theorem, which says 10^{p-1} = 1 (mod p). Therefore
it suffices that we check 10^{gcd(10^9, p-1)} = 1 (mod p).

"""

from mathfuncs import is_prime


def p132():
    C, S = 0, 0
    p = 5
    while C < 40:
        p += 2
        if not is_prime(p):
            continue
        if pow(10, pow(10, 9, p - 1), p) == 1:
            C += 1
            S += p
    return S
