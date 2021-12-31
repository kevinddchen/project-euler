#!/usr/bin/python
#ANSWER 0.5731441

"""

The possibilities for rolling 9 four-sided dice is given by the generating function
(x + x^2 + x^3 + x^4)^9, and similary for the 6 six-sided dice

"""

from time import time

def mult_poly(p_1, p_2):
    """ Multiply two polynomials, in dictionary form. """
    p = {}
    for x in p_1:
        for y in p_2:
            if x+y in p:    p[x+y] += p_1[x]*p_2[y]
            else:           p[x+y]  = p_1[x]*p_2[y]
    return p

def p205():
    die6 = {i:1 for i in range(1, 7)}
    colin = die6 
    for _ in range(5):
        colin = mult_poly(colin, die6)

    die4 = {i:1 for i in range(1, 5)}
    peter = die4
    for _ in range(8):
        peter = mult_poly(peter, die4)

    C = 0
    for N in peter:
        for M in range(6, N):
            C += colin[M]*peter[N]
    return round(C*1./(4**9 * 6**6), 7)

if __name__ == '__main__':
    time_start = time()
    print(p205())
    print("Time: {0:.3f}".format(time()-time_start))
             
