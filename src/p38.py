# ANSWER 932718654


def check(x):
    """

    Checks if a number can be represented as a concatenation of consecutive
    multiples of a number. Returns the final string if it can, else returns 0.

    """
    string = ""
    i = 1
    while len(string) < 9:
        string += str(x * i)
        i += 1
    if len(string) != 9:
        return False
    for d in range(1, 10):
        if str(d) not in string:
            return False
    return int(string)


def p38():
    # maximum 4 digit numbers as n > 1
    return max(check(x) for x in range(1, 10000))
