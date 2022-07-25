# ANSWER 209566

"""

With a lamina of length x and thinkness y (where 0 < y < x/2), the number of
tiles used is x^2 - (x-2y)^2 = 4y(x-y).

"""

from time import time


def p174():
    LIMIT = 10**6
    dct = {}
    for x in range(3, LIMIT // 4 + 2):
        for y in range(1, (x + 1) // 2):
            t = 4 * y * (x - y)
            if t > LIMIT:
                break
            if t in dct:
                dct[t] += 1
            else:
                dct[t] = 1

    L = [0] * 11
    for t in dct:
        if dct[t] <= 10:
            L[dct[t]] += 1
    return sum(L)


if __name__ == "__main__":
    time_start = time()
    print(p174())
    print("Time: {0:.3f}".format(time() - time_start))
