#include "common.h"
#include "mathfuncs.h"

/*

We use inclusion-exclusion to count the number of squarefree numbers. We first
compute the squares of all primes up to 2^25. Then, the squarefree numbers are
those excluding the following multiples:

    4, 8, 12, 16, 20, 24, 28, 32, 36, 40, ...
    9, 18, 27, 36, 45, ...
    25, 50, 75, ...

But note that we have double-counted the multiples of 4*9, 4*25, 9*25, ... Thus
these must be added back in. But this over subtracts the multiples of 4*9*25,
so we add these back in. And so on. This logic is implemented in the `recurse`
function.

ANSWER 684465067343069

*/

/**
 * Recursively count the number of squarefree numbers.
 * @param squares The squares of all primes up to 2^25.
 * @param quotient The current quotient of 2^50 by some product of squared
 * primes.
 * @param index The current index into `squares`. We only consider further
 * dividing `quotient` by indices greater than or equal to this.
 * @return
 */
long recurse(const std::vector<long>& squares, long quotient, int index = 0)
{
    long count = quotient;
    for (int i = index; i < squares.size(); ++i) {
        const long new_quotient = quotient / squares[i];
        if (new_quotient == 0) {
            break;  // short-circuit for speed
        }
        count -= recurse(squares, new_quotient, i + 1);  // minus sign for inclusion-exclusion
    }
    return count;
}

long p193()
{
    const int limit_log_2 = 50;

    const long limit = 1l << limit_log_2;              // 2^50
    const long prime_limit = 1l << (limit_log_2 / 2);  // sqrt(2^50)

    // First, compute squares of all primes up to `prime_limit`
    std::vector<long> squares;
    {
        const std::vector<bool> sieve = mf::prime_sieve(prime_limit);
        for (long i = 2; i < prime_limit; ++i) {
            if (sieve[i]) {
                squares.push_back(i * i);
            }
        }
    }

    // Then, recursively count squarefree numbers
    const long count = recurse(squares, limit - 1);
    return count;
}

int main()
{
    printf("%ld\n", p193());
}
