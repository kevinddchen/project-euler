#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>


/*

For a Torricelli triangle, we can use the law of cosines to show that

    a^2 = q^2 + r^2 + qr
    b^2 = p^2 + r^2 + pr
    c^2 = p^2 + q^2 + pq

It is faster to generate all p, q, r and then check that the a, b, c defined in
this way are integers.

ANSWER 30758397

*/


bool is_square(long x)
{
    long y = sqrt(x);
    return (x == y*y);
}


long p143()
{
    const int limit = 120'000;

    // for all p, find partners q such that
    // (1) 1 <= q < p
    // (2) p + q < 120'000
    // (3) p^2 + q^2 + p*q = k^2 for integer k
    std::vector<std::vector<int>> p_partners {{}};
    for (long p=1; p<limit; p++)
    {
        std::vector<int> temp;
        for (long q=1; q<p; q++)
        {
            if (p+q >= limit)
                break;
            if (is_square(p*p + q*q + p*q))
                temp.push_back(q);
        }
        p_partners.push_back(temp);
    }
    // (the steps above take ~30 sec)

    // try to find r < q from partners of p
    bool * hits = new bool[limit+1];
    for (int p=1; p<limit; p++)
    {
        auto partners = p_partners[p];
        for (auto r_iter=partners.begin(); r_iter!=partners.end(); r_iter++)
        {
            for (auto q_iter=r_iter+1; q_iter!=partners.end(); q_iter++)
            {
                if (p + *q_iter + *r_iter > limit)
                    break;
                auto q_partners = p_partners[*q_iter];
                // if r is a partner of q
                if (std::find(q_partners.begin(), q_partners.end(), *r_iter) != q_partners.end())
                    hits[p + *q_iter + *r_iter] = true;
            }
        }
    }

    // add up all hits
    long S = 0;
    for (int i=0; i<=limit; i++)
    {
        if (hits[i])
            S += i;
    }

    return S;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p143());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
