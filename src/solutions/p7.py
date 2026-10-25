from mathfuncs import is_prime

ANSWER = 104743


def p7():
    n, i = 1, 1
    while i < 10001:
        n += 2
        if is_prime(n):
            i += 1
    return n
