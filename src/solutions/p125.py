# ANSWER 2906969179

from math import isqrt

LIMIT = 10**8


def is_palindrome(n):
    n = str(n)
    for i in range(len(n) // 2):
        if n[i] != n[-i - 1]:
            return False
    return True


def p125():
    LIMIT = 10**8
    L = set()
    for a in range(1, isqrt(LIMIT) + 1):
        S = a * a
        for b in range(a + 1, isqrt(LIMIT) + 1):
            S += b * b
            if S >= LIMIT:
                break
            if is_palindrome(S):
                L.add(S)
    return sum(L)
