#include "mf/mathfuncs.hpp"

#include <memory>
#include <vector>

/*

We start by computing the bit representation of each prime number and putting
them into a binary tree, e.g. the left branch is a '0' bit and the right branch
is a '1' bit.

Once we have a tree, we note that at any node of the tree, the optimal strategy
is to pick the bit with most primes down that branch. For instance, if a node
has n0 primes down the '0' branch and n1 primes down the '1' branch, then the
optimal choice is the larger of n0 and n1. This is because since all primes are
uniformly distributed, the probability of the drawn prime number being in the
'0' branch is n0 / (n0 + n1).

If the probabilities of the branches are p0 and p1, respectively, then the
expected score for the node can be written in terms of the expected scores of
the child nodes:

    E(node) = p0 * E(0) + p1 * E(1) + max(p0, p1)

This can be computed via depth-first traversal.

ANSWER 14.97696693

*/

static const double UNSET_EXPECTED_SCORE = -1.0;

/**
 * Convert a number to a vector of bits, least significant bit first.
 */
std::vector<char> convert_to_bits(int n)
{
    std::vector<char> bits;
    while (n > 0) {
        bits.push_back(n & 1);
        n >>= 1;
    }
    return bits;
}

/**
 * Node in a binary tree.
 *
 * @param num_primes Number of primes in the subtree rooted at this node.
 * @param expected_score Expectation value of the score one would get using the
 * optimal strategy from this node: pick the bit with the highest probability.
 * @param zero Pointer to the child node with a 0 bit.
 * @param one Pointer to the child node with a 1 bit.
 */
struct Node {
    int num_primes = 0;
    double expected_score = UNSET_EXPECTED_SCORE;
    std::unique_ptr<Node> zero = nullptr;
    std::unique_ptr<Node> one = nullptr;
};

/**
 * Insert a prime number into the tree rooted at `root` and update the
 * `num_primes` field of each node in the path to the leaf.
 */
void insert_prime(Node* root, int prime)
{
    const std::vector<char> bits = convert_to_bits(prime);

    Node* current = root;
    current->num_primes++;
    for (char b : bits) {
        if (b == 0) {
            if (!current->zero) {
                current->zero = std::make_unique<Node>();
            }
            current = current->zero.get();
        } else {
            if (!current->one) {
                current->one = std::make_unique<Node>();
            }
            current = current->one.get();
        }
        current->num_primes++;
    }
}

double p869()
{
    const int limit = 1e8;

    // generate primes up to `limit`
    std::vector<int> primes;
    {
        const std::vector<bool> sieve = mf::prime_sieve(limit);
        for (int i = 2; i < limit; ++i) {
            if (sieve[i]) {
                primes.push_back(i);
            }
        }
    }

    // construct tree
    std::unique_ptr<Node> root = std::make_unique<Node>();
    for (long prime : primes) {
        insert_prime(root.get(), prime);
    }

    // compute expected scores via DFS
    std::vector<Node*> stack = {root.get()};
    while (!stack.empty()) {
        Node* current = stack.back();

        // check that both children have computed expectation values. if not,
        // add child to stack and continue DFS
        if (current->zero && current->zero->expected_score == UNSET_EXPECTED_SCORE) {
            stack.push_back(current->zero.get());
            continue;
        }
        if (current->one && current->one->expected_score == UNSET_EXPECTED_SCORE) {
            stack.push_back(current->one.get());
            continue;
        }

        // we can compute the expectation value for the current node:
        // E(current) = p0 * E(0) + p1 * E(1) + max(p0, p1)

        // NOTE: the denominators for p0 and p1 should be the `num_primes` of
        // the current node since it could be a prime itself
        current->expected_score = 0.0;
        double p0 = 0.0;
        double p1 = 0.0;
        if (current->zero) {
            p0 = static_cast<double>(current->zero->num_primes) / static_cast<double>(current->num_primes);
            current->expected_score += p0 * current->zero->expected_score;
        }
        if (current->one) {
            p1 = static_cast<double>(current->one->num_primes) / static_cast<double>(current->num_primes);
            current->expected_score += p1 * current->one->expected_score;
        }
        current->expected_score += std::max(p0, p1);
        stack.pop_back();
    }

    return root->expected_score;
}

int main()
{
    printf("%.8f\n", mf::round(p869(), 8));
}
