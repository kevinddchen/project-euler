#include <mf/mathfuncs.hpp>

/*

We use depth first search to traverse the de Bruijn graph. The graph has 2^N
vertices, which are enumerated from 0 to 2^N - 1.

ANSWER 209110240768

*/

/**
 * Generate the next two vertices in the de Bruijn graph.
 */
inline std::pair<int, int> next_vertices(int current_vertex, int num_vertices)
{
    current_vertex = (current_vertex << 1) % num_vertices;
    return {current_vertex, current_vertex + 1};
}

/**
 * Given a de Bruijn sequence, compute its encoding as a number, as described
 * in the problem statement.
 */
inline int sequence_encoding(const std::vector<int>& path, int N)
{
    int encoding = 0;
    for (int i = 0; i < static_cast<int>(path.size()) - (N - 1); i++) {  // disregard last N - 1 vertices
        encoding = (encoding << 1) + (path[i] & 1);                      // shift and add last bit of each vertex
    }
    return encoding;
}

long p265()
{
    const int N = 5;
    const int num_vertices = mf::pow(2, N);

    // table keeping track of visited vertices
    // NOTE: be careful of vector<bool> on Mac; use vector<char> when debugging
    std::vector<bool> visited(num_vertices, false);
    // path of traversed vertices
    std::vector<int> path;
    path.reserve(num_vertices);
    // at each point along the path, keep track of unexplored vertices
    std::vector<std::vector<int>> unexplored(num_vertices);

    // all sequences start with 0
    unexplored[0].push_back(0);
    int current_vertex = -1;  // dummy value

    long sum = 0;
    while (true) {
        if (static_cast<int>(path.size()) < num_vertices && !unexplored.at(path.size()).empty()) {
            // descend graph
            current_vertex = unexplored.at(path.size()).back();
            unexplored.at(path.size()).pop_back();
            visited.at(current_vertex) = true;
            path.push_back(current_vertex);

            // add new vertices to unexplored
            const auto [v1, v2] = next_vertices(current_vertex, num_vertices);
            if (static_cast<int>(path.size()) == num_vertices) {
                if (v1 == 0 || v2 == 0) {
                    // found a Hamiltonian cycle
                    sum += sequence_encoding(path, N);
                }
            } else {
                if (!visited[v1]) {
                    unexplored.at(path.size()).push_back(v1);
                }
                if (!visited[v2]) {
                    unexplored.at(path.size()).push_back(v2);
                }
            }
        } else {
            // backtrack
            visited.at(current_vertex) = false;
            path.pop_back();
            current_vertex = path.back();

            if (path.empty()) {
                break;
            }
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p265());
}
