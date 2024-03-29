# ANSWER 73682

"""

Recursive tree search

"""

coins = [100, 50, 20, 10, 5, 2]


def count(v, i):
    """Returns number of ways to arrange [v] pence using coins in the list
    [coins] with index [i] and greater."""
    if v < 0:
        return 0
    if v <= 1:
        return 1
    return 1 + sum(count(v - coins[j], j) for j in range(i, len(coins)))


def p31():
    return count(200, 0) + 1  # +1 for the 2 pound coin
