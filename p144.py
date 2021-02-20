#!/usr/bin/python
#ANSWER 354

"""

This question can be solved using a lot of tedious geometry. Given two points,
A and B, we can draw a vector of approach, v, from A to B. At B, we get the
normal vector to the ellipse, which we can then use Gram-Schmidt to decompse v
into parallel and perpendicular components. The vector of reflection is w = v -
2*v_parall.  Then B + tw satisfies the equation 4x^2 + y^2 = 100 for some t.
This gives a quadratic equation in t which we can solve, and we take the
non-zero solution. This gives the next point of reflection, C.

"""

from time import time

def vec_add(v, w):
    return (v[0]+w[0], v[1]+w[1])

def vec_scale(v, a):
    return (a*v[0], a*v[1])

def vec_dot(v, w):
    return v[0]*w[0] + v[1]*w[1]

def normal(v):
    return (4*v[0], v[1])

def next_point(A, B):
    v = vec_add(B, vec_scale(A, -1))
    n = normal(B)
    v_par = vec_scale(n, vec_dot(v, n)/vec_dot(n, n))
    w = vec_add(v, vec_scale(v_par, -2))
    t = 2*vec_dot(v, n)/(4*w[0]**2 + w[1]**2)
    return vec_add(B, vec_scale(w, t))

def p144():
    A = (0, 10.1)
    B = (1.4, -9.6)
    count = 0
    while not(-0.01 < B[0] and B[0] < 0.01 and B[1] > 0):
        A, B = B, next_point(A, B)
        count += 1
    return count

if __name__ == '__main__':
    time_start = time()
    print(p144())
    print("Time: {0:.3f}".format(time()-time_start))


