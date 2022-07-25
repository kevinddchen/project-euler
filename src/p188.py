# ANSWER 95962097

"""

We are finding 1777^^1855 = 1777^{1777^^1854} (mod 10^8)$. The generalized
Fermat's little theorem says that a^{phi(n)} = 1 (mod n) for any coprime a and
n, where phi(n) is the totient function. Since 1777 is prime, so
1777^{1777^^1854} = 1777^{a_1} (mod 10^8)$ for some integer a_1 = 1777^^1854
(mod phi(10^8)). We can repeat this process by taking successive totients,
defining a sequence a_1, a_2, ... Eventually we will reach a totient phi^k(10^8)
= 2. As 1777 is odd, any power of 1777 is odd so a_k = 1. We can then work
backwards using the recursive formula a_i = 1777^{a_{i+1}} (mod phi^i(10^8))
until we find a_0, which is the answer.

"""

from time import time

from .mathfuncs import prime_factorize


def totient(x):
    for f, _ in prime_factorize(x):
        x = (x // f) * (f - 1)
    return x


def p188():
    mod_list = [10**8]
    while mod_list[-1] != 2:
        mod_list.append(totient(mod_list[-1]))
    x = 1
    for mod in mod_list[::-1]:
        x = pow(1777, x, mod)
    return x


if __name__ == "__main__":
    time_start = time()
    print(p188())
    print("Time: {0:.3f}".format(time() - time_start))
