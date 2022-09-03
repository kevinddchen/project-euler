# ANSWER 0.3916721504

"""

Relatively simple if we can rely on third-party integration routines.
Thankfully, Python has scipy.integrate.

"""

from math import acos, pi, sqrt

from scipy.integrate import dblquad


def func(y: float, x: float) -> float:
    """
    Given point (x, y), returns the probability of the ant leaving along the
    long edge.
    """

    dot = (x * (x - 3) + y * (y - 4)) / (sqrt((x - 3) * (x - 3) + y * y) * sqrt((x * x + (y - 4) * (y - 4))))
    return acos(dot) / (2 * pi)


def p613() -> str:
    integral = dblquad(
        func=func,
        a=0,
        b=3,
        gfun=lambda x: 0,
        hfun=lambda x: 4 * (1 - x / 3),
        epsabs=1e-12,
        epsrel=1e-12,
    )
    assert integral[1] < 1e-10, "error is too large"
    area = 6.0
    prob = integral[0] / area
    return f"{prob:.10f}"
