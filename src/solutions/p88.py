# ANSWER 7587457

"""

Here we took every combination of integers, 2x2, 2x3, 2x4, ... 3x3, 3x4, ...
2x2x2, 2x2x3, ... 2x2x2x2, ... and computed the difference between their
product and their sum, eg. 3x4 - (3+4). This would be the number of place
holder 1's to use. Then for the number of total integers we used, we stored
that value in a dictionary for all k values, keeping the lowest value. The
key is to know how to traverse the tree of all possible integer combinations,
and knowing when to stop incrementing and search the next branch over.

"""

from math import prod


def recurse(i, prev_list, k_dict):
    """Recursive tree-search for i non-unity elements."""
    N = prod(prev_list)
    S = sum(prev_list)
    # have i integers
    if len(prev_list) == i:
        k = N - S + len(prev_list)
        if k not in k_dict:
            k_dict[k] = N
        elif k_dict[k] > N:
            k_dict[k] = N
    # need more integers
    else:
        i_r = i - len(prev_list)  # remaining i
        if len(prev_list) == 0:
            x = 2
        else:
            x = prev_list[-1]
        while N * (x**i_r) - (S + x * i_r) <= (KMAX - (len(prev_list) + 1)):
            prev_list.append(x)
            recurse(i, prev_list, k_dict)
            prev_list.pop()
            x += 1


KMAX = 12000


def p88():
    k_dict = {}
    n = 2
    while 2**n - 2 * n <= KMAX:
        recurse(n, [], k_dict)
        n += 1

    return sum(set(k_dict[x] for x in k_dict))
