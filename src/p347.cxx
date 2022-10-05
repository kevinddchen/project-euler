#include "common.h"
#include "mathfuncs.h"

#include <algorithm>

/*

Brute force.

ANSWER 11109800204052

*/

long M(long p, long q, long N)
{
    long A, B;
    long ans = 0;

    A = p * q;
    while (A <= N) {
        B = A;
        while (B * q <= N) {
            B *= q;
        }
        ans = std::max(ans, B);
        A *= p;
    }

    return ans;
}

long p347()
{
    const int N = 10'000'000;

    // get primes
    auto sieve = mf::prime_sieve(N / 2);
    std::vector<int> primes;
    for (int i = 0; i < N / 2; i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }

    // calculate M(p, q, N) for primes p < q
    long sum = 0;
    for (auto p_iter = primes.begin(); p_iter != primes.end(); p_iter++) {
        for (auto q_iter = p_iter + 1; q_iter != primes.end(); q_iter++) {
            long M_ans = M(*p_iter, *q_iter, N);
            if (M_ans == 0) {
                break;
            }
            sum += M_ans;
        }
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p347()));
}
