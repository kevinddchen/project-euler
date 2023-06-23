# ANSWER 38182

"""

Can be solved rather directly. Things for certain:
1) Last dart must be {D1, D2, ... D20, D25}. Thus only focus on first two darts
2) First two darts can be expressed as partition of their total.
i.e. 6 = 6 + 0
       = 5 + 1
       = 4 + 2
       = 3 + 3
3) Each of these darts can be expressed in a number of ways.

"""


def oneDartPossibilities(score):
    """Counts ways one score can be reached by one dart"""

    count = 0
    if score == 0:
        count += 1
    else:
        if score <= 20 or score == 25:
            count += 1
        if score % 2 == 0 and (score <= 40 or score == 50):
            count += 1
        if score % 3 == 0 and score <= 60:
            count += 1

    return count


def twoDartPossibilities(score):
    """Counts ways one score can be reached by two darts"""

    count = 0
    for a in range(min(score // 2, 60) + 1):
        b = score - a
        possA = oneDartPossibilities(a)
        possB = oneDartPossibilities(b)
        count += possA * possB
        if a == b:  # adjustments for same dart
            if possA == 2:
                count -= 1
            elif possA == 3:
                count -= 3

    return count


def checkout(score):
    """Counts number of ways to checkout with given score"""

    count = 0
    lastDart = list(range(2, min(score, 40) + 1, 2))
    if score >= 50:
        lastDart.append(50)
    for i in lastDart:
        count += twoDartPossibilities(score - i)
    return count


def p109():
    count = 0
    for i in range(2, 100):
        n = checkout(i)
        count += n
    return count
