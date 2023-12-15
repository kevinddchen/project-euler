#include "common.h"

#include <unordered_set>

/*

If N is "bipronic", i.e. N = x(x+1)y(y+1), then it is a stealthy number for
    a = xy
    b = (x+1)(y+1)
    c = x(y+1)
    d = (x+1)y
I cannot prove that the inverse is correct, but experimentally it seems so. The
answer is then obtained by simply iterating over these bipronic numbers.

ANSWER 75737353

*/

inline long bipronic(long x, long y)
{
    return x * (x + 1) * y * (y + 1);
}

long p757()
{
    const long limit = 100'000'000'000'000;

    std::unordered_set<long> set;

    long x = 1;
    while (true) {
        long y = x;
        while (true) {
            const long b = bipronic(x, y);
            if (b > limit) {
                if (y == x) {  // no more x's so we are done
                    return set.size();
                }
                break;
            }
            set.insert(b);
            y++;
        }
        x++;
    }

    return set.size();
}


int main()
{
    printf("%ld\n", p757());
}
