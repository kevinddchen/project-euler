# ANSWER 45228

from time import time


def count_digits(a, b, c):
    """Returns total number of digits in a, b, and c."""
    return len(str(a)) + len(str(b)) + len(str(c))


def check_pandigital(a, b, c):
    """Check if a, b, and c use every digit 1-9 exactly once."""
    digits = str(a) + str(b) + str(c)
    if len(digits) != 9:
        return False
    for d in range(1, 10):
        if str(d) not in digits:
            return False
    return True


def p32():
    s = set()

    # WLOG, a < b
    a = 2
    b = 3

    while count_digits(a, b, a * b) < 10:
        while count_digits(a, b, a * b) < 10:
            if check_pandigital(a, b, a * b):
                s.add(a * b)
            b += 1
        a += 1
        b = a + 1

    return sum(s)


if __name__ == "__main__":
    time_start = time()
    print(p32())
    print("Time: {0:.3f}".format(time() - time_start))
