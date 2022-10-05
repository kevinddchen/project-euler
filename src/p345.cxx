#include "common.h"

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

/*

This is solved using the Hungarian algorithm, as outlined on Wikipedia:
    https://en.wikipedia.org/wiki/Hungarian_algorithm#Matrix_interpretation
Step 3 requires the use of the Hopcroft-Karp algorithm and Konig's theorem to
find the minimal vertex cover of a bipartite graph.

ANSWER: 13938

*/

// Simple tree node.
struct Node {
    int val;
    Node* parent;
    std::vector<std::unique_ptr<Node>> _children;

    Node(int x) : val(x), parent(nullptr) {}

    /* Transfers ownership of node to the parent. */
    void add_child(std::unique_ptr<Node> N)
    {
        N->parent = this;
        _children.push_back(std::move(N));
    }

    std::vector<Node*> get_children() const
    {
        std::vector<Node*> children;
        for (const auto& child : _children)
            children.push_back(child.get());
        return children;
    }

    inline bool has_parent() const { return parent != nullptr; }
};

/**
 * Find an augmenting path using breadth-first search.
 *
 * G - graph, as adjacency matrix.
 * M - current matching, as adjacency matrix.
 * matched_rows/cols - keeps track of free vertices.
 * root - dummy node to build the BFS graph from.
 *
 * Returns last node in an augmenting path, or null pointer if no augmenting
 * path exists.
 */
template <size_t n_row, size_t n_col>
Node* find_augmenting_path(
    const std::array<std::array<bool, n_col>, n_row>& G,
    const std::array<std::array<bool, n_col>, n_row>& M,
    const std::array<bool, n_row>& matched_rows,
    const std::array<bool, n_col>& matched_cols,
    Node* root)
{
    // printf("ENTER find_augmenting_path\n");

    std::vector<Node*> row_layer, col_layer;

    // add free rows to first layer
    for (int i = 0; i < n_row; i++) {
        if (!matched_rows[i]) {
            auto node = std::make_unique<Node>(i);
            auto node_ptr = node.get();
            root->add_child(std::move(node));
            node_ptr->parent = nullptr;  // `node` is an actual root node, so has no parent
            row_layer.push_back(node_ptr);
        }
    }

    // breadth-first search
    while (row_layer.size() > 0) {
        // traverse all row -unmatched-> col edges
        // if col is free, we are done
        // printf("==row layer==\n");
        col_layer.clear();
        for (Node* row_node : row_layer) {
            int i = row_node->val;
            for (int j = 0; j < n_col; j++) {
                if (G[i][j] && !M[i][j]) {
                    // printf("row %d -> col %d\n", i, j);
                    auto col_node = std::make_unique<Node>(j);
                    auto col_node_ptr = col_node.get();
                    row_node->add_child(std::move(col_node));

                    if (!matched_cols[j]) {
                        // printf("found free col %d\n", j);
                        // printf("EXIT find_augmenting_path\n");
                        return col_node_ptr;
                    }

                    col_layer.push_back(col_node_ptr);
                }
            }
        }

        // find a free column in the last layer
        // else, traverse all col -matched-> row edges
        // printf("==col layer==\n");
        row_layer.clear();
        for (Node* col_node : col_layer) {
            int j = col_node->val;
            for (int i = 0; i < n_row; i++) {
                if (G[i][j] && M[i][j]) {
                    // printf("col %d -> row %d\n", j, i);
                    auto row_node = std::make_unique<Node>(i);
                    auto row_node_ptr = row_node.get();
                    col_node->add_child(std::move(row_node));
                    row_layer.push_back(row_node_ptr);
                }
            }
        }
    }
    // printf("could not find an augmenting path\n");
    // printf("EXIT find_augmenting_path\n");
    return nullptr;
}

/**
 * Modify the matching using an augmenting path.
 *
 * leaf - last node in the path.
 * M - current matching, as adjacency matrix.
 * matched_rows/cols - keeps track of free vertices.
 */
template <size_t n_row, size_t n_col>
void add_path(
    const Node* leaf,
    std::array<std::array<bool, n_col>, n_row>& M,
    std::array<bool, n_row>& matched_rows,
    std::array<bool, n_col>& matched_cols)
{
    // from `leaf`, recursively calling `->parent` gives all vertices in the path
    const Node* col = leaf;
    const Node* row;

    matched_cols[col->val] = true;
    while (true) {
        row = col->parent;
        M[row->val][col->val] = !M[row->val][col->val];  // reverse matching

        if (!row->has_parent()) {
            matched_rows[row->val] = true;
            break;
        }

        col = row->parent;
        M[row->val][col->val] = !M[row->val][col->val];  // reverse matching
    }
}

/**
 * Find a maximum matching, using Hopcroft-Karp algorithm.
 * https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm#Algorithm
 *
 * G - graph, as adjacency matrix.
 * M - current matching, as adjacency matrix.
 * matched_rows/cols - keeps track of free vertices.
 *
 * Returns the graph for Konig's theorem: starting at unmatched vertices, and
 * alternating between unmatched and matched edges.
 */
