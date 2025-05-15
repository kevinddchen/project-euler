#include <unordered_map>

/*

We can prove by induction that

    S(2n) = -a_n + 4

Therefore, we just need to compute a_5e11, which can be done quite efficiently using the recursive definition of the
sequence if we memoize intermediate computations.

ANSWER -6999033352333308

*/

/**
 * Memoized computation of a_n.
 */
class MemoizedSequence
{
public:
    // base case a_1 = 1
    MemoizedSequence() { cache.emplace(1, 1); }

    long get(long n)
    {
        if (auto it = cache.find(n); it != cache.end()) {
            // cache hit
            return it->second;
        }
        // cache miss; compute using recursion
        long retval;
        if (n % 2 == 0) {
            retval = 2 * get(n / 2);
        } else {
            retval = get((n - 1) / 2) - 3 * get((n + 1) / 2);
        }

        cache.emplace(n, retval);
        return retval;
    }

private:
    std::unordered_map<long, long> cache;
};

long p918()
{
    MemoizedSequence mem;

    // S(1e12) = -a_5e11 + 4
    const long n = 5e11;
    return -mem.get(n) + 4;
}

int main()
{
    printf("%ld\n", p918());
}
