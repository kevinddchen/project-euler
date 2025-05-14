#include <mf/containers.hpp>
#include <mf/hash.hpp>

#include <array>
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

long p155()
{
    const int limit = 18;

    std::unordered_set<mf::Frac> set;               // hash map to check if a capacitance has been encountered yet
    std::array<std::vector<mf::Frac>, limit> list;  // list of capacitances for each n

    mf::Frac one{1, 1};
    list[0] = {one};
    set.insert(one);

    long sum = 1;
    for (long n = 2; n <= limit; n++) {
        // sum capacitances for 1 + (n-1), 2 + (n-2), ...
        for (long i = 1; 2 * i <= n; i++) {
            long j = n - i;
            for (auto f1 : list[i - 1]) {
                for (auto f2 : list[j - 1]) {
                    auto f = f1 + f2;
                    if (set.find(f) == set.end())  // if capacitance not encountered yet
                    {
                        // add f to list
                        list[n - 1].push_back(f);
                        set.insert(f);
                        // add 1/f to list
                        auto f_rec = f.reciprocal();
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
    printf("%ld\n", p155());
}
