#include <mf/mathfuncs.hpp>

/*

We keep track of the number of integers whose digits sum to `i`. This
information can be represented by an array, whose ith element equals the number
of integers whose digits sum to i. This array can be generated for all integers
in the ranges 0-9, 0-99, 0-999, ...

Given a specific target n = 10^18, we can do a long-division-like algorithm to
go through the arrays generated above to zero-in onto the corresponding D. For
instance, below is the example for n = 61.

0-99 has 37 integers whose digits sum to a prime.
100-199 has 36 integers whose digits sum to a prime. This is too many.

100-109 has 4 integers whose digits sum to a prime. We now have 41 integers.
110-119 has 5 integers whose digits sum to a prime. We now have 46 integers.
120-129 has 4 integers whose digits sum to a prime. We now have 50 integers.
130-139 has 4 integers whose digits sum to a prime. We now have 54 integers.
140-149 has 4 integers whose digits sum to a prime. We now have 58 integers.
150-159 has 3 integers whose digits sum to a prime. This is too many.
151 has digits that sum to a prime. We now have 59 integers.
155 has digits that sum to a prime. We now have 60 integers.
157 has digits that sum to a prime. We now have 61 integers. We are done.

ANSWER 45009328011709400

*/

/**
 * Sum over array[i] where i + shift is prime.
 */
template <typename T>
T sum_at_prime_indices(const std::vector<T>& array, int shift)
{
    T sum = 0;

    // generating a sieve every call is not ideal--improve if too slow
    const std::vector<bool> sieve = mf::prime_sieve(array.size() + shift);
    for (int i = 0; i < static_cast<int>(array.size()); i++) {
        if (sieve[i + shift]) {
            sum += array[i];
        }
    }

    return sum;
}

/**
 * Add src to dest by performing dest[i + shift] += src[i].
 */
void add(std::vector<long>& dest, const std::vector<long>& src, int shift)
{
    // index exists in `dest` and `src`
    const int index_limit = std::min(src.size(), dest.size() - shift);
    for (int i = 0; i < index_limit; i++) {
        dest[i + shift] += src[i];
    }
    // index does not exist in `dest`
    assert(index_limit >= 0);  // check just in case
    dest.insert(dest.end(), src.begin() + index_limit, src.end());
}

long p845()
{
    const long n = 10'000'000'000'000'000;

    // the ith index holds the number of integers whose digits sum to i
    std::vector<long> digitsum_to_count = {1};

    int multiple = 1;  // `digitsum_to_count` is for integers 0 to multiple * 10^(power_of_ten) - 1
    int power_of_ten = 0;
    long count = 0;  // number of integers in `digitsum_to_count` whose digits sum to a prime

    // first element is {1}
    // second element is `digitsum_to_count` for integers 0-9
    // third element is `digitsum_to_count` for integers 0-99
    // ...
    std::vector<std::vector<long>> base_counts = {digitsum_to_count};

    // ========================================================================
    // first, generate `base_counts` until we arrive at the first
    // `digitsum_to_count` whose sum at prime indices exceeds `n`

    while (true) {
        // attempt to increment `multiple` by adding to `digitsum_to_count`. if this makes us exceed `n`, break
        const long add_to_count = sum_at_prime_indices(base_counts[power_of_ten], multiple);
        if (count + add_to_count >= n) {
            break;
        }
        count += add_to_count;
        add(digitsum_to_count, base_counts[power_of_ten], multiple);
        multiple++;

        // if multiple = 0, we have a new element of `base_counts`
        if (multiple == 10) {
            base_counts.push_back(digitsum_to_count);
            multiple = 1;
            power_of_ten++;
        }
    }

    // ========================================================================
    // second, zero-in on `n` using the `base_counts` we generated. This is
    // done by going through the powers of ten in `base_counts` in reverse
    // order

    long D = multiple * mf::pow(10, power_of_ten);
    int base_shift = multiple;  // this is the cummulative sum of all multiples encountered

    for (int k = power_of_ten - 1; k >= 0; k--) {
        // this loop is very similar to the first loop above, but we go through
        // all smaller powers of ten, which we denote `k`, with respective
        // multiples, which we denote `m`.

        int m = 0;

        while (true) {
            // attempt to increment `m`. if this makes us exceed `n`, break
            const long add_to_count = sum_at_prime_indices(base_counts[k], base_shift + m);
            if (count + add_to_count >= n) {
                break;
            }
            count += add_to_count;
            m++;
        }

        D += m * mf::pow(10, k);
        base_shift += m;
    }

    return D;
}

int main()
{
    printf("%ld\n", p845());
}
