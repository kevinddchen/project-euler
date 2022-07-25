# ANSWER 260324

"""

From left to right, go through each cell in a column and replace its value
with the lowest sum to reach that cell.

"""

from pathlib import Path
from time import time


def p82():
    # get matrix
    M = []
    fl = Path(__file__).parent / "../files/matrix.txt"
    for line in fl.read_text().splitlines():
        M.append([int(x) for x in line.split(",")])

    # find least-sum path
    dim = len(M)
    for j in range(1, dim):
        update = []
        for i in range(dim):
            lst = []
            for i_seek in range(dim):
                x = M[i_seek][j - 1]
                if i_seek < i:
                    x += sum(M[h][j] for h in range(i_seek, i))
                else:
                    x += sum(M[h][j] for h in range(i + 1, i_seek + 1))
                lst.append(x)
            update.append(min(lst))
        for i, x in enumerate(update):
            M[i][j] += x

    return min(row[-1] for row in M)


if __name__ == "__main__":
    time_start = time()
    print(p82())
    print("Time: {0:.3f}".format(time() - time_start))
