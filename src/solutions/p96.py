# ANSWER 24702

import heapq
from functools import cached_property

import numpy as np

from mathfuncs import read_text


class SudokuInputError(Exception):
    pass


class SudokuInconsistency(Exception):
    pass


class Sudoku(object):
    """
    Class for solving Sudoku puzzles.

    `mode` refers to how the information in the puzzle is organized. When
    mode=0, the majors are rows. When mode=1, the majors are columns. When
    mode=2, the majors are the 3 x 3 blocks of squares.

    Constructors:

        Sudoku(arr): arr is 9 x 9 array of integers between 0 and 9 (inclusive),
        where 0 represents an empty square.

        Sudoku(Sudoku): copies information from another Sudoku instance.

    Methods:

        (bool) is_solved(): returns True if puzzle is solved and valid.

        (bool) is_valid(): returns True if puzzle is valid. Also works for
        incomplete puzzles.

        (void) reduce(): fill in squares using simple logic. This is not
        guaranteed to solve the puzzle. Raises a `SudokuInconsistency` exception
        if the puzzle is invalid.

        (Sudoku) solve(): returns a solved puzzle. This is guaranteed to find a
        solution, if one exists. Otherwise, raises a `SudokuInconsistency`
        exception if there is no solution.

    Internal parameters:

        _grid: puzzle represented as 9 x 9 array of ints.

        _hints: dictionary of (i, j): array pairs. (i, j) is a location where
            _grid[i, j] is not yet filled-in. _hint[(i, j)] is an array of nine
            boolean values corresponding to possible values of _grid[i, j].

        _news: list of (i, j) tuples representing new filled-in squares.
    """

    def __init__(self, arg):
        # Sudoku(Sudoku) constructor
        if isinstance(arg, Sudoku):
            self._grid = arg._grid.copy()
            self._hints = {c: h.copy() for c, h in arg._hints.items()}
            self._news = arg._news.copy()

        # Sudoku(arr) constructor
        else:
            # initialize grid
            _validate_input(arg)
            arg = np.array(arg, np.uint8)
            _validate_grid(arg)
            self._grid = arg
            # initialize hints and news
            self._hints = {}
            self._news = []
            for i, row in enumerate(self._grid):
                for j, el in enumerate(row):
                    if el == 0:
                        self._hints[(i, j)] = np.ones(9, dtype=np.uint8)
                    else:
                        self._news.append((i, j))

    def __repr__(self):
        return str(self._grid)

    def __lt__(self, other):  # used in priority queue
        return self._ordinal < other._ordinal

    def is_solved(self):
        return len(self._hints) == 0 and self.is_valid()

    def is_valid(self):
        try:
            _validate_grid(self._grid)
            return True
        except SudokuInconsistency:
            return False

    def reduce(self):
        """
        Take each filled-in square and eliminate hints. If we encounter a square
        that only has one hint left, then we fill in the square. We also check
        for inconsistencies along the way.
        """
        while self._news:
            c1 = self._news.pop()
            el = self._grid[c1]
            # eliminate row, column, and 3 x 3 block
            for mode in range(3):
                major_idx = _get_major_idx(c1, mode)
                for c2 in _get_major(major_idx, mode):
                    # if not yet filled-in, eliminate hint
                    if self._grid[c2] == 0 and self._hints[c2][el - 1]:
                        self._hints[c2][el - 1] = False
                        # check if only one hint left
                        poss = np.nonzero(self._hints[c2])[0] + 1
                        if len(poss) == 1:
                            (n,) = poss
                            self._fill_in(c2, n)
                    # if already filled-in, check not equal
                    elif self._grid[c2] == el and c1 != c2:
                        err_msg = f"Found inconsistent entry {el} at ({c2[0] + 1}, {c2[1] + 1})."
                        raise SudokuInconsistency(err_msg)

    def solve(self):
        """
        Solve by reducing and making guesses. We keep track of our guesses with
        a priority queue, and always make guesses for the puzzle with the fewest
        number of possibilites. When a puzzle is inconsistent (i.e. an earlier
        guess was incorrect), it is discarded.
        """
        self.reduce()
        if self.is_solved():
            return self

        heap = [self]
        # loop guesses
        while heap:
            puzzle = heapq.heappop(heap)
            _, c = puzzle._min_hints
            poss = np.nonzero(puzzle._hints[c])[0] + 1
            for n in poss:
                child = Sudoku(puzzle)
                child._fill_in(c, n)  # make guess in child
                try:
                    child.reduce()
                except SudokuInconsistency:
                    continue
                if child.is_solved():
                    return child
                heapq.heappush(heap, child)
        err_msg = "Puzzle has no solution."
        raise SudokuInconsistency(err_msg)

    # --- Private -------------------------------------------------------------

    def _fill_in(self, coord, n):
        """Fill in square of puzzle."""
        self._grid[coord] = n
        del self._hints[coord]
        self._news.append(coord)

    @cached_property
    def _min_hints(self):
        """Returns (n, c) where c is a coordinate with n hints and n is minimal.
        Must be called after `reduce` for intended effects."""
        return min((np.sum(h), c) for c, h in self._hints.items())

    @cached_property
    def _ordinal(self):
        """Sudoku puzzles are ordered by (i) minimum number of hints, and (ii)
        number of empty squares.  Must be called after `reduce` for intended
        effects."""
        n, _ = self._min_hints
        return (n, len(self._hints))


