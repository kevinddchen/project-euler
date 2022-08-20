# ANSWER 1.710637717

"""

The function given is very close to the analytic function f(x) = 1.42*2^{-x^2}.
Let us look for stable fixed-points for the function f(x), i.e. points x_0 where
f(x_0) = x_0 and |f'(x_0)| < 1. There is one fixed-point for f(x) at x_0 ~
0.855, but f'(x_0) ~ -1.014 so it is not stable. Next we have to look for
fixed-points of the double map, f(f(x)), which are x_0 ~ 1.029 and x_1 ~ 0.681.
These fixed-points are stable and satisfy f(x_0) = x_1 and f(x_1) = x_0. If an
initial point u_0 is picked near these values, iteratively calling u_{n+1} =
f(u_n) will converge upon these two fixed-points very quickly.

"""


def f(x):
    return int(2 ** (30.403243784 - x**2)) * 1e-9


def p197():
    u = -1
    for _ in range(1000):
        u = f(u)
    return "{0:.9f}".format(u + f(u))
