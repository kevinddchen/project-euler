#include <mf/mathfuncs.hpp>

/*

For each cube-full number n, it contributes floor(10^18 / n) to the sum. Thus,
we just need to iterate through all cube-full numbers.

This can be done by considering the following binary tree: each node is a pair
(product, prime). The root node is (1, 2). The left child is (product * prime,
prime) or (product * prime^3, prime) depending on if `product` is divisible by
`prime`, and the right child is (product, next_prime). We can efficiently
traverse the entire tree via depth-first search. This tree is illustrated
below.

            (1, 2)
         /         \
    (8, 2)         (1, 3)
    /    \         /    \
(16, 2) (8, 3) (27, 3) (1, 5)
  / \     / \     / \    / \

It is important to traverse this tree iteratively, since recursion is too slow.

ANSWER 1339784153569958487

*/

/**
 * Returns a vector of all primes less than `size`.
 */
std::vector<long> get_primes(int size)
{
    const auto sieve = mf::prime_sieve(size);

    std::vector<long> primes;
    for (long i = 2; i < size; ++i) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

/**
 * Check if a * b <= c. Safe against overflow.
 */
bool check_limit(long a, long b, long c)
{
    // to avoid overflow, do crude check with floats
    const float af = a;
    const float bf = b;
    const float cf = c;
    // multiply by 1.1 to account for rounding errors
    return (af * bf <= cf * 1.1) && (a * b <= c);
}

struct Node {
    long product;
    int prime_idx;
};

/**
 * Iterate through all cube-full numbers n via depth-first search. Returns the
 * sum of all floor(limit / n).
 */
long dfs(long limit, const std::vector<long> primes)
{
    long sum = 0;

    std::vector<Node> stack;
    stack.push_back({1, 0});

    while (!stack.empty()) {
        const Node node = stack.back();
        stack.pop_back();

        // left child: multiply by p or p^3
        long p = primes[node.prime_idx];
        if (node.product % p != 0) {
            p = p * p * p;
        } else {
            // `node.product` is a newly encountered cube-full number
            sum += limit / node.product;
        }

        if (!check_limit(node.product, p, limit)) {
            continue;
        }

        const Node left_child = {node.product * p, node.prime_idx};
        stack.push_back(left_child);

        // right child: next prime
        if (node.prime_idx + 1 < primes.size()) {
            const Node right_child = {node.product, node.prime_idx + 1};
            stack.push_back(right_child);
        }
    }
    return sum;
}

long p694()
{
    const long limit = 1'000'000'000'000'000'000;
    const long size = std::cbrt(limit) + 1;

    const std::vector<long> primes = get_primes(size);

    const long sum = limit + dfs(limit, primes);  // add limit since 1 is cube-full

    return sum;
}

int main()
{
    printf("%ld\n", p694());
}
