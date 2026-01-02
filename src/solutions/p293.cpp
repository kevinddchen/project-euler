#include "mf/mathfuncs.hpp"

#include <unordered_set>

/*

Generating admissible numbers can be done by DFS through the following graph:
Start with 2. For each element n whose larget prime factor is p, explore n * p
and n * next_prime(p).

ANSWER 2209

*/

/**
 * Node in the graph. Stores an admissible number as `value`, the current
 * prime, and whether the two children have been visited.
 */
struct Node {
    long value;
    int prime;
    bool visited_left_child = false;   // same prime
    bool visited_right_child = false;  // next prime
};

/**
 * Get next prime after `n`.
 */
long next_prime(long n)
{
    n += 1 + (n % 2);  // get next odd number
    while (!mf::is_prime(n)) {
        n += 2;
    }
    return n;
}

/**
 * Generate all admissible numbers < `limit`.
 */
std::vector<long> generate_admissible(long limit)
{
    std::vector<long> admissible = {2};  // return value
    std::vector<Node> stack = {{2, 2}};

    while (!stack.empty()) {
        Node& back = stack.back();

        int prime;
        if (!back.visited_left_child) {
            // try to visit left child
            back.visited_left_child = true;
            prime = back.prime;
        } else if (!back.visited_right_child) {
            // try to visit right child
            back.visited_right_child = true;
            prime = next_prime(back.prime);
        } else {
            // all children visited; go up
            stack.pop_back();
            continue;
        }

        const Node new_node = {back.value * prime, prime};
        if (new_node.value >= limit) {
            // value exceeds limit; go up
            stack.pop_back();
        } else {
            admissible.push_back(new_node.value);
            stack.push_back(new_node);
        }
    }
    return admissible;
}

long p293()
{
    const int limit = 1'000'000'000;

    // first compute all admissible integers
    const std::vector<long> admissibles = generate_admissible(limit);

    // then compute pseudo-Fortunate numbers
    std::unordered_set<long> pseudo_fortunates;
    for (long admissible : admissibles) {
        long m = next_prime(admissible + 1) - admissible;
        pseudo_fortunates.insert(m);
    }

    // compute sum
    long sum = 0;
    for (long m : pseudo_fortunates) {
        sum += m;
    }
    return sum;
}

int main()
{
    printf("%ld\n", p293());
}
