#include <cstdio>
#include <ctime>
#include <vector>


/*

We use trees, since we only need to keep track of the root node and number of
nodes. For efficiency, we keep the depth of the tree as shallow as possible by
collapsing nodes whenever possible.

ANSWER 2325629

*/


struct LaggedFibGen
{
    int buffer[55];
    int jmod55;     // j = k-1

    LaggedFibGen()
    {
        for (int j=0; j<55; j++)
            buffer[j] = (100003L - 200003L*(j+1) + 300007L*(j+1)*(j+1)*(j+1)) % 1000000;
        jmod55 = 0;
    }

    int next()
    {
        int return_val = buffer[jmod55];
        buffer[jmod55] = (buffer[jmod55] + buffer[(jmod55+31)%55]) % 1000000;
        jmod55 = (jmod55 + 1) % 55;
        return return_val;
    }
};


int find_root(int j, int * parents)
{
    std::vector<int> nodes;
    // node is root if parent[node] = node
    while (j != parents[j])
    {
        nodes.push_back(j);
        j = parents[j];
    }
    // j is root
    // collapse tree
    for (int n : nodes)
        parents[n] = j;
    return j;
}


long p186()
{
    const int size = 1'000'000;
    const int threshold = .99 * size;
    const int pm = 524287;
    LaggedFibGen gen;

    // array keeping track of node parents and number of nodes
    int * parents = new int[size];
    int * num_nodes = new int[size];
    for (int j=0; j<size; j++)
    {
        parents[j] = j;
        num_nodes[j] = 1;
    }

    long n = 0;
    while (num_nodes[find_root(pm, parents)] < threshold)
    {
        int a = gen.next();
        int b = gen.next();
        if (a == b)
            continue;
        n++;
        int a_root = find_root(a, parents);
        int b_root = find_root(b, parents);
        // if roots are different, combine trees, rooted at `a_root`
        if (a_root != b_root)
        {
            num_nodes[a_root] += num_nodes[b_root];
            parents[b_root] = a_root;
        }
    }

    return n;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p186());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
