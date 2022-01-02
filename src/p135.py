#!/usr/bin/python
#ANSWER 4989

"""

If we have an arithmetic progression x, x+d, x+2d, the the equation simplifies
to (3d-x)(d+x) = n. Therefore for each n we find divisors and solve for d and x.

"""

from time import time

def divisor_sieve(LIMIT):
    sieve = [[1] for _ in range(LIMIT)]
    for x in range(2, LIMIT):
        for y in range(x, LIMIT, x):
            sieve[y].append(x)
    for i, d_list in enumerate(sieve):
        if i > 0:
            yield i, d_list

def count_solutions(n, d_list):
    count = 0
    for a in d_list:
        b = n//a
        if a >= b and (a+b)%4 == 0:
            d = (a+b)//4

            if a==b:
                count += 1
            elif d < a and d < b:
                count += 2
            else:
                count += 1
    return count

def p135():
    return sum(1 for n, L in divisor_sieve(1000000) if count_solutions(n, L) == 10)

if __name__ == '__main__':
    time_start = time()
    print(p135())
    print("Time: {0:.3f}".format(time()-time_start))

