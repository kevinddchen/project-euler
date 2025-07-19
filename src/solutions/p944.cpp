#include <mf/mathfuncs.hpp>

/*

Considering the example S(10), the subsets where 1 is an elevisor are all non-empty combinations of {2, 3, ..., 10}.
There are 2^9 - 1 such subsets. The subsets where 2 is an elevisor are all non-empty combinations of {4, 6, 8, 10} times
all combinations of {1, 3, 5, 7, 9}. There are (2^4 - 1) * 2^5 such subsets.

This generalizes to the following formula for general N:

    S(N) = sum_{n=1}^N [ n * ( 2^{N//n - 1} - 1 ) * 2^{N - N//n} ]

The only difficulty is trying to explicitly sum this for N=1e14. The trick is to split the sum into one over
n = 1, 2, 3, ..., 1e7 - 1 and a second one over n = 1e7, 1e7 + 1, ... 1e14. The second sum is more easier parametrized
by the values of N//n instead. So in some sense, we are "meeting in the middle".

ANSWER 1228599511

*/

constexpr long MOD = 1234567891;


long p944()
{
    constexpr long N = 1e14;

    const long sqrt_N = std::sqrt(N);
    const long neg_2 = mf::modular_inverse(2, MOD);

    long sum = 0;

    // sum for all n = 1, 2, ..., sqrt(N) - 1
    for (long n = 1; n < sqrt_N; ++n) {
        const long a = mf::modular_power(2, N / n - 1, MOD) - 1;
        const long b = mf::modular_power(2, N - N / n, MOD);

        long term = n;
        term = mf::modular_product(term, a, MOD);
        term = mf::modular_product(term, b, MOD);

        sum = (sum + term) % MOD;
    }

    // sum for all n = sqrt(N), sqrt(N) + 1, ..., N
    for (long N_div_n = sqrt_N; N_div_n > 1; --N_div_n) {
        // first, find all n such that N / n == N_div_n
        long min_n = N / (N_div_n + 1);
        while (N / min_n > N_div_n) {
            ++min_n;
        }

        long max_n = N / N_div_n;
        while (N / max_n < N_div_n) {
            --max_n;
        }

        const long a = mf::modular_power(2, N_div_n - 1, MOD) - 1;
        const long b = mf::modular_power(2, N - N_div_n, MOD);

        // Note that n + (n+1) + (n+2) + ... + m = (m + n) * (m - n + 1) / 2
        long term = (max_n + min_n) % MOD;
        term = mf::modular_product(term, (max_n - min_n + 1) % MOD, MOD);
        term = mf::modular_product(term, neg_2, MOD);
        term = mf::modular_product(term, a, MOD);
        term = mf::modular_product(term, b, MOD);

        sum = (sum + term) % MOD;
    }

    return sum;
}

int main()
{
    printf("%ld\n", p944());
}
