# ANSWER CAGBIHEFJDK

"""

The maximix arrangements for n carridges generate the maximix arrangements for
n+1 carriges.  After that, it is pretty much brute force.  Here I use a
depth-first tree search through all maximix arrangements to save space, keeping
track of the smallest 2048 arrangements (be sure to use binary search -- this
was the slowest part of the first program).  Doesn't take long at all, as there
are only 362,800 maximix arrangements to go search through.

"""


def reverse(L, a, b):
    """In-place reversal indices a through b of list L."""
    while a < b:
        L[a], L[b] = L[b], L[a]
        a += 1
        b -= 1


def insert_in_order(x, lst):
    """Inserts x into a list lst, which has been sorted in increasing order, and then pop the largest element."""
    a, b = 0, len(lst)
    while a != b:
        mid = (a + b) // 2
        if lst[mid] > x:
            b = mid
        else:
            a = mid + 1
    lst.insert(a, x)
    lst.pop()


def list_to_number(L, b):
    """Turns list for this problem into the arrangement, as a number."""
    n = 0
    for x in L[::-1]:
        n = n * b + (b - x - 1)
    return n


def number_to_alpha(n, b):
    """Turns arrangement as number into alphabetical representation."""
    char_set = "ABCDEFGHIJK"
    s = ""
    for _ in range(b):
        digit = n % b
        s = char_set[digit] + s
        n //= b
    return s


def recurse(L, depth, size, min_list):

    if depth == size:
        N = list_to_number(L, size)
        insert_in_order(N, min_list)
    else:

        reverse(L, 0, depth)
        for i in range(1, depth):
            reverse(L, 0, i)
            recurse(L, depth + 1, size, min_list)
            reverse(L, 0, i)
        reverse(L, 0, depth)


def p336():
    min_list = [float("inf")] * 2048
    N = 11
    L = list(range(N))
    reverse(L, 0, 1)
    recurse(L, 2, N, min_list)
    return number_to_alpha(min_list[2010], N)
