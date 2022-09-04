# ANSWER 1582

"""

We generate a tree of all addition chains, and traverse breadth first.

"""


def p122():
    LIMIT = 200
    L = [[1]]
    mem = [0] * (LIMIT + 1)

    # keep generating layers
    depth = 0
    while True:
        depth += 1
        new_L = []
        for lst in L:
            for x in lst:
                tot = lst[0] + x

                if tot <= LIMIT:
                    if mem[tot] == 0:
                        mem[tot] = depth
                    new_L.append([tot] + lst)

        L = new_L

        # fill zeros if possible
        zeros = 0
        for i in range(LIMIT - 1, 1, -1):
            if mem[i] == 0:
                if mem[i - 1] != 0:
                    mem[i] = mem[i - 1] + 1
                else:
                    zeros += 1

        if zeros == 0:
            break

    return sum(mem)
