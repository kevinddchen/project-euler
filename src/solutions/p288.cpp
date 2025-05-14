#include <mf/generators.hpp>
#include <mf/mathfuncs.hpp>

#include <deque>

/*

We use the fact that the powers of p in n! equals

    floor(n/p) + floor(n/p^2) + floor(n/p^3) + ...

So if N = T0 + T1*p + T2*p^2 + ... then we can note that the answer, mod p^k,
is equal to

      T1 + T2*p + ... + Tk*p^{k-1}
    + T2 + T3*p + ... + T{k+1}*p^{k-1}
    + ...
    + Tq

ANSWER 605857431263981935

*/

long p288()
{
    const long p = 61;
    const int mod_log_p = 10;
    const int limit = 10'000'000;

    const long mod = mf::pow(p, mod_log_p);

    mf::BlumBlumShub bbs;
    ++bbs;  // discard s0
    int n = 0;

    // initialize an array with `mod_log_p` elements
    std::deque<long> ts;
    for (; n < mod_log_p; n++) {
        ts.push_back(*bbs++ % p);
    }

    long sum = 0;
    for (; n < limit + mod_log_p; n++) {
        // compute T_n + T_{n+1} p + T_{n+2} p^2 + ...
        long power_of_p = 1;
        for (long t : ts) {
            sum = (sum + t * power_of_p) % mod;
            power_of_p *= p;
        }
        // shift ts
        ts.pop_front();
        if (n < limit) {
            ts.push_back(*bbs++ % p);
        } else {
            ts.push_back(0);  // pad with zeros, which do not contribute to the sum
        }
    }

    return sum;
}

int main()
{
    printf("%ld\n", p288());
}
