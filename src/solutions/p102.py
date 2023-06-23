# ANSWER 228

"""

We check that the cross-products of the points in order have the same sign.

"""

from pathlib import Path


def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]


def p102():
    count = 0
    fl = Path(__file__).parent / "../files/triangles.txt"
    for line in fl.read_text().splitlines():
        line = line.split(",")
        A = (int(line[0]), int(line[1]))
        B = (int(line[2]), int(line[3]))
        C = (int(line[4]), int(line[5]))
        AB_sign = cross(A, B) >= 0
        BC_sign = cross(B, C) >= 0
        CA_sign = cross(C, A) >= 0
        if AB_sign == BC_sign and BC_sign == CA_sign:
            count += 1
    return count
