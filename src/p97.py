# ANSWER 8739992577

"""

Just keep track of the last 10 digits

"""


def p97():
    x = 1
    for _ in range(7830457):
        x *= 2
        x %= 10**10
    x = x * 28433 + 1

    return x % 10**10
