#include "common.h"
#include "mathfuncs.h"

#include <array>

/*

Let L = 1,000,000,000. For a given value of f, the final value after winning k
times is

    value(f, k) = (1 + 2f)^k * (1 - f)^(1000 - k)

The probability of winning k times is

    prob(k) = (1000 choose k) 2^(-1000)

Note that if value(f, k) > L, then value(f, k') > L for any k' > k. In other
words, winning will always give you more money. So the goal is to find the
lowest k such that value(f, k) >= L for some value of f.

First, we maximize the value with respect to f. By taking the derivative of
value(f, k) with respect to f, we can show that it is maximized for

    f = (3k - 1000) / 2000 , where 1000/3 < k < 1000

Plugging this into the equation for value, we get

    log(max value(k)) = k log(1 + (3k - 1000)/1000) + (1000 - k) log(1 - (3k - 1000)/2000)

Then we look for the largest value of k where this is still >= log(L). Once
we know k, we just need to compute the sum of probabilities, prob(k).

ANSWER 0.999992836187

*/


double log_max_value(int n, int k)
{
    double max_f = (3.0 * k - n) / (2.0 * n);
    return k * log(1.0 + 2.0 * max_f) + (n - k) * log(1 - max_f);
}


/**
 * Generate the binomial probability distribution for p=1/2.
 */
template <size_t n>
std::array<double, n + 1> binomial_probs()
{
    // We generate Pascal's triangle for the binomial coefficients. For the
    // probabilities, we just divide by 2 each time we make a new row.
    std::array<double, n + 1> triangle;
    triangle[0] = 1.0f;

    // iterate over rows of Pascal's triangle
    for (int i = 1; i <= n; i++) {
        // for in-place assignment, remember the value we will replace
        double reg = triangle[0];
        triangle[0] = exp2(-i);
        // iterate over elements of each row
        for (int j = 1; j < i; j++) {
            const double sum = reg + triangle[j];
            reg = triangle[j];
            triangle[j] = sum / 2.0;
        }
        triangle[i] = reg / 2.0;
    }

    return triangle;
}

double p267()
{
    constexpr int n = 1000;
    constexpr int limit = 1'000'000'000;

    const auto probs = binomial_probs<n>();

    int k = n;
    while (log_max_value(n, k - 1) > log(limit)) {
        k--;
    }

    // sum from i=k to i=1000
    double sum = 0;
    for (int i = k; i <= n; i++) {
        sum += probs[i];
    }

    return sum;
}

int main()
{
    printf("%.12f\n", mf::round(p267(), 12));
}
