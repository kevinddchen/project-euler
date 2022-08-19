# ANSWER 210


def p40():
    P = 1
    digit_count = 0
    x = 0
    for n in range(7):
        while digit_count < 10**n:
            x += 1
            digit_count += len(str(x))
        P *= int(str(x)[10**n - digit_count - 1])
    return P
