# ANSWER 20492570929

"""

Can be solved by hand. See PDF for explanation.

"""


def p116():
    L_2 = [1, 0]
    L_3 = [1, 0, 0]
    L_4 = [1, 0, 0, 0]
    for _ in range(50):
        L_2.insert(0, L_2[0] + L_2.pop())
        L_3.insert(0, L_3[0] + L_3.pop())
        L_4.insert(0, L_4[0] + L_4.pop())
    return L_2[0] + L_3[0] + L_4[0] - 3
