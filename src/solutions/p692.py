# ANSWER 842043391019219959

"""

If we make a table for the first few values of H(k), we can note that H(k) =
the smallest term in the Zeckendorf representation of k. This has a couple
noteworthy consequences:

 -  H(F_n) = F_n, where F_n is the nth Fibonacci number
 -  H(F_n + i) = H(n), where F_n < F_n + i < F_{n+1}

This allows us to derive a useful recurrence relation for G(n):

    G(F_{n+1}) = G(F_n) + H(F_n + 1) + H(F_n + 2) + ... + H(F_{n+1} - 1) + H(F_{n+1})
               = G(F_n) + H(1) + H(2) + ... + H(F_{n+1} - F_n - 1) + F_{n+1}
               = G(F_n) + G(F_{n-1}) - H(F_{n+1} - F_n) + F_{n+1}
               = G(F_n) + G(F_{n-1}) - F_{n-1} + F_{n+1}
               = G(F_n) + G(F_{n-1}) + F_n

Note that the answer is G(F_80).

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
