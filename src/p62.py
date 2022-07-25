# ANSWER 127035954683

"""

Generate all cubes with n digits, sort each cube in increasing digits, then
search for five cubes with the same digit pattern. If no pattern is found, then
increment n and repeat.

"""

from time import time


def cube_gen(d):
    """generate cubes with specified digits"""
    n = int(10 ** ((d - 1) / 3.0))
    while True:
        x = n * n * n
        if len(str(x)) == d:
            yield x
        elif len(str(x)) > d:
            break
        n += 1


def p62():
    SAME = 5
    d = 1
    while True:
        # create lists of tuples containing (ordered digits, original cube)
        L = [(int("".join(sorted(str(c)))), c) for c in cube_gen(d)]
        L.sort()
        # search for consecutive identical ordered digits
        i, j = 0, 0
        while j < len(L):
            if L[i][0] == L[j][0]:
                j += 1
            else:
                if j - i == SAME:
                    return L[i][1]
                i = j
        d += 1


if __name__ == "__main__":
    time_start = time()
    print(p62())
    print("Time: {0:.3f}".format(time() - time_start))
