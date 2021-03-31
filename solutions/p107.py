#!/usr/bin/python
#ANSWER 259679

"""

See solution explanations.

"""

from time import time

def merge_trees(forest, t1, t2):
    for i in range(len(forest)):
        if forest[i] == t1 or forest[i] == t2:
            forest[i] = min(t1, t2)

def p107():
 ## get edges and store in list
    edges = []
    with open('files/network.txt', 'r') as fl:
        for i, line in enumerate(fl.readlines()):
            for j, x in enumerate(line[:-1].split(',')):
                if j > i and x != '-':
                    edges.append( (int(x), i, j) )
    forest = list(range(i+1))
    initial_weight = sum(e[0] for e in edges)

## add edges in increasing order, skiping if part of the same forest
    edges.sort()
    minimal_weight = 0
    for weight, v1, v2 in edges:
        if forest[v1] != forest[v2]:
            merge_trees(forest, forest[v1], forest[v2])
            minimal_weight += weight
            if sum(forest) == 0:        ## all trees have merged
                break

    return initial_weight - minimal_weight

if __name__ == '__main__':
    time_start = time()
    print(p107())
    print("Time: {0:.3f}".format(time()-time_start))

