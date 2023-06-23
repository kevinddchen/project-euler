# ANSWER 743

"""

Pretty straightforward. Here we deconstructed each roman numeral to its
numerical value, then constructed the minimal roman numeral.

"""

from mathfuncs import read_text

v_dict = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}
r_dict = dict((v, k) for k, v in v_dict.items())


def deconstruct(roman):
    """Take a roman numeral and extract its numerical value."""
    value = 0
    roman = list(roman)
    while len(roman) > 1:
        a = roman.pop(0)
        if (
            (a == "I" and (roman[0] in ("V", "X")))
            or (a == "X" and (roman[0] in ("L", "C")))
            or (a == "C" and (roman[0] in ("D", "M")))
        ):
            b = roman.pop(0)
            value += v_dict[b] - v_dict[a]
        else:
            value += v_dict[a]
    if len(roman) == 1:
        value += v_dict[roman[0]]
    return value


def construct(value):
    """Take a value and returns its roman numeral."""
    string = ""
    digits = [int(x) for x in list(str(value))]
    for i, n in enumerate(digits):
        exp = len(digits) - i - 1
        if exp == 3:
            string += r_dict[1000] * n
        elif n == 4 or n == 9:
            string += r_dict[10**exp] + r_dict[5 * (n // 4) * 10**exp]
        elif n >= 5:
            string += r_dict[5 * 10**exp] + r_dict[10**exp] * (n - 5)
        else:
            string += r_dict[10**exp] * n
    return string


def p89():
    saved_letters = 0
    text = read_text("roman.txt")
    for raw_roman in text.splitlines():
        new_roman = construct(deconstruct(raw_roman))
        saved_letters += len(raw_roman) - len(new_roman)

    return saved_letters
