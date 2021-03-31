#!/usr/bin/python
"""

By solving all fifty Su Doku puzzles in 'sudoku.txt', a list of 50 puzzles, find
the sum of the 3-digit numbers found in the top left corner of each solution
grid.

Answer: 24702

"""

from math import floor
from copy import deepcopy

class DeepBreak(Exception):
    pass

class NoPossibleValues(Exception):
    def __init__(self, index):
        self.index = index
    def __str__(self):
        return repr(self.index)

class GuessOverflow(Exception):
    pass

def load_puzzle():
    L = []
    dummyline = file.readline()
    for count in range(9):
        line = file.readline()
        if line == '':
            return None
        L.append( [int(x) for x in line.rstrip('\n')] )
    return L

def annotate(box):
    pencil = {}
    box_r = int( floor((box-1)/3)*3 )
    box_c = int( ((box-1)%3)*3 )
    box_bad = []
    for r in range(box_r, box_r+3):
        for c in range(box_c, box_c+3):
            test = Su[r][c]
            if test != 0:
                box_bad.append(test)
    for r in range(box_r, box_r+3):
        r_bad = [x for x in Su[r] if x != 0]
        for c in range(box_c, box_c+3):
            c_bad = [row[c] for row in Su if row[c] != 0]
            if Su[r][c] == 0:
                imposs = list(set(r_bad + c_bad + box_bad))
                poss = [x for x in range(1, 10) if x not in imposs]
                pencil[(r,c)] = poss
    return pencil

def reduce_box(box):

    change = False
    # REDUCE
    small_change = True
    while small_change == True:
        while small_change == True:
            small_change = False
            pencil = annotate(box)
            remove = []
            for i, poss in pencil.iteritems():
                if len(poss) == 1:
                    Su[i[0]][i[1]] = poss[0]
                    remove.append(i)
                    change = True
                    small_change = True
                elif len(poss) == 0:
                    raise NoPossibleValues(i)
            for i in remove:
                del pencil[i]
        # BOX ANALYSIS
        small_change = False
        good = {}
        bad = []
        for i, poss in pencil.iteritems():
            for x in poss:
                if x in bad:
                    continue
                if x in good:
                    del good[x]
                    bad.append(x)
                else:
                    good[x] = i
        for x, i in good.iteritems():
            Su[i[0]][i[1]] = x
            change = True
            small_change = True
    return change

def print_puzzle():
    for line in Su:
        print line
    print

def check_solved():
    model = range(1, 10)
    for row in Su:
        if sorted(row) != model:
            return False
    for c in range(9):
        column = [row[c] for row in Su]
        if sorted(column) != model:
            return False
    for box in model:
        box_r = int( floor((box-1)/3)*3 )
        box_c = int( ((box-1)%3)*3 )
        L = []
        for r in range(box_r, box_r+3):
            for c in range(box_c, box_c+3):
                L.append(Su[r][c])
        if sorted(L) != model:
            return False
    return True
        

file = open("files/sudoku.txt", "r")
sum = 0

while True:
    next_puzzle_list = [load_puzzle()]
    if next_puzzle_list[0] == None:
        break
    try:
        while True:
            puzzle_list = deepcopy(next_puzzle_list)
            next_puzzle_list = []
            for Su in puzzle_list:
                last_box_changed = 0
                try:
                    while True:
                        for i in range(1, 10):
                            if last_box_changed == 9:
                                raise DeepBreak
                            a = reduce_box(i)
                            if a == True:
                                last_box_changed = 0
                            else:
                                last_box_changed += 1
                except NoPossibleValues as err_index:
                    continue
                except DeepBreak:
                    pass

                if check_solved():
                    raise DeepBreak
                try:
                    for optimal in range(2, 10):
                        for box in range(1, 10):
                            pencil = annotate(box)
                            for i, poss in pencil.iteritems():
                                if len(poss) == optimal:
                                    raise DeepBreak
                    raise GuessOverflow
                except GuessOverflow:
                    continue
                except DeepBreak:
                    pass
                for x in poss:
                    Su[i[0]][i[1]] = x
                    next_puzzle_list.append(deepcopy(Su))
    except DeepBreak:
        sum += int( str(Su[0][0]) + str(Su[0][1]) + str(Su[0][2]) )

print sum
file.close()
