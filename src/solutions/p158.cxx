#include "common.h"

/*

Can be solved by hand. See PDF for explanation.

ANSWER 409511334375

*/

long p158()
{
    const int num_letters = 26;

    long eulerian = 0;  // Eulerian number A(n, 1)
    // A(n + 1, 1) = n + 2 * A(n, 1)
    long binom = 1;  // Binomial coefficient C(26, n)
    // C(26, n + 1) = C(26, n) * (26 - n) / (n + 1)

    long best_p = 0;
    for (int n = 1; n <= num_letters; n++) {
        eulerian = (n - 1) + 2 * eulerian;
        binom = binom * (num_letters - n + 1) / n;

        const long new_p = eulerian * binom;
        if (new_p > best_p) {
            best_p = new_p;
        }
    }
    return best_p;
}

int main()
{
    printf("%ld\n", p158());
}
