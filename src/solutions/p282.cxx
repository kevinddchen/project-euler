#include "common.h"
#include "mathfuncs.h"

#include <cmath>

/*

We start by computing the tetrations 2^^n mod 14^8.

    2^^4 = 2^16 = 65536.
    2^^5 = 2^65536 = 804,023,040 (mod 14^8).
    2^^6 = 2^(2^65536)

Now to calculate this, we note that the pseudoorder of 2 mod 14^8 is 2,470,629.
In other words, 2^(8 + 2,470,629) = 2^8 (mod 14^8). This means that

    2^^6 = 2^(2^65536 % 2,470,629) = 2^(1,892,158) = 1,381,536,256 (mod 14^8).

By continuing in this fashion, we can compute the remaining values of 2^^n. It
turns out that we do not need to do that much more work since they approach a
constant value:

    2^^7 = 915,627,008 (mod 14^8)
    2^^8 = 106,739,712 (mod 14^8)
    2^^9 = 407,921,152 (mod 14^8)
    2^^10 = 829,575,168 (mod 14^8)
    2^^n for n > 10 = 2^^10 (mod 14^8)

This implies that the higher hyperoperations of 2 also take this constant
value. Thus it becomes very easy to compute the Ackermann function modulo 14^8.

    A(0, 0) = 1  // known
    A(1, 1) = 3  // known
    A(2, 2) = 7  // known
    A(3, 3) = 61  // known
    A(4, 4) = 2^^7 - 3 = 915,627,005 (mod 14^8)
    A(5, 5) = 2^^^8 - 3 = 829,575,165 (mod 14^8)
    A(6, 6) = 2^^^^9 - 3 = 829,575,165 (mod 14^8)

ANSWER 1098988351

*/


/*
 * Given m with a prime factorization m = 2^a * p1^a1 * ..., returns the
 * smallest positive integer k such that 2^(k+a) = 2^a mod m.
 *
 * Similar to `order` in Problem 752.
 */
long pseudoorder_of_2(long m)
{
    const auto m_facts = mf::prime_factorize(m);

    // compute totient of m, but excluding factors of 2
    long exp_of_2 = 0;                      // exponent of 2 in prime factorization of m
    long order = 1;                         // totient of m, excluding factors of 2
    std::vector<mf::PrimePower> tot_facts;  // prime factorization of totient of m, excluding factors of 2
    for (const auto& fact : m_facts) {
        if (fact.base == 2) {
            exp_of_2 = fact.exp;
        } else {
            order *= (fact.base - 1) * pow(fact.base, fact.exp - 1);
            tot_facts = mf::merge_prime_factors(tot_facts, mf::prime_factorize(fact.base - 1));
            tot_facts.push_back({fact.base, fact.exp - 1});
        }
    }

    // go through divisors of the totient and check for a smaller pseudoorder
    const long pow_of_2 = pow(2, exp_of_2);
    for (const auto& fact : tot_facts) {
        for (int i = 0; i < fact.exp; i++) {
            if (mf::modular_power(2, exp_of_2 + order / fact.base, m) == pow_of_2) {
                order /= fact.base;
            } else {
                break;
            }
        }
    }

    return order;
}


long p282()
{
    constexpr long M = 1'475'789'056;  // 14^8

    // we keep track of the pseudoorders
    std::vector<long> pseudoorders = {M};  // tracks pseudoorders
    std::vector<long> values = {65536};    // tracks values of 2^^(i+4) mod M
    int i = 0;
    while (pseudoorders[i] != 2) {
        i++;

        // compute 2^^(i+4) mod M
        long value = 65536;
        for (int j = i - 1; j >= 0; j--) {
            value = mf::modular_power(2, value, pseudoorders[j]);
        }
        values.push_back(value);

        // add new pseudoorder to list
        const long last_pseudoorder = pseudoorders[i - 1];
        pseudoorders.push_back(pseudoorder_of_2(last_pseudoorder));
    }

    // compute the Ackermann function
    constexpr long A0 = 1;              // A(0, 0)
    constexpr long A1 = 3;              // A(1, 1)
    constexpr long A2 = 7;              // A(2, 2)
    constexpr long A3 = 61;             // A(3, 3)
    const long A4 = values[3] - 3;      // A(4, 4) = 2^^7 - 3
    const long A5 = values[i - 1] - 3;  // A(5, 5) = 2^^^8 - 3
    const long A6 = values[i - 1] - 3;  // A(6, 6) = 2^^^^9 - 3

    const long sum = (A0 + A1 + A2 + A3 + A4 + A5 + A6) % M;

    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p282()));
}
