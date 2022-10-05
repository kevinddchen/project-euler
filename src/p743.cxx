#include "common.h"
#include "mathfuncs.h"

/*

Define an n-vector with entries in {0, 1, 2} to be the matrix summed over its
first dimension. Since every window must sum up to k, this n-vector has period
k. If n is divisible by k, then what we need to do is enumerate all k-vectors of
{0, 1, 2} that sum up to k. For instance, if k=3, then we have the possibilities

    (1, 1, 1) , (1, 0, 2) , (1, 2, 0) , (0, 1, 2) , (2, 1, 0) , (0, 2, 1) , (2, 0, 1)

The answer is given by counting the number of combinations, weighted by factors
of 2 since every `1` corresponds to two different choices (either the upper
entry of the matrix is 1 or the lower entry is 1). Explicitly, the answer is

    sum_{p=0}^{k/2} (2^(k-2p))^j (k choose 2p) (2p choose p)

where n = k*j. We also have to calculate the terms of this series efficiently
while preventing overflow.

ANSWER 259158998

*/

long p743()
{
    const int M = 1'000'000'007;
    const int k = 100'000'000;  // window size
    const int j = k;            // n/k

    long term = mf::modular_power(mf::modular_power(2, k, M), j, M);  // p=0 term
    long S = term;

    // multiply by 2^(-2j)
    int power_of_2 = mf::modular_power(mf::modular_inverse(4, M), j, M);

    for (int p = 1; p <= k / 2; p++) {
        term = (term * power_of_2) % M;
        int inv_p = mf::modular_inverse(p, M);
        term = (term * (k - 2 * p + 2)) % M;
        term = (term * (k - 2 * p + 1)) % M;
        term = (term * inv_p) % M;
        term = (term * inv_p) % M;
        S = (S + term) % M;
    }
    return S;
}

int main()
{
    TIMED(printf("%ld\n", p743()));
}
