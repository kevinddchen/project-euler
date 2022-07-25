# ANSWER 354

"""

This question can be solved using a lot of tedious geometry. Given two points, A
and B, we can draw a vector of approach, v, from A to B. At B, we get the normal
vector to the ellipse, which we can then decompse v into parallel and
perpendicular components with respect to n. The vector of reflection is w = v -
2*v_par.  Then B + tw satisfies the equation 4x^2 + y^2 = 100 for some t. This
gives a quadratic equation in t which we can solve, and we take the non-zero
solution. This gives the next point of reflection, C.

"""

from time import time

import numpy as np


def normal_at(A):
    # return a vector normal to the ellipse at A.
    return np.array([4 * A[0], A[1]])


def next_point(A, B):
    v = B - A
    n = normal_at(B)
    v_par = n * v.dot(n) / n.dot(n)
    w = v - 2 * v_par
    t = 2 * v.dot(n) / (4 * w[0] ** 2 + w[1] ** 2)
    return B + t * w


def p144():
    A = np.array([0, 10.1])
    B = np.array([1.4, -9.6])
    count = 0
    while not (-0.01 < B[0] and B[0] < 0.01 and B[1] > 0):
        A, B = B, next_point(A, B)
        count += 1
    return count


if __name__ == "__main__":
    time_start = time()
    print(p144())
    print("Time: {0:.3f}".format(time() - time_start))
