#!/usr/bin/python

"""

Here we generate primes with a sieve, and store each pair of primes that they
concantenate to form primes. Each time we find a new pair, we check if we can
create complete 3-graphs with previously remembered pairs, as well as 4-graphs
and 5-graphs. In total it takes ~85s to find the answer, ~50s of which to
generate the primes needed up to 10^8.

The five primes are 8389, 6733, 5701, 5197, and 13.

"""

from time import time
from mathfuncs import primeSieve

SIZE = 5

def add_pair(conn_dicts, p, q):
    if q in conn_dicts[0]: conn_dicts[0][q].append( (p,) )
    else: conn_dicts[0][q] = [ (p,) ]

    ## check for complete graphs.
    for i in xrange(SIZE-2):
        if p in conn_dicts[i]:
            for tup in conn_dicts[i][p]:
                
                all_in = True
                for a in tup:
                    if (a,) not in conn_dicts[0][q]:
                        all_in = False
                        break

                if all_in:
                    if q in conn_dicts[i+1]: conn_dicts[i+1][q].append( (p,)+tup )
                    else: conn_dicts[i+1][q] = [ (p,)+tup ]

def p60():
    conn_dicts = [{} for i in xrange(SIZE-1)]
    d = 2
    while True:
        sieve_ref = [None]
        sieve = primeSieve(10**d, sieve_ref)
        for p in sieve: pass
        S = sieve_ref[0]

        ## generate prime pairs p, q with d total digits
        for p, p_prime in enumerate(S):
            if p==2 or not p_prime: continue
            p_d = len(str(p)) 
            if p_d * 2 > d: continue
            for q in xrange( max(10**(d-p_d-1)+1, p+2), 10**(d-p_d), 2):

                ## if concatenates, add pair to dictionary
                if S[q] and S[int(str(p)+str(q))] and S[int(str(q)+str(p))]:
                    add_pair(conn_dicts, p, q)

        if len(conn_dicts[-1]) != 0:
            M = 10**d
            for p in conn_dicts[-1]:
                for tup in conn_dicts[-1][p]:
                    if p+sum(tup) < M:
                        M = p+sum(tup)
            return M

        d += 1

if __name__ == '__main__':
    time_start = time()
    print(p60())
    print("Time: {0:.3f}".format(time()-time_start))

