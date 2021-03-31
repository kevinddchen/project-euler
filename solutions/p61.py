#!/usr/bin/python
#ANSWER 28684

"""

Generate all polygon numbers, then do a depth-first search for a cycle. The set
is {8256, 5625, 2512, 1281, 8128, 2882} with polygonal types {3, 4, 7, 8, 6, 5}.

"""

from time import time

def polygonGen(s):
    """Generates polygonal numbers of s-sides"""
    n = 1
    while True:
        yield n*(n-1)*(s-2)/2 + n 
        n += 1

def findChain(first, head, used, answer, poly_dicts):
    """Recursive depth-first search for cycle"""
    n = 0
    for s in xrange(len(poly_dicts)):
        if used[s]: continue
        n += 1
        if head in poly_dicts[s]:
            used[s] = True 
            for tail in poly_dicts[s][head]:
                answer.append(head*100+tail)
                if findChain(first, tail, used, answer, poly_dicts):
                    return True
                answer.pop()
            used[s] = False

    if n == 0:
        return first == head

def p61():
    ## generate all 4-digit polygonal numbers. And put into dictionary.
    poly_dicts = []
    for s in xrange(6):
        dct = {}
        for x in polygonGen(s+3):
            if x < 1000: continue
            if x >= 10000: break
            if x%100 > 10:
                if x//100 in dct: dct[x//100].append(x%100)
                else: dct[x//100] = [x%100]
        poly_dicts.append(dct)

    ## search to find a cycle
    used = [False for s in poly_dicts]
    used[0] = True
    answer = []
    for head in poly_dicts[0]:
        for tail in poly_dicts[0][head]:
            answer.append(head*100+tail)
            if findChain(head, tail, used, answer, poly_dicts):
                return sum(answer)
            answer.pop()

if __name__ == '__main__':
    time_start = time()
    print(p61())
    print("Time: {0:.3f}".format(time()-time_start))

