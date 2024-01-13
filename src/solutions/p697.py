# ANSWER 4343871.06

"""

We first reformulate the problem slightly,

    X_0 = 1
    X_1 = U_1
    X_2 = U_2 * U_1
    ...
    X_n = U_n * U_{n-1} * ... * U_1

and we want to find the probability that X_n < 1/c. Alternatively, let a_i =
-ln(U_i) and define another random variable Y_i = -ln(X_i). So we have an
equivalent problem,

    Y_0 = 0
    Y_1 = a_1
    Y_2 = a_1 + a_2
    ...
    Y_n = a_1 + a_2 + ... + a_n

and we want to find the probability that Y_n > ln(c). The a_i are iid according
to the exponential distribution with lambda = 1. Thus, Y is described by a
Poisson process. The probability that Y_n > ln(c) is given by the CDF,

    P(Y_n > ln c)
    = P(N(ln c) = 0) + P(N(ln c) = 1) + ... + P(N(ln c) = n - 1)
    = Q(n, ln c)

where Q is the regularized gamma function. We take advantage of Scipy to
compute this function, so we just do a simple binary search to find the ln c
that produces an output of 0.25, for the given value of n.

"""

from math import log

from scipy.special import gammaincc


def p697():
    n = 10_000_000
    target_prob = 0.25
    tolerance = 1e-3  # numerical error for ln(c)

    # first, find a value of ln(c) that gives a prob less than the target
    lnc_upper = 1
    while gammaincc(n, lnc_upper) > target_prob:
        lnc_upper *= 2
    lnc_lower = lnc_upper / 2

    # we have Q(n, lnc_upper) < target_prob < Q(n, lnc_lower)
    # use binary search to narrow the bounds below the given tolerance
    while lnc_upper - lnc_lower > tolerance:
        lnc_mid = (lnc_upper + lnc_lower) / 2
        if gammaincc(n, lnc_mid) > target_prob:
            lnc_lower = lnc_mid
        else:
            lnc_upper = lnc_mid

    lnc = (lnc_upper + lnc_lower) / 2

    # we return log_10(c) rounded to 2 decimals
    return round(lnc / log(10), 2)
