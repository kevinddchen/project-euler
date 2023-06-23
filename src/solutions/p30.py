# ANSWER 443839

"""

We can get an upper bound for the numbers to test. Let x be a positive integer
and f(x) be the sum of the fifth powers of the digits of x. We are looking for
cases where f(x) = x. If n is the number of digits of x, then as 10^(n-1) <= x
and f(x) <= n*9^5, if n*9^5 < 10^(n-1) then f(x) < x. Thus we require n <= 5.

"""


def generator(digits_left, initial, curr_sum):
    if digits_left == 0:
        if curr_sum == initial and initial not in [0, 1]:
            yield initial
    else:
        for i in range(10):
            for x in generator(digits_left - 1, initial * 10 + i, curr_sum + i**5):
                yield x


def p30():
    return sum(x for x in generator(6, 0, 0))
