# ANSWER 1258

"""

Can be solved directly using brute force by iterating through all combinations
of digits, permutations of those digits, permutations of the symbols (+, -, *,
/) with repeats, and orders of operations.

"""

from itertools import combinations, combinations_with_replacement, permutations


def add(x, y):
    return x + y


def sub(x, y):
    return x - y


def mult(x, y):
    return x * y


def div(x, y):
    return x * 1.0 / y


def perform_op(digits, i, op):
    return digits[:i] + (op(*digits[i : i + 2]),) + digits[i + 2 :]


def p93():
    maxim = (0, [])
    for digit_combo in combinations(range(1, 10), 4):
        numbers = []
        for digits in permutations(digit_combo):
            for symbol_combo in combinations_with_replacement([add, sub, mult, div], 3):
                for symbols in permutations(symbol_combo):
                    for order in permutations(range(3)):
                        try:
                            # first operation
                            d = perform_op(digits, order[0], symbols[order[0]])
                            # second operation
                            j = order[1]
                            if j > order[0]:
                                j -= 1
                            d = perform_op(d, j, symbols[order[1]])
                            # last operation
                            d = perform_op(d, 0, symbols[order[2]])[0]
                            # if d is integer, save
                            if d == round(d) and d > 0:
                                numbers.append(round(d))
                        except ZeroDivisionError:
                            # if divide by zero
                            pass

        # consecutive numbers 1 to n
        n = 0
        while n + 1 in numbers:
            n += 1
        maxim = max((n, digit_combo), maxim)

    return "".join(str(x) for x in maxim[1])
