#include <vector>

/*

We note that since we are summing T(k) over all k-digit numbers, we can
partition the k-digit numbers into sets that are permutations of each other.
Then the sum of T(k) over all elements of a set will be 0 + 1 + 2 + ... +
(n - 1), where n is the size of the partition. This is the (n - 1)th triangle
number.

Instead of generating all partitions, it is more efficient to generate all of
what I will call "collections": unordered and unspecified sets of digits. We
only distinguish whether a digit is non-zero or zero. All 3-digit collections
are:

    aaa: three copies of the same non-zero digit
    aab: two distinct non-zero digits, with 2 and 1 copies
    abc: three distinct non-zero digits, all 1 copy
    aa0: two distinct non-zero digits, all 1 copy, and a zero
    ab0:
    a00:

For each "collection", we can compute (i) the number of orderings, e.g. `aaa`
only has one ordering while `abc` has 6, and (ii) the number of specifications,
e.g. `aaa` has 9 specifications: 111, 222, 333, ..., 999. The number of
orderings gives the size of the partition, and the number of specifications
counts the total number of partitions that match that collection.

ANSWER 6111397420935766740

*/

long factorial(long n)
{
    long prod = 1;
    for (int i = 2; i <= n; ++i) {
        prod *= i;
    }
    return prod;
}

long choose(long n, long k)
{
    // because we use only use small numbers, we can use factorials directly
    return factorial(n) / factorial(k) / factorial(n - k);
}

long triangle(long n)
{
    return n * (n + 1) / 2;
}

/**
 * Represents an unordered and unspecified set of digits, e.g. `aabbc`
 */
struct Collection {
    // Number of `0` digits in the collection
    int zeros;
    // Decreasing sequence of digit multiplicities, e.g. {2, 1} represents `aab`
    std::vector<int> mults;

    // Count the number of distinct digit orderings without leading zeros
    long num_orderings() const
    {
        // first, compute number of digits
        int num_digits = zeros;
        for (int m : mults) {
            num_digits += m;
        }
        // count ways to distribute zeros in the number, without leading zeros
        long zero_factor = choose(num_digits - 1, zeros);
        // count ways to re-order non-zero digits
        long mults_factor = factorial(num_digits - zeros);  // this will never be too big
        for (long m : mults) {
            mults_factor /= factorial(m);
        }
        return zero_factor * mults_factor;
    }

    // Count the number of distinct digit specifications. For the collection
    // `ab`, the specification `a=1,b=2` and `a=2,b=1` are not considered
    // distinct.
    long num_specifications() const
    {
        // first, convert `mults` into run lengths, e.g. {2, 1, 1, 1} -> {1, 3}
        std::vector<int> runs;
        {
            int prev = mults[0];
            int run = 1;
            for (int i = 1; i < static_cast<int>(mults.size()); ++i) {
                if (mults[i] == prev) {
                    ++run;
                } else {
                    runs.push_back(run);
                    prev = mults[i];
                    run = 1;
                }
            }
            runs.push_back(run);
        }
        // start with 9 * 8 * ...
        long num = 1;
        for (int i = 0; i < static_cast<int>(mults.size()); ++i) {
            num *= (9 - i);
        }
        // divide out by factorial of run lengths
        for (long run : runs) {
            num /= factorial(run);
        }
        return num;
    }
};

/**
 * Generate all collections for the given number of digits.
 */
std::vector<Collection> generate_collections(int num_digits)
{
    std::vector<Collection> collections;

    // initial collection containing 1 non-zero digit
    {
        Collection init_c = {.zeros = 0, .mults = {1}};
        collections.push_back(std::move(init_c));
    }

    // the d-digit collections are obtained from the (d-1)-digit collections
    for (int d = 2; d <= num_digits; ++d) {
        std::vector<Collection> new_collections;
        for (auto c : collections) {
            // collection from adding a zero
            {
                Collection new_c = c;
                ++new_c.zeros;
                new_collections.push_back(std::move(new_c));
            }
            if (c.zeros > 0) {
                continue;  // if collection has a zero, do not add any more non-zero digits
            }
            const size_t n = c.mults.size();
            // collection from adding a new distinct digit
            if (n < 9) {
                Collection new_c = c;
                new_c.mults.push_back(1);
                new_collections.push_back(std::move(new_c));
            }
            // collection from adding another copy of the last digit
            if (n == 1 || c.mults[n - 1] < c.mults[n - 2]) {
                Collection new_c = c;
                ++new_c.mults[n - 1];
                new_collections.push_back(std::move(new_c));
            }
        }
        collections = new_collections;
    }

    return collections;
}

long p862()
{
    const int k = 12;

    const auto collections = generate_collections(k);

    long sum = 0;
    for (auto c : collections) {
        sum += triangle(c.num_orderings() - 1) * c.num_specifications();
    }
    return sum;
}

int main()
{
    printf("%ld\n", p862());
}
