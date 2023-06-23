# ANSWER 842043391019219959

"""

We can make a table to find out that H(k) = k if k is a Fibonacci number, and
in general H(k) = the smallest term in the Zeckendorf representation of k. Then
G(n) satisfies the recursion

    G(F_{n+1}) = G(F_n) + G(F_{n-1}) + F_n

where F_n is the nth Fibonacci number. Note that the big number given is F_80.

"""


def fib_gen():
    """Generates Fibonacci numbers 1, 1, 2, 3, ..."""
    a, b = 0, 1
    while True:
        yield b
        a, b = b, a + b


def p692():
    N = 80
    F = fib_gen()
    a, b = 1, -1  # a = G(F1) and b = G(F0)
    for _ in range(N - 1):
        a, b = a + b + next(F), a

    return a
