#include "common.h"
#include "mathfuncs.h"

/*

Let f(n) be the number of compositions of n, so f(n) = 2^(n-1). Let g(n) be the
number of compositions of n with no part equal to 2. It turns out that g(n) can
be computed from the recurrence relation:

    g(n) = g(n-1) + g(n-2) + g(n-4);    g(-1) = 0;   g(0) = g(1) = g(2) = 1

We can think of this as g(1) coming from the set { 1 }, and then subsequent
values of g(n) coming from applying two rules:

    a. Append 1 to the end of a composition of n-1.
    b. Add 2 to the last number in a composition of n-2.
    c. Append 4 to the end of a composition of n-4.

So g(2) comes from { 11 }, g(3) from { 111, 3 }, g(4) from { 1111, 31, 13, 4 }.

The number of palindromes are related to these two functions. For instance, let
us consider 6. Since it is even, the middle number can be 0 (no middle number),
2, or 4.

    middle is 0, compositions of 3 containing 2: f(3) - g(3) = 4 - 2 = 2
        composition 12 --> palindrome (1, 2, 2, 1)
        composition 21 --> palindrome (2, 1, 1, 2)
    middle is 2, compositions of 2: f(2) = 2
        composition 11 -> palindrome (1, 1, 2, 1, 1)
        composition 2 -> palindrome (2, 2, 2)
    middle is 4, compositions of 1 containing 2: f(1) - g(1) = 1 - 1 = 0
    => 4 palindromes

Next, let us consider 7. Since it is odd, the middle number can be 1, 3, or 5.

    middle is 1, compositions of 3 containing 2: f(3) - g(3) = 2
        composition 12 --> palindrome (1, 2, 1, 2, 1)
        composition 21 --> palindrome (2, 1, 2, 1, 2)
    middle is 3, compositions of 2 containing 2: f(2) - g(2) = 1
        composition 2 -> palindrome (2, 3, 2)
    middle is 5, compositions of 1 containing 2: f(1) - f(1) = 0
    => 3 palindromes

Next, consider 8. Middle number can be 0 (no middle), 2, 4, or 6.

    middle is 0, compositions of 4 containing 2: f(4) - g(4) = 8 - 4 = 4
        composition 112 --> palindrome (1, 1, 2, 2, 1, 1)
        composition 121 --> palindrome (1, 2, 1, 1, 2, 1)
        composition 211 --> palindrome (2, 1, 1, 1, 1, 2)
        composition 22 --> palindrome (2, 2, 2, 2)
    middle is 2, compositions of 3: f(3) = 4
        composition 111 --> palindrome (1, 1, 1, 2, 1, 1, 1)
        composition 12 --> palindrome (1, 2, 2, 2, 1)
        composition 21 --> palindrome (2, 1, 1, 1, 2)
        composition 3 --> palindrome (3, 2, 3)
    middle is 4, compositions of 2 containing 2: f(2) - g(2) = 1
        composition 2 -> palindrome (2, 4, 2)
    middle is 6, compositions of 1 containing 2: f(1) - f(1) = 0
    => 9 palindromes

In going from 6 to 7, we added -g(2).
In going from 7 to 8, we added f(4) - g(4) + g(3)

This pattern continues.

ANSWER 1275000

*/

/**
 * Computes the number of compositions of n with no part equal to 2.
 * @param n The number to compute the number of compositions for.
 * @param values The last 4 values of g(n), i.e. values[0] = g(n), values[1] = g(n-1), ...
 * @param mod The modulus to use.
 */
struct CompsNoTwo {
    int n;
    long values[4];
    long mod;

    CompsNoTwo(long mod) : n(1), values{1, 1, 0, -1}, mod(mod) {}

    void next()
    {
        const long next = (values[0] + values[1] + values[3]) % mod;
        values[3] = values[2];
        values[2] = values[1];
        values[1] = values[0];
        values[0] = next;
        n++;
    }
};

/**
 * Computes the number of compositions of n.
 * @param n The number to compute the number of compositions for.
 * @param mod The modulus to use.
 */
long comps(long n, long mod)
{
    return mf::modular_power(2, n - 1, mod);
}

long p710()
{
    const long mod = 1'000'000;
    CompsNoTwo g(mod);

    long N = 3;  // we are computing t(N)
    long total = 0;
    while (true) {
        // going from N odd to even adds f(n) - g(n) + g(n-1) to the total
        g.next();
        total = (total + comps(g.n, mod) - g.values[0] + g.values[1]) % mod;
        N++;

        if (total == 0) {
            break;
        }

        // going from N even to odd adds -g(n-1) to the total
        total = (total - g.values[1] + mod) % mod;
        N++;

        if (total == 0) {
            break;
        }
    }
    return N;
}

int main()
{
    TIMED(printf("%ld\n", p710()));
}
