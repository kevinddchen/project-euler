#include "common.h"

/*

Can be solved by hand. See PDF for explanation.

ANSWER 371048281

*/

int P(int m)
{
    double product = 1;
    for (int j = 1; j <= m; j++) {
        product *= pow(2 * j / (m + 1.), j);
    }
    return (int)product;
}

long p190()
{
    long sum = 0;
    for (int m = 2; m <= 15; m++) {
        sum += P(m);
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p190()));
}
