# ANSWER 9669182880384

"""

We keep track of all previous coordinates. For each new coordinate, we compute
the slope with all previous coordinates. We check that a new line is being made
by reducing the slope to coprime factors and checking that adding integer
multiples of the slope to the new coordinate does not produce two previous
coordinates.

We then track parallel lines by keeping a dictionary of slopes and the number
of lines with that slope.

"""

from __future__ import annotations

from math import gcd
from typing import Container, Iterator, NamedTuple

SIZE = 1000
TARGET = 2500


class Coordinate(NamedTuple):
    x: int
    y: int


class Displacement(NamedTuple):
    """`dx` and `dy` must be coprime."""

    dx: int
    dy: int

    def __radd__(self, other: Coordinate) -> Coordinate:
        return Coordinate(other.x + self.dx, other.y + self.dy)

    def reverse(self) -> Displacement:
        return Displacement(-self.dx, -self.dy)


def coord_generator(stop: int) -> Iterator[Coordinate]:
    def s_generator() -> Iterator[int]:
        m = 50_515_093
        s = 290_797
        while True:
            s = (s * s) % m
            yield s

    def t_generator() -> Iterator[int]:
        for s in s_generator():
            yield (s % (2 * SIZE)) - SIZE

    t_gen = t_generator()
    for _ in range(stop):
        t1 = next(t_gen)
        t2 = next(t_gen)
        yield Coordinate(t1, t2)


def compute_displacement(p: Coordinate, q: Coordinate) -> Displacement:
    """Returns the displacement from p to q"""
    dx = q.x - p.x
    dy = q.y - p.y
    assert not (dx == 0 and dy == 0), "Points are coincident."
    n = gcd(abs(dx), abs(dy))
    dx, dy = dx // n, dy // n
    return Displacement(dx, dy)


def check_new_line(prev_coords: Container[Coordinate], coord: Coordinate, disp: Displacement) -> bool:
    """If by adding multiples of `disp` to `coord` we encounter at least two
    previous coordinates, then we are not making a new line.

    Returns True if we are making a new line."""

    def inside_bounds(coord: Coordinate) -> bool:
        return (-SIZE <= coord.x < SIZE) and (-SIZE <= coord.y < SIZE)

    count = 0

    for disp_ in [disp, disp.reverse()]:
        new_coord = coord + disp_
        while inside_bounds(new_coord):
            if new_coord in prev_coords:
                count += 1
                if count >= 2:
                    return False
            new_coord = new_coord + disp_
    return True


def p630() -> int:

    num_lines = 0
    num_intersections = 0

    prev_coords: set[Coordinate] = set()
    prev_disps: dict[Displacement, int] = dict()

    for coord in coord_generator(TARGET):
        for prev_coord in prev_coords:

            # displacement with each previous coordinate
            disp = compute_displacement(prev_coord, coord)

            # check a new line is being made
            if not check_new_line(prev_coords, coord, disp):
                continue

            # check for parallel lines
            # first, make `disp` a positive vector
            if disp.dx == 0:
                disp = Displacement(0, abs(disp.dy))
            if disp.dx < 0:
                disp = disp.reverse()
            count_parallel = prev_disps.get(disp, 0)

            num_intersections += 2 * (num_lines - count_parallel)
            num_lines += 1

            prev_disps[disp] = count_parallel + 1
        prev_coords.add(coord)

    return num_intersections
