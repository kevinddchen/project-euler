#include "common.h"
#include "mathfuncs.h"

#include <functional>
#include <vector>

/*

ANSWER

*/

int M(int k, int n)
{
    // first, precompute the first k primes
    std::vector<int> primes = {2};
    {
        int p = 1;
        while (primes.size() < k) {
            p += 2;
            if (mf::is_prime(p)) {
                primes.push_back(p);
            }
        }
    }

    // next, recurse over all possible collections of integers
    std::vector<int> arr(n);
    int max_sum_p = 0;

    std::function<void(int, int)> recurse;

    // i: index in the array
    // prev_a: previous value in the array
    recurse = [&](int i, int prev_a) -> void {
        if (i == n) {
            int sum_a = 0;
            int sum_p = 0;
            for (int i = 0; i < n; ++i) {
                const int a = arr[i];
                sum_a += a;
                sum_p += primes[a];
            }

            // break if sum(a) not multiple of k
            if (sum_a % k != 0) {
                return;
            }

            for (int i = 0; i < n; ++i) {
                printf("%d ", arr[i]);
            }
            printf("-- %d\n", sum_p);

            if (sum_p > max_sum_p) {
                max_sum_p = sum_p;
            }
        } else {
            for (int a = prev_a; a < k; ++a) {
                arr[i] = a;
                recurse(i + 1, a);
            }
        }
    };

    recurse(0, 0);
    return max_sum_p;
}

long p0()
{
    return M(5, 10);
}

int main()
{
    printf("%ld\n", p0());
}
