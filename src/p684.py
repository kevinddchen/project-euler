# ANSWER 922058210

"""

Note that

    s(9i+j) = (j+1) 10^i - 1 ,  for 0 <= j <= 9

and so

    S(9n+m) = (6 + m(m+3)/2) 10^n - (9n+m) - 6 ,    for 0 <= m <= 9

Then we just add up all the S(N) calls, using Fermat's Little theorem to speed
up calculation of exponents (the number 1000000007 given is a prime).

"""


def next_fib(f1, f2):
    f = list(map(lambda x, y: x + y, f1, f2))
    if f[1] >= 9:
        f[1] = f[1] - 9
        f[0] = f[0] + 1
    return f2, f


def S(n, m, P):
    exp = n % (P - 1)
    return (6 + (m * (m + 3)) // 2) * pow(10, exp, P) - (9 * n + m) - 6


def p684():

    P = 1000000007
    tot = 0

    f1 = [0, 0]
    f2 = [0, 1]
    for _ in range(2, 91):
        f1, f2 = next_fib(f1, f2)
        tot = (tot + S(f2[0], f2[1], P)) % P

    return tot
