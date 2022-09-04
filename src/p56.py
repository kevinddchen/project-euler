# ANSWER 972


def p56():
    return max(sum(int(d) for d in str(a**b)) for a in range(2, 101) for b in range(2, 101))
