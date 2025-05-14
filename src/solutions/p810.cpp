#include <vector>

#include <cassert>

/*

We use a prime sieve to find primes.

If log2(a) is the log base 2 of `a` rounded down to the nearest integer, then
based on the fact that the XOR product does not carry, we can note that the
XOR product of `a` and `b` will be between `a * b` and `2^(log2(a) + log2(b))`.
This observation guides our sieving strategy.

ANSWER 124136381

*/

/**
 * Compute the XOR product of two numbers.
 */
long xor_product(long a, long b)
{
    // faster if a is smaller
    if (a > b) {
        std::swap(a, b);
    }

    long result = 0;
    while (a > 0) {
        if (a & 1) {  // if (a % 2 == 1)
            result ^= b;
        }
        a >>= 1;
        b <<= 1;
    }
    return result;
}

/**
 * Compute the log base 2 of a number, rounded down to the nearest integer.
 */
int log2(long x)
{
    int count = -1;
    while (x > 0) {
        count++;
        x >>= 1;
    }
    return count;
}

/**
 * Find the bound on `b` such that for `b` greater than or equal to this return
 * value, the XOR product of `a` and `b` will be greater than `2^(log2_size)`.
 */
long get_b_limit(long a, int log2_size)
{
    const int log2_a = log2(a);
    const int log2_b = log2_size - log2_a;
    return 1 << log2_b;
}

long p810()
{
    const int target = 5'000'000;

    const int log2_size = 27;
    const int size = 1 << log2_size;  // size of the sieve

    // create prime sieve
    std::vector<bool> sieve(size);
    for (int i = 2; i < size; i++) {
        sieve[i] = true;
    }

    // generate pairs a and b, compute their XOR product
    long a = 2;
    while (true) {
        // compute bounds on b
        const long b_limit = get_b_limit(a, log2_size);
        if (a > b_limit) {
            break;
        }

        // sieve out values
        for (long b = a; b < b_limit; b++) {
            const long product = xor_product(a, b);
            if (product < size) {
                sieve[product] = false;
            }
        }
        a++;
    }

    // find the 5,000,000th prime
    int count = 0;
    for (int i = 2; i < size; i++) {
        if (sieve[i]) {
            count++;
            if (count == target) {
                return i;
            }
        }
    }

    printf("Found %d < %d primes. Increase the sieve size? (current size = 2^%d)\n", count, target, log2_size);
    assert(false);
}

int main()
{
    printf("%ld\n", p810());
}
