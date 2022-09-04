# ANSWER 2544559

"""

We can write n = y(4a-y) as a product of two positive factors, and y>a. Go
through all y and a, keeping track of how many times we can form each n.

"""


def p136():
    size = 50000000
    # keep track of n's
    arr = [0 for _ in range(size)]

    for y in range(1, size):
        a = y // 4 + 1
        n = y * (4 * a - y)
        while y > a and n < size:
            arr[n] = arr[n] + 1
            a += 1
            n = y * (4 * a - y)
    return arr.count(1)
