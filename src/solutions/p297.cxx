#include "common.h"

#include <vector>

/*

We first note some properties of z(n):

 -  z(F_n) = 1, where F_n is the nth Fibonacci number
 -  z(F_n + i) = 1 + z(i), where F_n < F_n + i < F_{n+1}

Let S(k) be the sum of z(n) for 0 < n < k, i.e. we want to find S(10^17). We
can derive a useful recurrence relation for S(k):

    S(F_{n+1}) = S(F_n) + z(F_n) + z(F_n + 1) + z(F_n + 2) + ... + z(F_{n+1} - 1)
               = S(F_n) + z(1) + z(2) + ... + z(F_{n+1} - F_n - 1) + F_{n+1} - F_n
               = S(F_n) + S(F_{n-1}) + F_{n-1}

In general, if k has the Zeckendorf representation k = F_a0 + F_a1 + ... F_an, then
    S(k) =   S(F_a0) + F_a1 + F_a2 + ... + F_an
           + S(F_a1) + F_a2 + F_a3 + ... + F_an
           + ...
           + S(F_a{n-1}) + F_an
           + S(F_an)

Using this recurrence relation, we can compute S(10^17) quite efficiently
knowing its Zeckendorf representation.

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
