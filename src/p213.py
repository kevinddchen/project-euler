# ANSWER 330.721154

"""

The problem can be modeled as a Markov process. If a single flea starts on a
square (i, j), the probability that it ends up at (i', j') is denoted
P_ij(i', j'). The product of 1 - P_ij(i', j') over all i, j gives the
probability that the square (i', j') is unoccupied. Summing this over all i', j'
gives the expected number of unoccupied squares.

"""

from time import time

import numpy as np


def p213():
    n = 30

    # one-jump transition matrix
    T = np.zeros((n, n, n, n))
    for i in range(n):
        for j in range(n):
            neighbors = 4
            if (i == 0) or (i == n - 1):
                neighbors -= 1
            if (j == 0) or (j == n - 1):
                neighbors -= 1

            if i != 0:
                T[i, j, i - 1, j] = 1.0 / neighbors
            if i != n - 1:
                T[i, j, i + 1, j] = 1.0 / neighbors
            if j != 0:
                T[i, j, i, j - 1] = 1.0 / neighbors
            if j != n - 1:
                T[i, j, i, j + 1] = 1.0 / neighbors
    T = T.reshape((n * n, n * n))

    # 50-jump transition matrix
    # calculate P = T^50 by repeated squaring
    iter = 50
    P = np.identity(n * n)
    while iter > 0:
        if iter % 2 == 1:
            P = P @ T
        T = T @ T
        iter >>= 1

    # for each square, calculate probability it is uoccupied
    prob = np.ones(n * n)
    for i in range(n * n):
        state = np.zeros(n * n)
        state[i] = 1

        state = state @ P

        prob = prob * (1 - state)

    # expected value
    ev = np.sum(prob)
    return round(ev, 6)


if __name__ == "__main__":
    time_start = time()
    print(p213())
    print("Time: {0:.3f}".format(time() - time_start))
