# ANSWER 73162890

"""

This problem is best solved by hand. From the key logger we created a graph
that tracked the well-ordering of the characters according to their occurances.
This method is guaranteed to work with non-repeating digits.

"""

from pathlib import Path


def pop_longest_list(d):
    x = max([(len(d[x]), x) for x in d])[1]
    del d[x]
    return x


def p79():
    # Create graph
    dct = {}
    fl = Path(__file__).parent / "../files/keylog.txt"
    for line in fl.read_text().splitlines():
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
