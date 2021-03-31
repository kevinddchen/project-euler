#!/usr/bin/python
#ANSWER 425185

"""

See solution explanations.

"""

from time import time

def directions(i, j, dim):
    if i > 0: yield (i-1, j)
    if j > 0: yield (i, j-1)
    if i < dim-1: yield (i+1, j)
    if j < dim-1: yield (i, j+1)

def p83():
    ## get matrix
    with open('files/matrix.txt', 'r') as fl:
        M = [[int(x) for x in line.strip('\n').split(',')] for line in fl.readlines()]

    dim = len(M)
    ## distance matrix
    ## 0 denotes unknown distance
    D = [[0]*dim for i in xrange(dim)]
    D[0][0] = M[0][0]   ## seed to start

    ## store new nodes 
    node_list = [(0, 0)]

    ## find least path using Dijkstra's algorithm
    while D[-1][-1] == 0:
        ## get node with lowest distance
        s, i, j = sorted([(D[n[0]][n[1]], n[0], n[1]) for n in node_list])[0]
        for x, y in directions(i, j, dim):
            ## update distance to adjacent vertices
            t = M[x][y]
            if D[x][y] == 0: 
                D[x][y] = s+t
                node_list.append( (x, y) )
            else:
                D[x][y] = min(D[x][y], s+t)
        ## mark node as complete
        node_list.remove( (i, j) )

    return D[-1][-1]

if __name__ == '__main__':
    time_start = time()
    print(p83())
    print("Time: {0:.3f}".format(time()-time_start))

