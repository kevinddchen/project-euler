# ANSWER 18522

"""

For a cuboid a x b x c, the Lth layer contains

    2(ab+bc+ca) + 4(L-1)(a+b+c) + 4(L-1)(L-2)

blocks. So we just iterate over all a >= b >= c and L, using a priority queue
to keep track of all possibilities in a reasonable amount of time.

"""

import heapq


def blocks(a, b, c, L):
    return 2 * (a * b + b * c + c * a) + 4 * (L - 1) * (a + b + c) + 4 * (L - 2) * (L - 1)


def p126():
    h = []
    heapq.heappush(h, (blocks(1, 1, 1, 1), 1, 1, 1, 1))

    C = 0
    N = 0
    while True:
        (n, a, b, c, L) = heapq.heappop(h)

        if n == N:
            C = C + 1
        else:
            if C == 1000:
                break
            N = n
            C = 1

        heapq.heappush(h, (blocks(a, b, c, L + 1), a, b, c, L + 1))
        if L == 1:
            if c == 1:
                if b == 1:
                    heapq.heappush(h, (blocks(a + 1, b, c, L), a + 1, b, c, L))
                if b < a:
                    heapq.heappush(h, (blocks(a, b + 1, c, L), a, b + 1, c, L))
            if c < b:
                heapq.heappush(h, (blocks(a, b, c + 1, L), a, b, c + 1, L))

    return N
