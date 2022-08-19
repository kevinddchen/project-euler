#include "common.h"

#include <numeric>

/*

Very similar to Problem 71.

ANSWER 7295372

*/

long p73()
{
    const int limit = 12'000;

    int counts = 0;
    for (int q = 4; q <= limit; q++)
    {
        int p_0 = (int)((q - 1.) / 3.) + 1; // p/q just over 1/3
        for (int p = p_0; p * 2 < q; p++)   // while p/q less than 1/2
        {
            if (std::gcd(p, q) == 1) // check fraction reduced
            {
                counts++;
            }
        }
    }
    return counts;
}

int main()
{
    TIMED(printf("%ld\n", p73()));
}
