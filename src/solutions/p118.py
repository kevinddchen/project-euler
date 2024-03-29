# ANSWER 44680

"""

To solve this problem, every single concatenation was reached using a
depth-first tree search. Starting with an empty set, the digits 1-9 were
added by 1) inserting into an existing element, left to right, then 2)
appending to the end. To reduce the number of searches, a criteria was
evaluated at each node to determine if it is possible to have every number
in the list be prime, given the number of digits remaining.

For instance, if there were four numbers in the set already and we have yet
to add 7, 8, and 9, if all four numbers are not prime then we can abandon
this branch.

Once we get to the bottom of the tree and all 9 digits are used, we simply
check that all elements are prime. Each set is guaranteed to be unique.

"""

from mathfuncs import is_prime


def recurse(lst=[], n=1):
    # evaluate criteria
    crit = n + len(lst) - 10
    if crit > 0:
        n_primes = sum(1 for x in lst if (x > 1 and is_prime(x)))
        if n_primes < crit:
            return 0

    # hit bottom of tree
    if n == 10:
        return 1

    # recursive step
    S = 0
    for i, x in enumerate(lst):
        j = 0
        x_str = str(x)
        while j <= len(x_str):
            new_x = int(x_str[:j] + str(n) + x_str[j:])
            lst[i] = new_x
            S += recurse(lst, n + 1)
            j += 1
        lst[i] = x

    lst.append(n)
    S += recurse(lst, n + 1)
    lst.pop()
    return S


def p118():
    return recurse()
