from __future__ import annotations

from collections import deque
from enum import Enum, auto
from itertools import permutations, product
from typing import MutableSequence, MutableSet, NamedTuple

from mathfuncs import read_text

# --- Binary Tree -------------------------------------------------------------

LEAF = "x"
LEFT = "("
SEP = ","
RIGHT = ")"


class Node:
    """Node of a binary tree. Each node must have either 0 or 2 children."""

    __slots__ = ("left", "right")

    left: Node | None
    right: Node | None

    def __init__(self, left: Node | None = None, right: Node | None = None):
        assert (left is None and right is None) or (left is not None and right is not None)
        self.left = left
        self.right = right

    def to_string(self) -> str:
        """Return a string representation of the binary tree."""
        if self.left is None or self.right is None:
            return LEAF
        else:
            return f"{LEFT}{self.left.to_string()}{SEP}{self.right.to_string()}{RIGHT}"

    @classmethod
    def from_string(cls, string: str) -> Node:
        """Parse a binary tree from its string representation."""

        if string == LEAF:
            return cls()
        elif string[0] == LEFT:
            assert string[-1] == RIGHT
            left_string, right_string = cls._split_children(string)
            left = cls.from_string(left_string)
            right = cls.from_string(right_string)
            return cls(left=left, right=right)
        else:
            raise ValueError(f"Invalid node: {string}")

    @staticmethod
    def _split_children(string: str) -> tuple[str, str]:
        """Split string of form '(left,right)' into its two nodes."""

        string = string[1:-1]  # remove outer parentheses

        # get index of top-level ","
        depth = 0
        for i, char in enumerate(string):
            if char == LEFT:
                depth += 1
            elif char == RIGHT:
                depth -= 1
            elif char == SEP and depth == 0:
                return string[:i], string[i + 1 :]

        raise ValueError(f"Invalid node: {string}")


# --- Parenthesizations -------------------------------------------------------


def generate_parenthesizations(num_ops: int) -> set[str]:
    """Generate the parenthesizations over `num_ops` binary operations. For
    example, the associahedron over 2 operations are ((a,b),c) and (a,(b,c)).
    """

    init = _initial_parenthesization(num_ops)

    parens_all = set((init,))
    parens_queue = [init]

    # generate all parenthesizations
    while parens_queue:
        parens_new: list[str] = []
        for p in parens_queue:
            node = Node.from_string(p)
            _recurse_parenthesizations(node, node, parens_all, parens_new)
        parens_queue = parens_new

    return parens_all


def _initial_parenthesization(num_ops: int) -> str:
    """The initial parenthesization is the binary tree stacked on the left side."""

    node = Node()
    for _ in range(num_ops):
        node = Node(left=node, right=Node())
    return node.to_string()


def _recurse_parenthesizations(
    root: Node,
    current_node: Node,
    parens_all: MutableSet[str],
    parens_new: MutableSequence[str],
) -> None:
    """Recursively generate parenthesizations from a binary tree by making the
    replacement when possible: ((a,b),c) --> (a,(b,c))."""

    if current_node.left is None or current_node.right is None:
        return

    _recurse_parenthesizations(root, current_node.left, parens_all, parens_new)
    _recurse_parenthesizations(root, current_node.right, parens_all, parens_new)

    if current_node.left.left is None or current_node.left.right is None:
        return

    child = current_node.left
    child_left = current_node.left.left
    child_right = current_node.left.right
    parent_right = current_node.right
    # make temporary switch
    current_node.left = child_left
    current_node.right = child
    current_node.right.left = child_right
    current_node.right.right = parent_right
    # add to set
    string = root.to_string()
    if string not in parens_all:
        parens_new.append(string)
        parens_all.add(string)
    # switch back
    current_node.left = child
    current_node.right = parent_right
    current_node.left.left = child_left
    current_node.left.right = child_right


