# ANSWER 14516824220

"""

You can work out that in a ring the only two tiles that can have up to 3 prime
neighbors are the top tiles and the one to its immediate right. Then given that the
sequence of tiles going straight upwards is 3*k*(k-1)+2, you can figure out what
differences need to be calculated.

"""

from mathfuncs import is_prime


def p128():
    C = 2  # includes 1 and 2 from the inner rings
    k = 2
    while True:
        if is_prime(6 * k - 1) and is_prime(6 * k + 1) and is_prime(6 * (2 * k + 1) - 1):
            C += 1  # top
            if C == 2000:
                return 3 * k * (k - 1) + 2
        if is_prime(6 * k - 1) and is_prime(6 * k + 5) and is_prime(6 * (2 * k - 1) - 1):
            C += 1  # top-right
            if C == 2000:
                return 3 * (k + 1) * k + 1
        k += 1
