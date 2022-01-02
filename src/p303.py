#!/usr/bin/python
#ANSWER 1111981904675169

"""

Work out the possible multiples digit-by-digit instead of brute force, then
simply take the smallest possibility. Finding the answer for 9999 takes a long
time, so I just found the pattern:

9 --> 1358
99 --> 11335578
999 --> 111333555778
Therefore,
9999 --> 1111333355557778

I verified this by multiplying explicitly. So I summed the multiples for all
numbers up to 9998, and then added manually for 9999 and 10000 (which is just
1).

"""

from time import time

def only012(x):
    """ Returns true if integer x contains only digits 0, 1, 2 """
    while x != 0:
        if (x%10) > 2:
            return False
        x //= 10
    return True

def min_poss(poss):
    """ From a list of possible multiplications returns the smallest that
    contains only digits 0, 1, 2 (else returns zero) """

    best = 0
    for L in poss:
        if only012(L[1]):
            x = int(L[0])
            if (best == 0) or (x < best):
                best = x
    return best

def find_multiple(N, MultTable):

    MultList = MultTable[N%10]      ## take multiplications for last digit
    poss = []
    ## build initial possibilities:
    for x in MultList[0]:
        if x != 0:  ## ignore 0 as first digit
            poss.append( [str(x), (N*x)//10] )

    best = min_poss(poss)
    while best == 0:
        new_poss = []
        for L in poss:
            mult_index = (10 - L[1]%10)%10
            for x in MultList[mult_index]:
                new_poss.append( [str(x) + L[0], (N*x+L[1])//10] )
        poss = new_poss
        best = min_poss(poss)
    return best

def p303():
    ## Initialize Multiplication Table
    MultTable = [ [] for _ in range(10) ]
    for i in range(10):
        MultTable[i] = [ [] for _ in range(10) ]

    for i in range(10):
        for j in range(10):
            last_digit = (i*j)%10
            MultTable[i][last_digit].append(j)
            MultTable[i][last_digit-1].append(j)
            MultTable[i][last_digit-2].append(j)

    S = 0
    for N in range(1, 10000-1):
        S += find_multiple(N, MultTable)
    return S + 1111333355557778 + 1


if __name__ == '__main__':
    time_start = time()
    print(p303())
    print("Time: {0:.3f}".format(time()-time_start))
