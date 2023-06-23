# ANSWER 162

from mathfuncs import read_text


def convert_to_int(word):
    """Converts a word into an integer."""
    return sum(ord(letter) - ord("A") + 1 for letter in word.strip('"'))


def is_triangle(x):
    n = round((2 * x + 0.25) ** 0.5 - 0.5)
    return x == n * (n + 1) // 2


def p42():
    text = read_text("words.txt")
    lst = [convert_to_int(word) for word in text.split(",")]
    return sum(1 for x in lst if is_triangle(x))
