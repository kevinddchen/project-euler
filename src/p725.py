# ANSWER 4598797036650685

"""

Since we are adding together digit-sum numbers, we can use some of their nice
properties to simplify the sum.

1.  Pick a digit sum between 1 and 9.

2.  Pick a partition of that digit sum into a list of smaller integers. If the
    partition is just a single number (equal to the digit sum), then we don't
    need to consider any permutations. Otherwise, we count how many different
    permutations of the smaller integers there are.

    In the former case, we let the multiplicity be 1. In the latter case, we
    let the multiplicity be 2 * (number of permutations of the smaller
    integers).

We claim that the sum over all digit-sum numbers stemming from this choice of
digits is

    repunit(2020) * digit_sum * multiplicity * comb(2019, len(partition))

As an example, let us consider only 4 digits, digit_sum = 3, and the partition
[2, 1]. Then the sum over all digit-sum numbers stemming from this choice of
digits is

    3210 + 3120 + 3201 + 3102 + 3021 + 3012
    + 2310 + 1320 + 2301 + 1302 + 0321 + 0312
    + 2130 + 1230 + 2031 + 1032 + 0231 + 0132
    + 2103 + 1203 + 2013 + 1023 + 0213 + 0123
    = 3333 * 12
    = 3333 * (2 * num_permutations([2, 1])) * comb(4 - 1, 2)

"""

from collections import defaultdict
from math import comb, factorial
from typing import Generator, Iterable


def _generate_partitions(n: int) -> Generator[list[int], None, None]:
    """Generate all partitions of n. Each partition is in decreasing order."""

    def gen(n: int, max_term: int) -> Generator[list[int], None, None]:
        if n == 0:
            yield []
            return

        assert max_term <= n
        for term in range(max_term, 0, -1):
            new_n = n - term
            new_max_term = term
            for partition in gen(new_n, min(new_n, new_max_term)):
                yield [term] + partition

    yield from gen(n, n)


def _count_permutations(items: Iterable[int]) -> int:
    """Given a list of integers, return the number of permutations of that list."""

    counts: dict[int, int] = defaultdict(lambda: 0)
    total_count = 0
    for item in items:
        counts[item] += 1
        total_count += 1

    result = factorial(total_count)
    for count in counts.values():
        result //= factorial(count)

    return result


def _repunit(num_digits: int) -> int:
    """Return the repunit with `num_digits` digits."""

    return (10**num_digits - 1) // 9


def p725() -> int:
    mod = 10**16
    num_digits = 2020

    total_sum = 0

    for digit_sum in range(1, 10):
        for partition in _generate_partitions(digit_sum):
            # if too many digits, skip
            if len(partition) + 1 > num_digits:
                continue

            multiplier = 1

            # if partition is not `[digit_sum]`, count its permutations
            if len(partition) != 1:
                multiplier *= 2 * _count_permutations(partition)

            # count the digit combinations
            multiplier *= comb(num_digits - 1, len(partition))

            total_sum = (total_sum + multiplier * digit_sum * _repunit(num_digits)) % mod

    return total_sum
