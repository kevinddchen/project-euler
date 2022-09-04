# ANSWER 101524

"""

We can model the monopoly board as a Markov chain. Then multiply the matrix over
and over on any vector to get the steady state.

"""

import numpy as np


def roll(tile, prob_vec, n_rolls=0, end_turn=False, prob=1.0):
    """Evaluate probability for given tile."""

    # land on space and end turn
    if end_turn:
        prob_vec[tile] += prob
        return

    # roll dice
    n_rolls += 1
    prob /= 16
    for i in [1, 2, 3, 4]:
        for j in [1, 2, 3, 4]:

            if i == j and n_rolls == 3:  # speeding
                roll(10, prob_vec, n_rolls, True, prob)
                continue

            # move spaces
            end_turn = i != j
            next_tile = (tile + i + j) % 40
            if next_tile == 30:  # Go to jail
                roll(10, prob_vec, n_rolls, True, prob)
            elif next_tile in [2, 17, 33]:  # Community Chest
                roll(next_tile, prob_vec, n_rolls, end_turn, prob * 14 / 16)
                roll(0, prob_vec, n_rolls, end_turn, prob / 16)
                roll(10, prob_vec, n_rolls, True, prob / 16)
            elif next_tile in [7, 22, 36]:  # Chance
                next_rail = ((next_tile + 5) // 10 * 10 + 5) % 40
                next_utility = 28 if next_tile >= 12 and next_tile < 28 else 12
                roll(next_tile, prob_vec, n_rolls, end_turn, prob * 6 / 16)
                roll(0, prob_vec, n_rolls, end_turn, prob / 16)
                roll(5, prob_vec, n_rolls, end_turn, prob / 16)
                roll(10, prob_vec, n_rolls, True, prob / 16)
                roll(11, prob_vec, n_rolls, end_turn, prob / 16)
                roll(24, prob_vec, n_rolls, end_turn, prob / 16)
                roll(39, prob_vec, n_rolls, end_turn, prob / 16)
                roll(next_rail, prob_vec, n_rolls, end_turn, prob * 2 / 16)
                roll(next_utility, prob_vec, n_rolls, end_turn, prob / 16)
                if next_tile == 36:  # Chance -> Community Chest
                    roll(33, prob_vec, n_rolls, end_turn, prob * 14 / 256)
                    roll(0, prob_vec, n_rolls, end_turn, prob / 256)
                    roll(10, prob_vec, n_rolls, True, prob / 256)
                else:  # Chance -> 3 spaces backwards
                    roll((next_tile - 3) % 40, prob_vec, n_rolls, end_turn, prob / 16)
            else:
                roll(next_tile, prob_vec, n_rolls, end_turn, prob)


def p84():
    # Set up transition matrix
    M = np.zeros((40, 40))  # M[i, j] is prob j -> i
    for j in range(40):
        roll(j, M[:, j])

    # Apply transition many times on uniform vector
    p = np.ones(40) / 40
    for _ in range(101):
        p = M @ p

    sorted_i = np.argsort(p)[::-1]
    return "{:02d}{:02d}{:02d}".format(*sorted_i[:3])