template <size_t n_row, size_t n_col>
std::unique_ptr<Node> find_maximum_matching(
    const std::array<std::array<bool, n_col>, n_row>& G,
    std::array<std::array<bool, n_col>, n_row>& M,
    std::array<bool, n_row>& matched_rows,
    std::array<bool, n_col>& matched_cols)
{
    while (true) {
        auto root = std::make_unique<Node>(-1);  // dummy node
        Node* leaf = find_augmenting_path<n_row, n_col>(G, M, matched_rows, matched_cols, root.get());

        if (leaf == nullptr)  // no augmenting path has been found
        {
            return root;
        }

        add_path<n_row, n_col>(leaf, M, matched_rows, matched_cols);
    }
}

/**
 * Finds minimum vertex covering, using recursion.
 * https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_(graph_theory)#Constructive_proof_without_flow_concepts
 */
template <size_t n_row, size_t n_col>
void find_minimum_vertex_cover(
    const Node* root, std::array<bool, n_row>& matched_rows, std::array<bool, n_col>& matched_cols, bool parity)
{
    std::vector<Node*> children = root->get_children();

    for (auto child : children) {
        if (parity) {
            matched_rows[child->val] = false;
        } else {
            matched_cols[child->val] = true;
        }

        find_minimum_vertex_cover<n_row, n_col>(child, matched_rows, matched_cols, !parity);
    }
}

long p345()
{
    const int size = 15;

    const int reward[15][15] = {
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

    // make a copy of the reward matrix but with minus signs, so we solve for
    // minimum cost instead
    std::array<std::array<int, size>, size> cost;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cost[i][j] = -reward[i][j];
        }
    }

    // STEP 1: subtract row minimum
    for (int i = 0; i < size; i++) {
        int row_min = INT_MAX;
        for (int j = 0; j < size; j++) {
            row_min = std::min(row_min, cost[i][j]);
        }
        for (int j = 0; j < size; j++) {
            cost[i][j] -= row_min;
        }
    }

    // STEP 2: subtract col minimum
    for (int j = 0; j < size; j++) {
        int col_min = INT_MAX;
        for (int i = 0; i < size; i++) {
            col_min = std::min(col_min, cost[i][j]);
        }
        for (int i = 0; i < size; i++) {
            cost[i][j] -= col_min;
        }
    }

    std::array<std::array<bool, size>, size> graph;
    std::array<std::array<bool, size>, size> maximum_matching;
    std::array<bool, size> matched_rows;
    std::array<bool, size> matched_cols;

    while (true) {
        // STEP 3: find a smallest set of rows and/or columns that contains
        // all zero elements of the cost matrix. Doing this "marks" the rows
        // and columns. This is done by:
        //
        // 1. preparing a bipartite graph between the "row" and "column"
        //    vertices of the cost matrix
        // 2. find a maximum matching using the Hopcroft-Karp algorithm
        // 3. produce the minimum vertex cover using Konig's theorem

        // initialize data structures
        for (int i = 0; i < size; i++) {
            matched_rows[i] = false;
            matched_cols[i] = false;
            for (int j = 0; j < size; j++) {
                graph[i][j] = cost[i][j] == 0;
                maximum_matching[i][j] = false;
            }
        }

        // for (int i = 0; i < size; i++)
        // {
        //     for (int j = 0; j < size; j++)
        //     {
        //         printf("%d ", graph[i][j]);
        //     }
        //     printf("\n");
        // }

        // find maximum matching using the Hopcroft-Karp algorithm.
        auto root = find_maximum_matching<size, size>(graph, maximum_matching, matched_rows, matched_cols);

        // if all rows are matched, then we are done
        bool done = true;
        for (int i = 0; i < size; i++) {
            if (!matched_rows[i]) {
                done = false;
                break;
            }
        }
        if (done) {
            break;
        }

        // find minimum vertex cover using Konig's theorem.
        for (int i = 0; i < size; i++) {
            matched_rows[i] = true;
            matched_cols[i] = false;
        }

        find_minimum_vertex_cover<size, size>(root.get(), matched_rows, matched_cols, true);

        // printf("matched_rows: ");
        // for (auto x : matched_rows)
        // {
        //     printf("%d ", x);
        // }
        // printf("\nmatched_cols: ");
        // for (auto x : matched_cols)
        // {
        //     printf("%d ", x);
        // }
        // printf("\n");

        // STEP 4: Find min of unmarked elements. Subtract this from unmarked
        // elements, and add to elements with marked row _and_ marked column.

        int unmarked_min = INT_MAX;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!matched_rows[i] and !matched_cols[j]) {
                    unmarked_min = std::min(unmarked_min, cost[i][j]);
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!matched_rows[i]) {
                    cost[i][j] -= unmarked_min;
                }
                if (matched_cols[j]) {
                    cost[i][j] += unmarked_min;
                }
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (maximum_matching[i][j] == 1) {
                sum += reward[i][j];
            }
        }
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p345()));
}
