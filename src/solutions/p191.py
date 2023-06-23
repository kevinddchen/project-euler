# ANSWER 1918080160


def add_dict(d, L, i):
    """For each element x in L add i to dct[x]."""
    for x in L:
        if x in d:
            d[x] += i
        else:
            d[x] = i


def get_next(s):
    """Generate next possible strings."""
    yield s[0] + s[2] + "O"  # on time
    if s[1:] != "AA":
        yield s[0] + s[2] + "A"  # absent
    if s[0] != "L":
        yield "L" + s[2] + "L"  # late


def p191():
    # format is string of three characters. The first remembers if the string ever
    # contains a late, and the last two remembers the last two day history.
    dct = {"XXX": 1}
    for _ in range(30):
        new_dct = {}
        for s in dct:
            add_dict(new_dct, get_next(s), dct[s])
        dct = new_dct
    return sum(dct[s] for s in dct)
