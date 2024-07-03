#include "common.h"

#include <algorithm>
#include <vector>

/*

ANSWER

*/

long f(long x)
{
    // get non-zero digits of x
    std::vector<long> digits;
    while (x > 0) {
        const auto dv = std::div(x, 10L);
        if (dv.rem != 0) {
            digits.push_back(dv.rem);
        }
        x = dv.quot;
    }
    // sort the digits
    std::sort(digits.begin(), digits.end());
    // from sorted digits, form the number
    long result = 0;
    for (auto digit : digits) {
        result = 10 * result + digit;
    }
    return result;
}

long p0()
{
    long sum = 0;
    for (long i = 1; i < 100000; ++i) {
        // printf("f(%ld) = %ld\n", i, f(i));
        sum += f(i);
    }
    return sum;
}

int main()
{
    printf("%ld\n", p0());
}