def _validate_input(arr):
    """Basic input validation."""
    if len(arr) != 9:
        err_msg = f"Invalid number of rows. Got {len(arr)}, but expected 9."
        raise SudokuInputError(err_msg)
    for i, row in enumerate(arr):
        if len(row) != 9:
            err_msg = f"Invalid length for row {i + 1}. Got {len(row)}, but expected 9."
            raise SudokuInputError(err_msg)
        for j, el in enumerate(row):
            if (not isinstance(el, int)) or el < 0 or el > 9:
                err_msg = (
                    f"Invalid entry at ({i + 1}, {j + 1}). "
                    "Got {el}, but expected an integer between 0 and 9 (inclusive)."
                )
                raise SudokuInputError(err_msg)


def _validate_grid(grid):
    """Check puzzle is valid."""
    for mode in range(3):
        for major_idx in range(9):
            filled = set()  # tracks filled-in values in the major
            for c in _get_major(major_idx, mode):
                el = grid[c]
                if el > 0:
                    if el in filled:
                        err_msg = f"Invalid puzzle. Duplicate entry {el} at ({c[0] + 1}, {c[1] + 1})."
                        raise SudokuInputError(err_msg)
                    filled.add(el)


def _get_major_idx(coord, mode):
    """Get the index of the major containing (i, j)."""
    if mode == 0:
        return coord[0]
    if mode == 1:
        return coord[1]
    if mode == 2:
        return 3 * (coord[0] // 3) + (coord[1] // 3)


def _get_major(major_idx, mode):
    """Get the nine coordinates (i, j) of a major."""
    if mode == 0:
        irange = range(major_idx, major_idx + 1)
        jrange = range(9)
    elif mode == 1:
        irange = range(9)
        jrange = range(major_idx, major_idx + 1)
    else:
        imin = 3 * (major_idx // 3)
        jmin = 3 * (major_idx % 3)
        irange = range(imin, imin + 3)
        jrange = range(jmin, jmin + 3)
    for i in irange:
        for j in jrange:
            yield (i, j)


def read_puzzles():
    text = read_text("sudoku.txt")
    lines = text.splitlines()
    while lines:
        line = lines.pop(0)
        if line:
            arr = []
            for _ in range(9):
                x = lines.pop(0)
                x = x.strip("\n")
                x = [int(c) for c in x]
                arr.append(x)
            yield arr


def p96():
    S = 0
    for arr in read_puzzles():
        puzzle = Sudoku(arr)
        puzzle = puzzle.solve()
        S += puzzle._grid[0, 0] * 100 + puzzle._grid[0, 1] * 10 + puzzle._grid[0, 2]
    return S
