#include "common.h"
#include "mathfuncs.h"

#include <array>

/*

If P2 has i pts left, P1 has j pts left, and P2 is first to move, let p(i, j; T)
denote the probability of P2 winning for a fixed T. By considering all four
possibilities (i.e. P2 heads and P1 heads, P2 heads and P1 tails, ...) we have
the following equation for p(i, j; T):

    p(i, j; T) =  (1/2)(1/2^T) p(i - 2^(T-1), j; T) + (1/2)(1/2^T) p(i - 2^(T-1), j-1; T)
                + (1/2)(1 - 1/2^T) p(i, j-1; T) + (1/2)(1 - 1/2^T) p(i, j; T)

We can rearrange this into a single equation for p(i, j; T). Then if we let
p(i, j) denote the probability of P2 winning if T is always optimally chosen, we
simply just take the maximum over all values of T.

    p(i, j) = max_T { p(i - 2^(T-1), j) + p(i - 2^(T-1), j-1) + (2^T - 1) * p(i, j-1) } / { 2^T + 1 }

The values of p(i, j) can be computed efficiently using dynamic programming.

ANSWER 0.83648556

*/

/* Return ceil(log2(n)) for positive integers n. */
int ceillog2(int n)
{
    n--;
    int i = 0;
    while (n > 0) {
        n >>= 1;
        i++;
    }
    return i;
}

// class to store probabilities
template <size_t size>
struct Probs {
    std::array<std::array<double, size>, size> table;

    Probs()
    {
        // initialize 2d array storing probabilities
        for (int i = 0; i < size; i++) {
            table[i].fill(-1);
        }
    }

    /* Probability of P2 winning if P2 has i pts left, P1 has j pts left, and P2 moves first. */
    double get(int i, int j)
    {
        if (i <= 0) {
            return 1;
        }
        if (j == 0) {
            return 0;
        }
        if (table[i - 1][j - 1] >= 0)  // get(i, j) = table[i-1][j-1] if value is already computed
        {
            return table[i - 1][j - 1];
        }
        // compute new probability
        double max = 0;        // tracks highest probability
        int power_of_two = 1;  // tracks 2^(T-1)
        int T_max = ceillog2(i) + 1;
        for (int T = 1; T <= T_max; T++, power_of_two *= 2) {
            double p =
                (get(i - power_of_two, j) + get(i - power_of_two, j - 1) + (2 * power_of_two - 1) * get(i, j - 1)) /
                (2 * power_of_two + 1);
            if (p > max) {
                max = p;
            }
        }
        table[i - 1][j - 1] = max;
        return max;
    }
};

double p232()
{
    const int size = 100;

    Probs<size> P;
    // generate entire table of needed values
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            (void)P.get(i, j);
        }
    }
    // manually do P1's first move
    return (P.get(size, size) + P.get(size, size - 1)) / 2;
}

int main()
{
    printf("%.8f\n", mf::round(p232(), 8));
}
