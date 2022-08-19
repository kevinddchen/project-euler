# ANSWER 872187


def p36():
    # only odd numbers can be palindrones in binary
    return sum(x for x in range(1, 1000000, 2) if str(x) == str(x)[::-1] and bin(x)[2:] == bin(x)[:1:-1])
