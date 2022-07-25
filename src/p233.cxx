#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>
#include "mathfuncs.h"


/*

For any integers a, b such that N^2 = a^2 + b^2, we can check that the integers

    x = (N - (a-b)) / 2 ,       y = (N - (a+b)) / 2

give a point (x, y) on the circle. Therefore, f(N) = r_2(N^2), where r_2 is the
sum of squares function. If the prime factorization is

    N = 2^g p1^j1 p2^j2 ... q1^k1 q2^k2 ...

where p_i and q_i are primes of the form

    p_i = 1 (mod 4) ,           q_i = 3 (mod 4)

then r_2(N^2) = 4(2*j_1 + 1)(2*j_2 + 1) ... . Since 420 = 4 * 3 * 5 * 7, we
iterate over all combinations of at most 3 p_i primes:

    p1^3 p2^2 p3 = 5^3 * 13^2 * 17 , 5^3 * 13^2 * 29 , ...
    p1^7 p2^3    = 5^7 * 13^3 , 5^7 * 17^3 , ...
    p1^10 p2^2   = 5^10 * 13^2 , 5^10 * 13^2 , ...

The other combinations are too large. For each combination, we find all integers
that can be obtained by further multiplying by the other primes {2, 3, 7, 11, ...}.
This is most efficiently done by generating all numbers whose prime
factorizations contain primes in {2, 3, 7, 11, ...}, sorting the list, and then
keeping track of the partial sums.

ANSWER 271204031455541309

*/


/* Return all integers <= N whose prime factorizations only include elements of `primes`. */
std::vector<int> generate_restricted_integers(std::vector<int> primes, int N)
{
    std::vector<int> out{1};
    for (int p : primes)
    {
        if (p > N)
            break;
        // For each p, multiply its powers to previously obtained numbers.
        // It is slightly faster to keep `out` sorted each iteration.
        long power_of_p = p;
        std::vector<int> temp;
        while (power_of_p <= N)
        {
            for (int n : out)
            {
                if (n*power_of_p > N)    // `out` is sorted
                    break;
                temp.push_back(n*power_of_p);
            }
            power_of_p *= p;
        }
        // add new numbers to `out` and then sort
        out.insert(out.end(), temp.begin(), temp.end());
        std::sort(out.begin(), out.end());
    }
    return out;
}


/* Iterate through all powers like p1^j1 * p2^j2 * ... */
void recurse(
    long &S,                    // sum so far
    const long limit,           // limit = 10^11
    std::vector<int> &powers,   // powers of p's we are considering
    std::vector<int> &prev_p,   // previous p's
    long prev_prod,             // product of previous p's
    int k,                      // current index of p
    std::vector<int> &p_primes,
    std::vector<int> &q_numbers,
    long * partial_sums)
{
    for (long p : p_primes)
    {
        // check p is not previously used
        if (std::find(prev_p.begin(), prev_p.begin()+k, p) != prev_p.begin()+k)
            continue;

        long prod = prev_prod * pow(p, powers[k]);
        if (prod > limit)
            break;

        if (k == powers.size()-1)   // bottom of recursion
        {
            // find first i such that limit/prod < q_numbers[i]
            auto i = std::upper_bound(q_numbers.begin(), q_numbers.end(), limit/prod);
            // then prod*q_numbers[i-1] <= limit
            S += prod * partial_sums[i - 1 - q_numbers.begin()];
        }
        else                        // not at bottom of recursion
        {
            prev_p[k] = p;
            recurse(S, limit, powers, prev_p, prod, k+1, p_primes, q_numbers, partial_sums);
        }
    }
}


long p233()
{
    const long limit = 100'000'000'000;

    // generate all primes needed
    int sieve_size = 1 + limit / (5*5*5*13*13);
    bool * sieve = prime_sieve(sieve_size);

    // sort primes into {p : p=1 mod 4} and {q : q=2 or q=3 mod 4}
    std::vector<int> p_primes;
    std::vector<int> q_primes{2};
    for (int i=3; i<sieve_size; i+=4)
    {
        if (sieve[i])
            q_primes.push_back(i);
        if (i+2<sieve_size && sieve[i+2])
            p_primes.push_back(i+2);
    }

    // find integers whose prime factorizations only contain elements in `q_primes`
    std::vector<int> q_numbers = generate_restricted_integers(q_primes, limit / (5*5*5*13*13*17));

    // calculate partial sums of `q_numbers`
    int q_numbers_size = q_numbers.size();
    long * partial_sums = new long[q_numbers_size];
    long ps = 0;
    for (int i=0; i<q_numbers_size; i++)
    {
        ps += q_numbers[i];
        partial_sums[i] = ps;
    }

    long S = 0;
    std::vector<int> powers, prev_p = {0, 0};
    // iterate through all p1^3 * p2^2 * p3
    powers = {3, 2, 1};
    recurse(S, limit, powers, prev_p, 1, 0, p_primes, q_numbers, partial_sums);
    // iterate through all p1^7 * p2^3
    powers = {7, 3};
    recurse(S, limit, powers, prev_p, 1, 0, p_primes, q_numbers, partial_sums);
    // iterate through all p1^10 * p2^2
    powers = {10, 2};
    recurse(S, limit, powers, prev_p, 1, 0, p_primes, q_numbers, partial_sums);

    return S;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p233());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
