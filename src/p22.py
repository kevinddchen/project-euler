# ANSWER 871198282

from pathlib import Path
from time import time


def score(name):
    """Returns score of the name"""
    return sum(ord(letter) - ord("A") + 1 for letter in name)


def p22():
    fl = Path(__file__).parent / "../files/names.txt"
    lst = [x.strip('"') for x in fl.read_text().split(",")]
    return sum(score(name) * (i + 1) for i, name in enumerate(sorted(lst)))


if __name__ == "__main__":
    time_start = time()
    print(p22())
    print("Time: {0:.3f}".format(time() - time_start))
