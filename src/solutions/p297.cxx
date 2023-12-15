#include "common.h"

#include <vector>

/*

Let S(k) be the sum of z(n) for 0 < n < k, i.e. we want to find S(10^17). We
can note two properties of S(k) that can be proven:

1.  S(F_{i+1}) = S(F_i) + S(F_{i-1}) + F_{i-1} for all Fibbonacci numbers F_i.
2.  If k has the Zeckendorf representation k = F_a0 + F_a1 + ... F_an, then
    S(k) =   S(F_a0) + F_a1 + F_a2 + ... + F_an
           + S(F_a1) + F_a2 + F_a3 + ... + F_an
           + ...
           + S(F_a{n-1}) + F_an
           + S(F_an)

Using these two propositions, we can compute S(10^17) quite efficiently.

ANSWER 2252639041804718029

*/

/*
 * Return largest fibonacci number <= the input.
 */
long largest_fibonacci(long x)
{
    assert(x >= 0);

    long curr_fib = 0;
    long next_fib = 1;
    while (next_fib <= x) {
        const long temp = curr_fib + next_fib;
        curr_fib = next_fib;
        next_fib = temp;
    }
    return curr_fib;
}

/*
 * Return the Zeckendorf representation of the input.
 */
std::vector<long> zeckendorf(long x)
{
    std::vector<long> result;
    while (x > 0) {
        const long f = largest_fibonacci(x);
        result.push_back(f);
        x -= f;
    }
    return result;
}

long p297()
{
    const long limit = 100'000'000'000'000'000;

    // Compute Zeckendorf representation of the limit
    const auto fibs = zeckendorf(limit);

    long sum = 0;

    // Compute the partial sum S(F_i) for each F_i in the Zeckendorf representation
    // Then accumulate their sum.
    {
        // Iterate over fibs in reverse order
        auto fib_ptr = fibs.end() - 1;

        long prev_fib = 1;
        long curr_fib = 1;
        long prev_S = 0;
        long curr_S = 0;

        while (fib_ptr >= fibs.begin()) {
            if (*fib_ptr == curr_fib) {
                sum += curr_S;
                fib_ptr--;
            }

            const long next_fib = curr_fib + prev_fib;
            const long next_S = curr_S + prev_S + prev_fib;
            prev_fib = curr_fib;
            curr_fib = next_fib;
            prev_S = curr_S;
            curr_S = next_S;
        }
    }

    // Add the remaining part of the sum
    for (int i = 0; i < fibs.size(); i++) {
        sum += i * fibs[i];
    }

    return sum;
}

int main()
{
    printf("%ld\n", p297());
}
