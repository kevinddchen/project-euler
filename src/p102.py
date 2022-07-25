# ANSWER 228

"""

We check that the cross-products of the points in order have the same sign.

"""

from time import time


def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]


def p102():
    count = 0
    with open("files/triangles.txt", "r") as fl:
        for line in fl.readlines():
            line = line[:-1].split(",")
            A = (int(line[0]), int(line[1]))
            B = (int(line[2]), int(line[3]))
            C = (int(line[4]), int(line[5]))
            AB_sign = cross(A, B) >= 0
            BC_sign = cross(B, C) >= 0
            CA_sign = cross(C, A) >= 0
            if AB_sign == BC_sign and BC_sign == CA_sign:
                count += 1
    return count


if __name__ == "__main__":
    time_start = time()
    print(p102())
    print("Time: {0:.3f}".format(time() - time_start))
