#include "common.h"

#include <array>

/*

If you spend some time to work out the optimal moves, and if we use "s" to
denote "slide" and "h" to denote "hop", then you will find that the sequence
of optimal modes has a pattern:

    n=1     s h s
    n=2     s h s hh s h s
    n=3     s h s hh s hhh s hh s h s

For any n, there are n^2 "h" and 2n "s". Thus, we have the formula

    M(n) = n^2 + 2n

Now we want this to be a triangle number, i.e.

    n^2 + 2n = k(k+1)/2

which can be rearranged into Pell's equation,

    (2n + 2)^2 = (2k + 1)^2 + 7
    => x^2 - 2 y^2 = -7         where x = 2k + 1, y = 2n + 2

For the theory on how to solve Pell's equation, see this:
https://acollectionofelectrons.wordpress.com/2016/11/30/almost-equilateral-triangles-part-ii/
The fundamental solution is (1 + sqrt2). For the Pell equation we have on hand,
there are two "fundamental solutions":

    (5 + 4 sqrt2) , (11 + 8 sqrt2)

All other solutions can be obtained by multiplying by powers of (1 + sqrt2).
All that remains is to check that n and k are integer, i.e. x is odd and y is
even.

ANSWER 2470433131948040

*/

struct PellPair {
    long x;
    long y;

    bool is_valid() const
    {
        // valid when x is odd and y is even
        return (x % 2 == 1) && (y % 2 == 0);
    }

    long get_n() const
    {
        assert(y % 2 == 0);
        return (y / 2) - 1;
    }

    PellPair next() const
    {
        // obtained by (x + y sqrt2) * (1 + sqrt2)
        const PellPair next_pair = {.x = x + 2 * y, .y = x + y};
        return next_pair;
    }
};

long p321()
{
    constexpr int TARGET = 40;

    // keeps track of the smallest unseen solutions of the two families
    std::array<PellPair, 2> sols;
    sols[0] = {.x = 5, .y = 4};
    sols[1] = {.x = 11, .y = 8};

    long sum = 0;
    int count = 0;

    while (count < TARGET) {
        // find the solution with smallest n, i.e. smallest y
        const int idx = sols[0].y < sols[1].y ? 0 : 1;

        // if solution is valid, add its triangle number to the sum
        auto& sol = sols[idx];
        if (sol.is_valid()) {
            sum += sol.get_n();
            ++count;
        }

        // replace the solution with its child
        sols[idx] = sol.next();
    }

    return sum;
}

int main()
{
    printf("%ld\n", p321());
}
