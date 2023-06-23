#include "common.h"
#include "mathfuncs.h"

#include <cmath>

/*

At index N, the probability that x_N will be all 1's is,

    P(N) = ( 1 - 2^(-N) )^32

so the probability that N is the first integer where x_N is all 1's is,

    P(N) - P(N-1)

Then we simply calculate the expected value.

    E = sum{i=1} i * (P(i) - P(i-1))

ANSWER 6.3551758451

*/

double p323()
{
    double exp_val = 0;
    double prev_cum = 0;

    for (int N = 1; true; N++) {
        double cum = pow(1 - pow(2, -N), 32);
        double prob = cum - prev_cum;

        if (prob < 1e-13) {
            break;
        }

        exp_val += N * prob;
        prev_cum = cum;
    }
    return exp_val;
}

int main()
{
    TIMED(printf("%.10f\n", mf::round(p323(), 10)));
}
