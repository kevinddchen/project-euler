# ANSWER 2178309

"""

Can be solved by hand. See PDF for explanation.

"""


def p301():
    a, b = 2, 3
    for _ in range(28):
        a, b = b, a + b
    return b
