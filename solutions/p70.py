#!/usr/bin/python
#ANSWER 8319823

"""

We are trying to minimize n/phi(n), which is the product: 
p_1/(p_1-1) * p_2/(p_2-1) * ... * p_i/(p_i-1) 
for all distinct prime factors p_i. Each term is greater than 1, so to minimize
the ratio we can take large primes for n. However, then phi(n) = n-1 and it
is impossible for them to be permutations. So, we let n be a product of two
primes. We can reasonably hold that for large enough n, we only need to
look at cases where n is the product of two primes.

Now, it is a matter of generating prime pairs whose products do not exceed
10^7. We can further reduce the prime search space by going through the primes
in increasing order, saving the smallest ratio achieved, and terminating once
we cannot achieve a smaller ratio, even without the permutation constraint.
This prevents us from searching all primes up to 10^7.

"""

from time import time
from mathfuncs import is_prime

def prime_gen():
    yield 2
    y = 3
    while True:
        if is_prime(y):
            yield y
        y += 2

def p70():
    LIMIT = 10**7
    M = (87109, 79180)
    p_lst = []
    for p in prime_gen():
        for q in p_lst:
            n, tot = p*q, (p-1)*(q-1)
            if n > LIMIT:
                if n*M[1] > tot*M[0]:
                    return M[0]
            else:
                if n*M[1] > tot*M[0]:
                    break
                if sorted(str(n)) == sorted(str(tot)) and n*M[1] < tot*M[0]:
                    M = (n, tot)
                    break
        p_lst.insert(0, p)

if __name__ == '__main__':
    time_start = time()
    print(p70())
    print("Time: {0:.3f}".format(time()-time_start))
