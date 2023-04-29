# ANSWER 2772

"""

For a nx1 grid, there are (n+1) choose 2 = n(n+1)/2 ways of choosing the end
points for our rectangle. Therefore for a nxm grid, there are nm(n+1)(m+1)/4
possible rectangles.

"""


def nearest_m(n, t):
    """m for given n with nearest number of rectangles to target."""
    c = -4 * t / (n * (n + 1))
    return round(((1 - 4 * c) ** 0.5 - 1) / 2)


def p85():
    TARGET = 2000000
    minim = (TARGET, 0)

    n = 1
    m = nearest_m(n, TARGET)
    while m > n:
        N = n * m * (n + 1) * (m + 1) / 4
        if abs(TARGET - N) < minim[0]:
            minim = (abs(TARGET - N), n * m)
        n += 1
        m = nearest_m(n, TARGET)

    return minim[1]
