#include "common.h"
#include "mathfuncs.h"

/*

Wilson's Theorem states that for prime p, we have (p-1)! = -1 (mod p). Thus we
can deduce that (p-2)! = 1, (p-3)! = -1/2, (p-4)! = 1/6, and (p-5)! = -1/24 (mod
p). Fractions are to be interpreted as modular inverses, since Z_p is a field.
Thus S(p) = -3/8 (mod p).

ANSWER 139602943319822

*/

long p381()
{
    const int size = 100'000'000;
    auto sieve = prime_sieve(size);

    long sum = 0;
    for (long i = 2; i < size; i++)
    {
        if (sieve[i])
        {
            long n = (-3 * modular_inverse(8, i)) % i;
            if (n < 0)
            {
                n += i;
            }
            sum += n;
        }
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p381()));
}
