# ANSWER 1818

"""

Here we present a new method for generating Pythagorean triples. Given a
primitive triple (a, b, c), we can generate three different primitive triples
using the following linear transformations,

    [[-1, 2, 2], [-2, 1, 2], [-2, 2, 3]] @ [a, b, c]
    [[ 1, 2, 2], [ 2, 1, 2], [ 2, 2, 3]] @ [a, b, c]
    [[ 1,-2, 2], [ 2,-1, 2], [ 2,-2, 3]] @ [a, b, c]

Using an initial seed (3, 4, 5) every primitive triple can be generated using
this method.

"""


def possible(a, b):
    """Return number of possible x, y pairs such that x+y = b and a >= x >= y >= 1."""
    return b // 2 - max(b - a, 1) + 1


def generate_triples(t):
    a, b, c = t
    return [
        (-a + 2 * b + 2 * c, -2 * a + b + 2 * c, -2 * a + 2 * b + 3 * c),
        (+a + 2 * b + 2 * c, +2 * a + b + 2 * c, +2 * a + 2 * b + 3 * c),
        (+a - 2 * b + 2 * c, +2 * a - b + 2 * c, +2 * a - 2 * b + 3 * c),
    ]


def p86():
    triple_bank = [(3, 4, 5)]
    triple_list = []

    count = 0
    M = 0
    while count < 1000000:
        M += 1
        remove_list = []
        # generate new triples and add potential triples
        for triple in triple_bank:
            a = max(triple[0], triple[1])
            b = min(triple[0], triple[1])
            if M == b:
                triple_bank.extend(generate_triples(triple))
                if a < 2 * M:
                    triple_list.append((b, a))
                triple_list.append((a, b))
                remove_list.append(triple)

        # add possibilities from previously known triples
        for a, b in triple_list:
            if M % a == 0:
                count += possible(M, b * M // a)

        for triple in remove_list:
            triple_bank.remove(triple)

    return M
