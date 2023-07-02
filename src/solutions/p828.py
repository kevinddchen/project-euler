# ANSWER 148693670

"""

For each tuple of numbers, we recursively generate all possible values that can
be created from the four operations.

"""

from itertools import combinations, product
from typing import Generator, NamedTuple

from mathfuncs import read_text


def _iterate_subsets(nums: tuple[int, ...]) -> Generator[tuple[tuple[int, ...], tuple[int, ...]], None, None]:
    """Iterate over all ways to split `nums` into two non-empty subsets."""
    assert len(nums) > 1

    includes_generator = product([True, False], repeat=len(nums))
    next(includes_generator)  # skip all True
    for _ in range(2 ** len(nums) - 2):
        subset_a_includes = next(includes_generator)
        subset_a = tuple(x for x, include in zip(nums, subset_a_includes) if include)
        subset_b = tuple(x for x, include in zip(nums, subset_a_includes) if not include)
        yield subset_a, subset_b


def get_all_values(nums: tuple[int, ...]) -> set[int]:
    """Given a tuple of numbers, return all possible values that can be
    obtained by applying binary operations to the numbers. We do this by
    splitting the tuple into two non-zero subsets, recursively getting all
    possible values from each subset, and then combining the values from each
    subset using the four operations."""

    if len(nums) == 1:
        return set((nums[0],))

    # split into two subsets and recursively get all values from each subset
    values: set[int] = set()
    for nums_a, nums_b in _iterate_subsets(nums):
        values_a = get_all_values(nums_a)
        values_b = get_all_values(nums_b)
        for a in values_a:
            for b in values_b:
                values.add(a + b)
                values.add(a * b)
                if a > b:
                    values.add(a - b)
                if a % b == 0:
                    values.add(a // b)
    return values


class Problem(NamedTuple):
    target: int
    numbers: tuple[int, ...]


def find_minimum_score_solution(problem: Problem) -> int:
    """Iterate over all combinations of numbers and find the minimum score."""
    min_score: int | None = None
    for n in range(1, len(problem.numbers) + 1):
        for nums in combinations(problem.numbers, n):
            if min_score is not None and sum(nums) >= min_score:
                continue
            values = get_all_values(nums)
            if problem.target in values:
                # we have already checked that sum(nums) < min_score
                min_score = sum(nums)

    return min_score if min_score is not None else 0


def parse_problems() -> list[Problem]:
    text = read_text("number_challenges.txt")
    lines = text.splitlines()

    problems: list[Problem] = []
    for line in lines:
        target, all_numbers = line.split(":")
        numbers = tuple(int(x) for x in all_numbers.split(","))
        problems.append(Problem(int(target), numbers))

    return problems


def p828() -> int:
    problems = parse_problems()
    mod = 1_005_075_251
    total = 0
    for i, problem in enumerate(problems):
        min_score = find_minimum_score_solution(problem)
        total = (total + pow(3, i + 1, mod) * min_score) % mod
    return total
