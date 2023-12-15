#include "common.h"
#include "generators.h"

#include <array>
#include <vector>

/*

We use trees, since we only need to keep track of the root node and number of
nodes. For efficiency, we keep the depth of the tree as shallow as possible by
collapsing nodes whenever possible.

ANSWER 2325629

*/

template <size_t size>
int find_root(int j, std::array<int, size>& parents)
{
    std::vector<int> nodes;
    // node is root if parent[node] = node
    while (j != parents[j]) {
        nodes.push_back(j);
        j = parents[j];
    }
    // j is root
    // collapse tree
    for (int n : nodes) {
        parents[n] = j;
    }

    return j;
}

long p186()
{
    const int size = 1'000'000;
    const int threshold = .99 * size;
    const int pm = 524287;
    mf::LaggedFibonacci gen;

    // array keeping track of node parents and number of nodes
    std::array<int, size> parents;
    std::array<int, size> num_nodes;
    for (int j = 0; j < size; j++) {
        parents[j] = j;
        num_nodes[j] = 1;
    }

    long n = 0;
    while (num_nodes[find_root(pm, parents)] < threshold) {
        int a = *gen++;
        int b = *gen++;
        if (a == b) {
            continue;
        }
        n++;
        int a_root = find_root(a, parents);
        int b_root = find_root(b, parents);
        // if roots are different, combine trees, rooted at `a_root`
        if (a_root != b_root) {
            num_nodes[a_root] += num_nodes[b_root];
            parents[b_root] = a_root;
        }
    }

    return n;
}

int main()
{
    printf("%ld\n", p186());
}
