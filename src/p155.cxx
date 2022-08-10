#include "common.h"

#include <array>
#include <numeric>
#include <unordered_set>
#include <vector>

/*

All capacitances are created by two operations:

    C1 + C2,    C1 @ C2 = 1/(1/C1 + 1/C2)

If C can be obtained with n unit capacitors, then 1/C can also be obtained with
n unit capacitors. Thus, the set of capacitances that can be obtained with n
unit capacitors can be obtained by taking n `+` operations and arbitrarily many
reciprocals. We keep track of the capacitances inductively for n=1, 2, 3, ...

ANSWER 3857447

*/

// class to handle exact fractions
struct Fraction
{
    int numer;
    int denom;

    Fraction(int numer, int denom) : numer(numer), denom(denom) { reduce(); };

    void reduce()
    {
        const int d = std::gcd(numer, denom);
        numer /= d;
        denom /= d;
    }

    inline Fraction reciprocal() const
    {
        return (Fraction){denom, numer};
    }

    inline bool operator==(const Fraction &other) const
    {
        return numer == other.numer && denom == other.denom;
    }

    inline Fraction operator+(const Fraction &other) const
    {
        return (Fraction){numer * other.denom + denom * other.numer, denom * other.denom};
    }
};

// Fraction hash
template <>
struct std::hash<Fraction>
{
    inline std::size_t operator()(const Fraction &frac) const
    {
        return std::hash<float>{}((float)frac.numer / frac.denom);
    }
};

long p155()
{
    const int limit = 18;
    std::unordered_set<Fraction> set;              // hash map to check if a capacitance has been encountered yet
    std::array<std::vector<Fraction>, limit> list; // list of capacitances for each n

    const Fraction one{1, 1};
    list[0] = {one};
    set.insert(one);

    long sum = 1;
    for (int n = 2; n <= limit; n++)
    {
        // sum capacitances for 1 + (n-1), 2 + (n-2), ...
        for (int i = 1; 2 * i <= n; i++)
        {
            const int j = n - i;
            for (auto f1 : list[i - 1])
            {
                for (auto f2 : list[j - 1])
                {
                    const auto f = f1 + f2;
                    if (set.find(f) == set.end()) // if capacitance not encountered yet
                    {
                        // add f to list
                        list[n - 1].push_back(f);
                        set.insert(f);
                        // add 1/f to list
                        const auto f_rec = f.reciprocal();
                        list[n - 1].push_back(f_rec);
                        set.insert(f_rec);
                    }
                }
            }
        }
        sum += list[n - 1].size();
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p155()));
}