def compile_parenthesization(paren: str) -> list[tuple[int, int]]:
    """Given a parenthesization, return a list of indixes representing how
    each binary operations should act on an array of input values.

    For example, on paren = "((x,x),x)" this function should return:
        [(0, 1), (0, 2)]
    meaning that the first binary operation will operate on elements 0 and 1.
    By convention, the result will be placed at 0. Then, the second binary
    operation will operate on elements 0 and 2. The final result will always
    be in the 0th position.
    """

    num_ops = paren.count(SEP)
    indices = deque(range(num_ops + 1))
    idx_pairs: list[tuple[int, int]] = []

    root = Node.from_string(paren)
    final_idx = _recurse_compile(root, indices, idx_pairs)
    assert final_idx == 0

    return idx_pairs


def _recurse_compile(node: Node, unused_idxs: deque[int], idx_pairs: list[tuple[int, int]]) -> int:
    if node.left is None or node.right is None:
        idx = unused_idxs.popleft()
        return idx

    left_idx = _recurse_compile(node.left, unused_idxs, idx_pairs)
    right_idx = _recurse_compile(node.right, unused_idxs, idx_pairs)

    idx_pairs.append((left_idx, right_idx))
    return left_idx


def compile_all(max_ops: int) -> dict[int, list[list[tuple[int, int]]]]:
    """Generate and compile all parenthesizations."""

    compiled: dict[int, list[list[tuple[int, int]]]] = {}
    for num_ops in range(1, max_ops + 1):
        parens = generate_parenthesizations(num_ops)
        idx_pairs = [compile_parenthesization(paren) for paren in parens]
        compiled[num_ops] = idx_pairs
    return compiled


# --- Binary Operations -------------------------------------------------------


class BinaryOperation(Enum):
    ADD = auto()
    SUB = auto()
    MUL = auto()
    DIV = auto()


class BadOperation(Exception):
    pass


def execute_binary_operation(op: BinaryOperation, a: int, b: int) -> int:
    """Executes a binary operation on two integers and returns the result.
    Raises `BadOperation` if the operation is invalid."""

    if op == BinaryOperation.ADD:
        return a + b
    if op == BinaryOperation.SUB:
        if a <= b:
            raise BadOperation
        return a - b
    if op == BinaryOperation.MUL:
        return a * b
    if op == BinaryOperation.DIV:
        if a % b != 0:
            raise BadOperation
        return a // b


# -----------------------------------------------------------------------------


class Challenge(NamedTuple):
    target: int
    numbers: tuple[int, ...]


def evaluate(challenge: Challenge, compiled: dict[int, list[list[tuple[int, int]]]]) -> int:
    """Try all combinations of parenthesizations and binary operations to find
    the smallest sum of numbers that evaluates to `target`. Returns 0 if no
    solution exists."""

    best: int | None = None

    def try_nums(nums: tuple[int, ...]) -> None:
        nonlocal best
        num_ops = len(nums) - 1
        for idx_pairs in compiled[num_ops]:
            for ops in product(BinaryOperation, repeat=num_ops):
                try:
                    mut_nums = list(nums)
                    for op, (i, j) in zip(ops, idx_pairs):
                        mut_nums[i] = execute_binary_operation(op, mut_nums[i], mut_nums[j])
                    result = mut_nums[0]

                    if result == challenge.target:
                        best = sum(nums)
                        return

                except BadOperation:
                    pass

    for num_ops in range(1, len(challenge.numbers)):
        for nums in permutations(challenge.numbers, r=num_ops + 1):
            if best is not None and sum(nums) >= best:
                continue
            try_nums(nums)

    return best or 0


def parse_challenges() -> list[Challenge]:
    text = read_text("number_challenges.txt")
    lines = text.splitlines()

    def parse_line(line: str) -> Challenge:
        target, all_numbers = line.split(":")
        numbers = tuple(int(x) for x in all_numbers.split(","))
        return Challenge(int(target), numbers)

    return [parse_line(line) for line in lines]


def p828():
    challenges = parse_challenges()
    compiled = compile_all(max_ops=len(challenges[0].numbers))

    mod = 1_005_075_251
    total = 0
    for i, challenge in enumerate(challenges):
        ans = evaluate(challenge, compiled)
        print(i, ans)
        total = (total + pow(3, i + 1, mod) * ans) % mod

    return total
