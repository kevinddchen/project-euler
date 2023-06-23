# ANSWER 73162890

"""

This problem is best solved by hand. From the key logger we created a graph
that tracked the well-ordering of the characters according to their occurances.
This method is guaranteed to work with non-repeating digits.

"""

from mathfuncs import read_text


def pop_longest_list(d):
    x = max([(len(d[x]), x) for x in d])[1]
    del d[x]
    return x


def p79():
    # Create graph
    dct = {}
    text = read_text("keylog.txt")
    for line in text.splitlines():
        a, b, c = [int(x) for x in line.strip("\n")]
        for x in a, b, c:
            if x not in dct:
                dct[x] = set()
        dct[a].add(b)
        dct[a].add(c)
        dct[b].add(c)

    # Figure out well-ordering
    s = ""
    while len(dct) > 0:
        s += str(pop_longest_list(dct))
    return s
