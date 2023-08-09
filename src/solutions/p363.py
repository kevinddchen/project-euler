# ANSWER 0.0000372091

"""

We first compute v by hand. Starting from the definition of the Bezier curve,

    B(t) = (1-t)^3 P0 + 3(1-t)^2 t P1 + 3(1-t) t^2 P2 + t^3 P3

    x = (1-t)^3 + 3(1-t)^2 t + 3(1-t) t^2 v
    y = 3(1-t)^2 t v + 3(1-t) t^2 + t^3

The area is given by the integral

    A = int_0^1 y(x) dx = int_1^0 y(t) x'(t) dt
      = ... (do the integration by hand, or Mathematica)
      = - (3v^2 - 12v - 10) / 20

Setting this equal to pi/4 and solving for v, the smaller solution is

    v = 2 - sqrt((22 - 5 pi) / 3)

The arclength is given by the integral

    L = int_0^1 sqrt(x'(t)^2 + y'(t)^2) dt

We do this numerically using scipy.

"""

from math import pi, sqrt

import scipy.integrate


def p363() -> str:
    v = 2 - sqrt((22 - 5 * pi) / 3)

    def dx(t: float) -> float:
        return -9 * t * t * v + 6 * t * t + 6 * t * v - 6 * t

    def dy(t: float) -> float:
        return 9 * t * t * v - 6 * t * t - 12 * t * v + 6 * t + 3 * v

    def dlength(t: float) -> float:
        return sqrt(dx(t) * dx(t) + dy(t) * dy(t))

    area: float
    err: float

    area, err = scipy.integrate.quad(dlength, 0, 1)

    actual_area = pi / 2
    assert err / actual_area < 1e-10, "Not enough precision"

    diff = 100 * abs(area - actual_area) / actual_area
    return f"{diff:.10f}"
