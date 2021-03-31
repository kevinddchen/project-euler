#!/usr/bin/python

class Sudoku:
    def __init__(self, S):
        self.S = S

    def get_row(self, i, j):
        return [self.S[i][k] for k in xrange(9)]
    def get_column(self, i, j):
        return [self.S[k][j] for k in xrange(9)]
    def get_box(self, i, j):
        box_i = i//3*3
        box_j = j//3*3
        return sum(([self.S[box_i+k][box_i+l] for l in xrange(3)]
                    for k in xrange(3)), []) 

    def check(self, i, j):
        """ Returns True if changes were made. i=row, j=column. """
        if self.S[i][j] != 0:
            return False
        row = self.get_row(i, j) 
        column = self.get_column(i, j) 
        box = self.get_box(i, j)
        leftover = [x for x in xrange(1, 10) if x not in row+column+box]
        if len(leftover) == 1:
            self.S[i][j] = leftover[0]
            return True
        else:
            return False

    def try_solve(self):
        t = True
        while t:
            t = False
            for i in xrange(9):
                for j in xrange(9):
                    if self.check(i, j):
                        t = True


raw_puzzle = [
[0,0,3,0,2,0,6,0,0],
[9,0,0,3,0,5,0,0,1],
[0,0,1,8,0,6,4,0,0],
[0,0,8,1,0,2,9,0,0],
[7,0,0,0,0,0,0,0,8],
[0,0,6,7,0,8,2,0,0],
[0,0,2,6,0,9,5,0,0],
[8,0,0,2,0,3,0,0,9],
[0,0,5,0,1,0,3,0,0]]
puzzle = Sudoku(raw_puzzle)
print puzzle.S
puzzle.try_solve()
print puzzle.S

