#include "common.h"
#include "mathfuncs.h"

/*

Given T_n, we obtain T_{n+1} by the following equivalent procedure:
 1. Let p be the largest power of 2 that is <= n. Find the node with value p.
 2. Increment the value of every node.
 3. For the node found in (1), add a child node with value 1.

As a corollary, starting from T_p where p is a power of 2, in obtaining T_{2p}
every node in T_p will grow exactly 1 child node. The node with value v in T_p
will have value v + p in T_{2p} and the value of the new child node in T_{2p}
will be v.

Thus, if we apply the logic backwards, we can start with a T_p and find the
values of the nodes along the path to a particular node with value v:
  - If v <= p/2, then the node was newly added to T_{p/2} and was attached to a
    node with value v.
  - If v > p/2, then the node corresponds to a node with value v - p/2 in
    T_{p/2}.

ANSWER 2903144925319290239

*/

long p872()
{
    const long n = mf::pow(10, 17);
    const long k = mf::pow(9, 17);

    // p here tracks the tree T_p, and is initialized to the smallest power of 2 > 10^17
    long p = mf::pow(2, 57);
    // since we are working in T_p and not T_n, we need to add an offset to k for the value of the node
    long v = k + (p - n);

    long sum = k;
    while (p > 1) {
        const long p_half = p / 2;
        if (v > p_half) {
            // old leaf corresponding node `v - p_half` of T_{p/2}
            v -= p_half;
        } else {
            // new leaf off of node `v` of T_{p/2}
            // we add the value plus an offset going from T_{p/2} to
            sum += v + n - p_half;
        }
        p = p_half;
    }
    return sum;
}

int main()
{
    printf("%ld\n", p872());
}
