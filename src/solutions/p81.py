# ANSWER 427337

"""

Starting from the top-left and traversing to the bottom-right, we go
through each cell and replace its value with the lowest sum to reach that cell.

"""

from mathfuncs import read_text


def p81():
    # get matrix
    M = []
    text = read_text("matrix.txt")
    for line in text.splitlines():
        M.append([int(x) for x in line.split(",")])

    # find least-sum path
    dim = len(M)
    for x in range(1, 2 * dim):
        i = x
        j = 0
        while i >= 0 and j < dim:
            if i < dim:
                lst = []
                if i > 0:
                    lst.append(M[i - 1][j])
                if j > 0:
                    lst.append(M[i][j - 1])
                M[i][j] += min(lst)
            i -= 1
            j += 1

    return M[-1][-1]
