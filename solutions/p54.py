#!/usr/bin/python
#ANSWER 376

"""

Simple in theory, but quite tedious in practice. There are many approaches to
this problem. I used a scoring system that gave each hand a value and compared
the values (here they are lists, but in theory they can be turned into unique
integers).

 - Table of Scores - 
_____________________________________________________________________
    *RANK POINTS*       |           *SECONDARY POINTS*               |  
                        |   I    |   II   |  III   |   IV   |   V    |
High Card:          1   | Single | Single | Single | Single | Single |
One Pair:           2   | Pair   | Single | Single | Single | -      |
Two Pairs:          3   | Pair   | Pair   | Single | -      | -      |
Three of a Kind:    4   | Triple | Single | Single | -      | -      |
Straight:           5   | Single | -      | -      | -      | -      |
Flush:              6   | Single | Single | Single | Single | Single |
Full House:         7   | Triple | Pair   | -      | -      | -      |
Four of a Kind:     8   | Quad   | Single | -      | -      | -      |
Straight Flush:     9   | Single | -      | -      | -      | -      |

"""

from time import time

def score(hand):
    values = sorted([value(card) for card in hand], reverse=True)
    flush_bool = find_flush(hand)
    straight_bool, straight_point = find_straight(values)
    decomp_dct = decompose(values)
    
    if flush_bool and straight_bool:        ## straight
        return [9, straight_point]
    if 4 in decomp_dct:                     ## four of a kind
        return [8] + decomp_dct[4] + decomp_dct[1]
    if 3 in decomp_dct and 2 in decomp_dct: ## full house
        return [7] + decomp_dct[3] + decomp_dct[2]
    if flush_bool:                          ## flush
        return [6] + values
    if straight_bool:                       ## straight
        return [5, straight_point]
    if 3 in decomp_dct:                     ## three of a kind
        return [4] + decomp_dct[3] + decomp_dct[1]
    if 2 in decomp_dct:
        if len(decomp_dct[2])==2:           ## two pair
            return [3] + decomp_dct[2] + decomp_dct[1]
        return [2] + decomp_dct[2] + decomp_dct[1]  ## one pair
    return [1] + decomp_dct[1]                    ## high card

def suit(card):
    return card[1]

def value(card):
    v = card[0]
    if v == 'A': return 14
    if v == 'K': return 13
    if v == 'Q': return 12
    if v == 'J': return 11
    if v == 'T': return 10
    return int(v)

def find_flush(hand):
    """hand --> True/False"""
    for card in hand:
        if suit(card) != suit(hand[0]):
            return False
    return True

def find_straight(values):
    """values --> True/False, leading value"""
    ## Special case A2345:
    if values == [14, 5, 4, 3, 2]:
        return True, 5
    for i in range(len(values)-1):
        if values[i]-values[i+1] != 1:
            return False, 0 
    return True, values[0]

def decompose(values):
    """values --> {repetitions:[values,...]}"""
    dct = {}
    for v in values:
        rep = values.count(v)
        if rep in dct:
            if v not in dct[rep]:
                dct[rep].append(v)
        else:
            dct[rep] = [v]
    return dct

def p54():
    count = 0
    with open('files/poker.txt', 'r') as fl:
        for line in fl.readlines():
            line = line.strip('\n\r').split(' ')
            hand1, hand2 = line[:5], line[5:]
            if score(hand1) > score(hand2):
                count += 1
    return count

if __name__ == '__main__':
    time_start = time()
    print(p54())
    print("Time: {0:.3f}".format(time()-time_start))

