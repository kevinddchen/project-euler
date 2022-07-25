# ANSWER 2.223561019313554106173177

"""

Note that

    theta = a1 + (1/a1)( a2 - a1 + (1/a2) ( a3 - a2 + (1/a3) ( ... )))

We can work out the a_i coefficients one-by-one, using the previous a_i in the
sequence. Only a2=2 and a3=2 have to be deduced by checking all possibilities.
The hardest part is keeping track of enough precision, which we do using the
`decimal` package.

"""

import decimal
from time import time

decimal.getcontext().prec = 30


def p751():

    theta = decimal.Decimal("2.22")

    prec = decimal.Decimal("0.01")  # decimal precision of theta
    lb = decimal.Decimal(2)  # lower bound for theta
    a = 2
    denom = 8

    while prec > 1e-24:
        a_diff = (denom * (theta - lb)).quantize(1, rounding=decimal.ROUND_DOWN)
        a += a_diff
        # update lower bound
        lb += a_diff / denom
        denom *= a
        # update theta
        prec /= 10 ** len(str(a))
        theta += a * prec

        print(theta)

    return theta.quantize(decimal.Decimal("1e-24"), rounding=decimal.ROUND_DOWN)


if __name__ == "__main__":
    time_start = time()
    print(p751())
    print("Time: {0:.3f}".format(time() - time_start))
