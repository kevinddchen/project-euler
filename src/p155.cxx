#include <cstdio>
#include <ctime>
#include <numeric>
#include <array>
#include <vector>
#include <unordered_set>

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
    int a;
    int b;

    void reduce()
    {
        int d = std::gcd(a, b);
        a /= d;
        b /= d;
    }

    Fraction reciprocal()
    {
        Fraction out {b, a};
        return out;
    }
};


// Fraction equality
bool operator==(const Fraction &f1, const Fraction &f2)
{
    return (f1.a*f2.b == f1.b*f2.a);
}


// Fraction addition
Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    Fraction out {f1.a*f2.b + f1.b*f2.a, f1.b*f2.b};
    return out;
}


// Fraction hash
template<>
struct std::hash<Fraction>
{
    std::size_t operator()(const Fraction &f) const noexcept
    {
        return std::hash<float>{}((float) f.a / f.b);
    }
};


long p155()
{
    const int limit = 18;
    std::unordered_set<Fraction> set;   // hash map to check if a capacitance has been encountered yet
    std::array<std::vector<Fraction>, limit> list;  // list of capacitances for each n

    Fraction one {1, 1};
    list[0] = {one};
    set.insert(one);

    long S = 1;
    for (int n=2; n<=limit; n++)
    {
        // sum capacitances for 1 + (n-1), 2 + (n-2), ...
        for (int i=1; 2*i<=n; i++)
        {
            int j = n-i;
            for (auto f1 : list[i-1])
            {
                for (auto f2 : list[j-1])
                {
                    auto f = f1 + f2;
                    if (set.find(f) == set.end()) // if capacitance not encountered yet
                    {
                        // add f to list
                        f.reduce();
                        list[n-1].push_back(f);
                        set.insert(f);
                        // add 1/f to list
                        auto f_rec = f.reciprocal();
                        list[n-1].push_back(f_rec);
                        set.insert(f_rec);
                    }
                }
            }
        }
        S += list[n-1].size();
    }
    return S;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p155());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
