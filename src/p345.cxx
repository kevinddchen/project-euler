#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>

/*

This is solved using the Hungarian algorithm, as outlined on Wikipedia. Step
III requires the use of the Hopcroft-Karp algorithm and Konig's theorem to find
the minimal vertex cover of a bipartite graph.

ANSWER: 13938

*/

// Simple tree node.
class Node
{
public:
    Node *parent;
    std::vector<Node *> children;
    int val;
    bool hasParent;

    // Constructor
    Node(int x)
    {
        val = x;
        hasParent = false;
    }

    void add_child(Node *N)
    {
        children.push_back(N);
        N->hasParent = true;
        N->parent = this;
    }
};

Node *find_aug_path(bool **G, bool **M, bool *mark_row, bool *mark_col, int size)
{
    /*

    Find augmenting path using breadth-first-search.
    G - graph represented by connected edges.
    M - current matching.
    mark_row/col - keeps track of free vertices.

    */

    Node *root = new Node(-1);
    std::vector<Node *> row_layer, col_layer;
    std::vector<Node *>::iterator iter;

    // add free rows to tree
    for (int i = 0; i < size; i++)
    {
        if (!mark_row[i])
        {
            Node *N = new Node(i);
            root->add_child(N);
            row_layer.push_back(N);
            N->hasParent = false;
        }
    }

    while (row_layer.size() != 0)
    {
        // build unmatched edges to paths
        col_layer.clear();
        for (iter = row_layer.begin(); iter != row_layer.end(); iter++)
        {
            int i = (*iter)->val;
            for (int j = 0; j < size; j++)
            {
                if (G[i][j] and !M[i][j])
                {
                    Node *N = new Node(j);
                    (*iter)->add_child(N);
                    col_layer.push_back(N);
                }
            }
        }

        // find free column at end of a path
        row_layer.clear();
        for (iter = col_layer.begin(); iter != col_layer.end(); iter++)
        {
            int j = (*iter)->val;
            if (!mark_col[j])
                return *iter;

            // build matched edges to paths
            for (int i = 0; i < size; i++)
            {
                if (G[i][j] and M[i][j])
                {
                    Node *N = new Node(i);
                    (*iter)->add_child(N);
                    row_layer.push_back(N);
                }
            }
        }
    }
    return root;
}

void add_path(Node *N, bool **M, bool *mark_row, bool *mark_col, int size)
{
    /* Add augmenting path to our matching M. */

    int row, col;
    mark_col[N->val] = true;
    while (true)
    {
        col = N->val;
        N = N->parent;
        row = N->val;

        M[row][col] = !M[row][col];

        if (!N->hasParent)
        {
            mark_row[N->val] = true;
            break;
        }

        row = N->val;
        N = N->parent;
        col = N->val;

        M[row][col] = !M[row][col];
    }
}

void find_vert_cover(Node *N, bool *mark_row, bool *mark_col, bool par, int size)
{
    /* Given maximum matching, finds minimum vertex covering, by depth-first-search. */

    std::vector<Node *> children = N->children;
    std::vector<Node *>::iterator iter;

    for (iter = children.begin(); iter != children.end(); iter++)
    {
        if (par)
            mark_row[(*iter)->val] = false;
        else
            mark_col[(*iter)->val] = true;

        find_vert_cover(*iter, mark_row, mark_col, !par, size);
    }
}

