# ANSWER 0.00396087

"""

Descartes' Theorem allows you to find the radius of the kissing circle, given
the radii of three mutually tangent circles. With this theorem, we can generate
all the circles that form the "fractal" (which is called an Apollonian gasket).
It is crucial to memoize the results of the area calculations.

"""

import logging
from functools import cache
from math import pi
from time import time

LOG = logging.getLogger(__name__)


def solve_quadratic(a: float, b: float, c: float, larger: bool = True) -> float:
    """
    Solve the quadratic equation ax^2 + bx + c = 0. If `larger` is True this
    will return the larger solution (with the + sign), otherwise this will
    return the smaller solution (with the - sign).
    """
    discriminant = b**2 - 4.0 * a * c
    assert discriminant >= 0, f"Discriminant is negative for a={a} b={b} c={c}."
    sign = 1 if larger else -1
    return (-b + sign * discriminant**0.5) / (2.0 * a)


def get_kissing_curvature(k1: float, k2: float, k3: float, larger: bool = True) -> float:
    """
    Given the curvatures (inverse radii) of three mutually tangent circles,
    returns the curvature of a kissing circle, using Descartes' Theorem. If
    `larger` is True this will return the larger curvature, otherwise this will
    return the smaller curvature. A negative curvature means that the kissing
    circle encloses the three circles.

    Returns the larger curvature and the smaller curvature.
    """
    sum_of_k = k1 + k2 + k3
    sum_of_k_square = k1**2 + k2**2 + k3**2
    return solve_quadratic(1.0, -2.0 * sum_of_k, 2.0 * sum_of_k_square - sum_of_k**2, larger=larger)


@cache
def get_gasket_area(depth: int, k1: float, k2: float, k3: float) -> float:
    """
    Given the curvatures (inverse radii) of three mutually tangent circles,
    where k1 <= k2 <= k3, returns the area of the Apollonian gasket formed by
    recursively adding kissing circles to a maximum depth given by `depth`.
    """

    LOG.debug(f"depth={depth}: {k1:.3f} {k2:.3f} {k3:.3f}")

    if depth <= 0:
        return 0.0

    k = get_kissing_curvature(k1, k2, k3)
    area = pi / k**2

    # if more depth is needed, recurse
    if depth > 1:
        area += get_gasket_area(depth - 1, k, k1, k2)
        area += get_gasket_area(depth - 1, k, k2, k3)
        area += get_gasket_area(depth - 1, k, k1, k3)

    return area


def p199() -> float:

    depth = 10

    # get curvature of enclosing circle
    k0 = get_kissing_curvature(1.0, 1.0, 1.0, larger=False)
    total_area = pi / k0**2

    covered_area = 3 * pi  # the three initial circles
    covered_area += get_gasket_area(depth, 1.0, 1.0, 1.0)
    covered_area += 3 * get_gasket_area(depth, 1.0, 1.0, k0)  # even though k0 < 0, this is ok
    return round(1.0 - covered_area / total_area, 8)


if __name__ == "__main__":
    # logging.basicConfig(level=logging.DEBUG)
    time_start = time()
    print(f"{p199():.8f}")
    print("Time: {0:.3f}".format(time() - time_start))
