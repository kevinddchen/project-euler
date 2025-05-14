#include <mf/mathfuncs.hpp>

#include <algorithm>
#include <vector>

/*

First, we note that
  - the product of two Hamming numbers is Hamming.
  - the totient of a Hamming number is Hamming.

For general n, if we separate n = h * m where h is Hamming and m contains prime
factors greater than 5, then phi(n) = phi(h) * phi(m). For this to be Hamming,
we need phi(m) to be Hamming. If we look at the formula for computing phi from
the prime factorization, we see that this is only possible if m contains
simple powers of primes (i.e. exponents = 1) and for each prime p in the prime
factorization, that p - 1 is Hamming.

Thus, our method is the following:
 1. Generate all Hamming numbers up to the limit
 2. Find all primes p where p - 1 is a Hamming number. The easiest way to do
    this is to just check the primarily of the Hamming numbers found in (1),
    since they get sparser and sparser at higher limits.
 3. Compute all products of these primes.
 4. Compute all products of the numbers found in (1) and (3). Sum these.

ANSWER 939087315

*/

/**
 * Generate all Hamming numbers not exceeding the limit, sorted.
 */
std::vector<long> generate_hamming(long limit)
{
    std::vector<long> list;

    // loop through all possible products
    for (long prod_2 = 1; prod_2 <= limit; prod_2 *= 2) {
        for (long prod_3 = prod_2; prod_3 <= limit; prod_3 *= 3) {
            for (long prod_5 = prod_3; prod_5 <= limit; prod_5 *= 5) {
                list.push_back(prod_5);
            }
        }
    }

    std::sort(list.begin(), list.end());

    return list;
}

long p516()
{
    const long limit = 1e12;
    const long mod = mf::pow(2, 32);

    // first, generate all Hamming up to the limit
    const auto hamming = generate_hamming(limit);

    // for each Hamming number, check if +1 is a prime
    std::vector<long> primes;
    for (auto h : hamming) {
        const long p = h + 1;
        if (mf::is_prime(p) && p > 5 && p <= limit) {
            primes.push_back(p);
        }
    }

    // generate all products between primes
    std::vector<long> products = {1};
    for (auto p : primes) {
        // append to `products` p time each element
        const size_t prev_size = products.size();
        for (int i = 0; i < prev_size; ++i) {
            const long prod = products[i] * p;
            if (prod > limit) {
                break;  // can break because `products` is sorted
            }
            products.push_back(prod);
        }
        // re-sort `products`
        std::sort(products.begin(), products.end());
    }

    // multiply each product with each Hamming number. sum all these up
    long sum = 0;
    for (auto prod : products) {
        for (auto h : hamming) {  // NOTE: binary search would be faster here, but this is not the bottleneck
            const long n = prod * h;
            if (n > limit) {
                break;
            }
            sum = (sum + n) % mod;
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p516());
}
