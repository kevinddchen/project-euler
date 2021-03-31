#!/usr/bin/python
#ANSWER 101524

"""

See solution explanations.

"""

from time import time

def roll(curr_tile, prob_vec, n=0, roll_bool=True, prob=1.):
    """ Set up probabilities for given starting tile """

    ## land on space and end turn
    if not roll_bool:
        prob_vec[curr_tile] += prob
        return

    ## roll dice
    n += 1
    prob /= len(D)**2
    for i in D:
        for j in D:

            if i==j and n == 3:         ## Speeding
                roll(10, prob_vec, n, False, prob)
                continue

            ## move spaces
            next_tile = (curr_tile + i + j) % 40
            if next_tile == 30:                ## Go to jail
                roll(10, prob_vec, n, False, prob)
            elif next_tile in [2, 17, 33]:     ## Community Chest
                roll(next_tile, prob_vec, n, i==j, prob*14/16)
                roll(0, prob_vec, n, i==j, prob/16)
                roll(10, prob_vec, n, False, prob/16) 
            elif next_tile in [7, 22, 36]:     ## Chance
                next_rail = ((next_tile+5)//10*10 + 5) % 40
                next_utility = 28 if next_tile >= 12 and next_tile < 28 else 12
                roll(next_tile, prob_vec, n, i==j, prob*6/16)
                roll(0, prob_vec, n, i==j, prob/16)
                roll(5, prob_vec, n, i==j, prob/16)
                roll(10, prob_vec, n, False, prob/16)
                roll(11, prob_vec, n, i==j, prob/16)
                roll(24, prob_vec, n, i==j, prob/16)
                roll(39, prob_vec, n, i==j, prob/16)
                roll(next_rail, prob_vec, n, i==j, prob*2/16)
                roll(next_utility, prob_vec, n, i==j, prob/16)
                if next_tile == 36:     ## Chance -> Community Chest
                    roll(33, prob_vec, n, i==j, prob*14/256)
                    roll(0, prob_vec, n, i==j, prob/256)
                    roll(10, prob_vec, n, False, prob/256)
                else:
                    roll((next_tile-3)%40, prob_vec, n, i==j, prob/16)
            else:
                roll(next_tile, prob_vec, n, i==j, prob)

def transform(A, x):
    """ Apply matrix A to vector x. Must have valid dimensions. """
    return [sum(A[i][j]*x[j] for j in range(len(A[0]))) for i in range(len(A))]

D = [1, 2, 3, 4]
def p84():
    ## Set up transition matrix
    M = [[0 for i in range(40)] for j in range(40)]
    for j in range(40):
        prob_vec = [0 for i in range(40)]
        roll(j, prob_vec)
        for i in range(40):
            M[i][j] = prob_vec[i]

    ## Apply transition many times
    repeat = 100
    p = [1/40. for i in range(40)]
    for i in range(repeat):
        p = transform(M, p)
    sorted_p = sorted([(prob, tile) for tile, prob in enumerate(p)], reverse=True)
    return "{0}{1}{2}".format(sorted_p[0][1], sorted_p[1][1], sorted_p[2][1])

if __name__ == '__main__':
    time_start = time()
    print(p84())
    print("Time: {0:.3f}".format(time()-time_start))