long p345()
{
    int const size = 15;

    int M_orig[15][15] = {
        {7, 53, 183, 439, 863, 497, 383, 563, 79, 973, 287, 63, 343, 169, 583},
        {627, 343, 773, 959, 943, 767, 473, 103, 699, 303, 957, 703, 583, 639, 913},
        {447, 283, 463, 29, 23, 487, 463, 993, 119, 883, 327, 493, 423, 159, 743},
        {217, 623, 3, 399, 853, 407, 103, 983, 89, 463, 290, 516, 212, 462, 350},
        {960, 376, 682, 962, 300, 780, 486, 502, 912, 800, 250, 346, 172, 812, 350},
        {870, 456, 192, 162, 593, 473, 915, 45, 989, 873, 823, 965, 425, 329, 803},
        {973, 965, 905, 919, 133, 673, 665, 235, 509, 613, 673, 815, 165, 992, 326},
        {322, 148, 972, 962, 286, 255, 941, 541, 265, 323, 925, 281, 601, 95, 973},
        {445, 721, 11, 525, 473, 65, 511, 164, 138, 672, 18, 428, 154, 448, 848},
        {414, 456, 310, 312, 798, 104, 566, 520, 302, 248, 694, 976, 430, 392, 198},
        {184, 829, 373, 181, 631, 101, 969, 613, 840, 740, 778, 458, 284, 760, 390},
        {821, 461, 843, 513, 17, 901, 711, 993, 293, 157, 274, 94, 192, 156, 574},
        {34, 124, 4, 878, 450, 476, 712, 914, 838, 669, 875, 299, 823, 329, 699},
        {815, 559, 813, 459, 522, 788, 168, 586, 966, 232, 308, 833, 251, 631, 107},
        {813, 883, 451, 509, 615, 77, 281, 613, 459, 205, 380, 274, 302, 35, 805}};

    // copy matrix
    int **M = new int *[size];
    for (int i = 0; i < size; i++)
    {
        M[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            M[i][j] = M_orig[i][j];
        }
    }

    // STEP I: subtract row maximum
    for (int i = 0; i < size; i++)
    {
        int row_max = INT_MIN;
        for (int j = 0; j < size; j++)
            row_max = std::max(row_max, M[i][j]);
        for (int j = 0; j < size; j++)
            M[i][j] -= row_max;
    }

    // STEP II: subtract col maximum
    for (int j = 0; j < size; j++)
    {
        int col_max = INT_MIN;
        for (int i = 0; i < size; i++)
            col_max = std::max(col_max, M[i][j]);
        for (int i = 0; i < size; i++)
            M[i][j] -= col_max;
    }

    bool **graph = new bool *[size];
    bool **match = new bool *[size];
    bool *mark_row = new bool[size]();
    bool *mark_col = new bool[size]();

    for (int i = 0; i < size; i++)
    {
        graph[i] = new bool[size]();
        match[i] = new bool[size]();
    }

    while (true)
    {
        for (int i = 0; i < size; i++)
        {
            mark_row[i] = false;
            mark_col[i] = false;
            for (int j = 0; j < size; j++)
            {
                graph[i][j] = (M[i][j] == 0) ? 1 : 0;
                match[i][j] = 0;
            }
        }

        // STEP III: mark all zeros with fewest number of lines

        // find maximum matching using the Hopcroft-Karp algorithm.
        Node *N;
        while (true)
        {
            N = find_aug_path(graph, match, mark_row, mark_col, size);
            if (!N->hasParent)
                break;
            add_path(N, match, mark_row, mark_col, size);
        }

        // find minimum vertex cover using Konig's theorem.
        for (int i = 0; i < size; i++)
        {
            mark_row[i] = true;
            mark_col[i] = false;
        }

        find_vert_cover(N, mark_row, mark_col, true, size);

        // STEP 4: Select unmarked elements, and subtract max

        int unmark_max = INT_MIN;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (!mark_row[i] and !mark_col[j])
                    unmark_max = std::max(unmark_max, M[i][j]);
            }
        }

        // no unmarked rows
        if (unmark_max == INT_MIN)
            break;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (!mark_row[i])
                    M[i][j] -= unmark_max;
                if (mark_col[j])
                    M[i][j] += unmark_max;
            }
        }
    }

    // find sum
    int S = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (match[i][j] == 1)
                S += M_orig[i][j];
        }
    }
    return S;
}

int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p345());
    t = clock() - t;
    printf("Time: %.3f\n", ((float)t) / CLOCKS_PER_SEC);
}
