# ANSWER 871198282

from mathfuncs import read_text


def score(name):
    """Returns score of the name"""
    return sum(ord(letter) - ord("A") + 1 for letter in name)


def p22():
    text = read_text("names.txt")
    lst = [x.strip('"') for x in text.split(",")]
    return sum(score(name) * (i + 1) for i, name in enumerate(sorted(lst)))
