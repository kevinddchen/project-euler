# ANSWER 906609


def p4():
    maxproduct = 0
    a, b = 999, 999
    while a * b > maxproduct:
        while a * b > maxproduct:
            if str(a * b) == str(a * b)[::-1]:
                maxproduct = a * b
                break
            b -= 1
        a -= 1
        b = a
    return maxproduct
