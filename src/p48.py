# ANSWER 9110846700


def p48():
    return sum((pow(x, x, 10**10) for x in range(1, 1001))) % 10**10
