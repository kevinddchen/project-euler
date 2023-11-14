#include "common.h"

/*

Brute force. Iterate through all square roots.

ANSWER 128088830547982

*/

bool recurse(long target, long digits)
{
    long x = 0;
    long multiple_of_10 = 1;
    if (target > digits) {
        return false;
    }
    if (target == digits) {
        return true;
    }
    while (target >= x) {
        x += multiple_of_10 * (digits % 10);
        digits /= 10;
        multiple_of_10 *= 10;
        if (recurse(target - x, digits)) {
            return true;
        }
    }
    return false;
}

long p719()
{
    const long sqrtN = sqrt(1'000'000'000'000);
    long T = 0;

    for (long sqrtS = 2; sqrtS <= sqrtN; sqrtS++) {
        long S = sqrtS * sqrtS;
        if (recurse(sqrtS, S)) {
            T += S;
        }
    }
    return T;
}

int main()
{
    TIMED(printf("%ld\n", p719()));
}
