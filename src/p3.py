# ANSWER 6857


def p3():
    x = 600851475143
    y = 3
    while y * y <= x:
        while x % y == 0:
            x //= y
        y += 2
    return x
