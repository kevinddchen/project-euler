# ANSWER 7273

"""

Same method as problem 18. Start from the bottom and work upwards.

"""

from pathlib import Path


def p67():
    fl = Path(__file__).parent / "../files/triangle.txt"
    m = [[int(x) for x in line.split(" ")] for line in fl.read_text().splitlines()]

    for i in range(len(m) - 2, -1, -1):
        for j in range(len(m[i])):
            m[i][j] += max(m[i + 1][j], m[i + 1][j + 1])
    return m[0][0]
