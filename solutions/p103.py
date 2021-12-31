#!/usr/bin/python
#ANSWER 20313839404245

"""

We can apply the algorithm to guess the optimal solution for n=7. Then we
generate all special sum sets with n=7 with sums less than that of the guess.
The difficulty is that it takes too long to generate all sets then individually check
whether they are special sum sets. You must make selective choices while
traversing the tree to only build sets that can construct special sum sets.
As it turns out, the guess is actually the optimal set.

"""

from time import time

def subsets(lst, i=0, temp=[]):
    """ Generates all subsets of lst."""
    yield temp
    for j in range(i, len(lst)):
        temp.append(lst[j])
        for x in subsets(lst, j+1, temp):
            yield x
        temp.pop()

def generate_possible(limit, n, temp=[]):
    """ Generates special sum sets with sums less than or equal to the limit. """

    if len(temp) == n:
        yield temp

    elif len(temp) == 0:
        i = 1
        while i*n + n*(n-1)//2 <= limit:
            temp.append(i)
            for x in generate_possible(limit, n, temp):
                yield x
            temp.pop()
            i += 1

    else:
        remain = n - len(temp)
        i = temp[-1]+1
        while sum(temp) + i*remain + remain*(remain-1)//2 <= limit:
            try:
                ## enforce property ii
                if len(temp) >= 2:
                    j = len(temp)//2 + 1
                    k = (len(temp)+1)//2 + 1
                    if i >= sum(temp[:j]) - sum(temp[k:]):
                        raise Exception
                ## enforce property i
                for s in [s[:] for s in subsets(temp)]:
                    if sum(s) == i:
                        raise Exception
                    other = [x for x in temp if x not in s]
                    for t in [t[:] for t in subsets(other)]:
                        if sum(s)+i == sum(t):
                            raise Exception

                temp.append(i)
                for x in generate_possible(limit, n, temp):
                    yield x
                temp.pop()
            except Exception:
                pass
            finally:
                i += 1
   
def p103():
    optimal_6 = [11, 18, 19, 20, 22, 25]
    ## apply algorithm to create guess 
    middle = optimal_6[len(optimal_6)//2]
    guess_7 = [middle] + [x+middle for x in optimal_6]

    minim = (sum(guess_7), guess_7)
    for x in generate_possible(sum(guess_7), 7):
        if sum(x) < minim[0]:
            minim = (sum(x), x)

    optimal_7 = minim[1]
    return ''.join(str(x) for x in optimal_7)

if __name__ == '__main__':
    time_start = time()
    print(p103())
    print("Time: {0:.3f}".format(time()-time_start))
