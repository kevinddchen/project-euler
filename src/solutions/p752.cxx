#include "common.h"
#include "mathfuncs.h"

/*

Recall that if we want to find the order of a mod x, by Euler's theorem we have
a^phi(x) = 1 (mod x), where phi(x) is the totient of x, i.e. the number of
positive integers < x that are coprime to x. Since the order of a must divide
phi(x), we can go through the divisors of phi(x) to find the order.

Because the ring of quadratic integers Q[sqrt(7)] is a Euclidean domain (i.e.
the greatest common divisor makes sense), a similar story follows: for a
quadratic integer a + b sqrt(7), we have (a + b sqrt(7))^psi(x) = 1 (mod x),
where psi(x) counts the number of quadratic integers that are coprime to x.

But what is the psi(x) analogue of the totient function for quadratic integers?
A bit of experimenting landed me at what is described in
`prime_factorize_quad_totient()`. Perhaps there is a more formal body of math that
explains its derivation, but I did not look any further.

As a final note, we skip all x that have 2 or 3 as a divisor--these will not
have any solutions. This is because the norm of 1 + sqrt(7) is -6, which needs
to be coprime to x for both -6 and 1 + sqrt(7) to have a multiplicative order
defined in the first place.

ANSWER 5610899769745488

*/

/*
 * Quadratic integer, a + b * sqrt(rad).
 */
template <long rad>
struct QuadInt {
    long a;
    long b;

    inline QuadInt<rad> copy() const { return {a, b}; }

    inline bool operator==(const QuadInt<rad>& other) const { return a == other.a && b == other.b; }

    inline QuadInt<rad> operator%(long m) const { return {a % m, b % m}; }

    inline QuadInt<rad> operator*(const QuadInt<rad>& other) const
    {
        return {a * other.a + rad * b * other.b, a * other.b + b * other.a};
    }
};

constexpr QuadInt<7> ONE = {1, 0};

/**
 * Recall that the totient of x counts the integers a, where 0 <= a < x, that
 * do not share a non-trivial divisor with x. If x has the prime factorization
 * x = p1^a1 * p2^a2 * ... * pk^ak, then the totient of x is given by
 * tot(x) = p1^(a1 - 1) * (p1 - 1) * p2^(a2 - 1) * (p2 - 1) * ...
 *
 * This function computes the analogue of the totient for quadratic integers,
 * i.e. it counts the quadratic integers a + b sqrt(rad), where 0 <= a, b < x,
 * that do not share a (quad int) divisor with x. This is given by
 * quad_tot(x) = p1^(2*a1 - 2) * (p1^2 - 1) * p2^(2*a2 - 2) * (p2^2 - 1) * ...
 *
 * If rad is prime and x contains rad in its prime factorization, then we have
 * to modify the corresponding term in the product above to
 * quad_tot(x) = ... * rad^(2*a - 2) * (rad^2 - rad) * ...
 * This is because sqrt(rad) is a divisor of rad.
 *
 * More specifically, this function returns the prime factorization, which is
 * more useful in this specific problem.
 */
template <long rad>
std::vector<mf::PrimePower> prime_factorize_quad_totient(long x, const std::vector<int>& factor_sieve)
{
    assert(factor_sieve[rad] == rad);  // only implemented for primes

    const auto facts = mf::prime_factorize(x, factor_sieve);
    std::vector<mf::PrimePower> out_facts;
    for (const auto& fact : facts) {
        if (fact.base == rad) {
            out_facts = mf::merge_prime_factors(out_facts, {{fact.base, 2 * fact.exp - 1}});
        } else {
            out_facts = mf::merge_prime_factors(out_facts, {{fact.base, 2 * fact.exp - 2}});
            out_facts = mf::merge_prime_factors(out_facts, mf::prime_factorize(fact.base + 1));
        }
        out_facts = mf::merge_prime_factors(out_facts, mf::prime_factorize(fact.base - 1));
    }
    return out_facts;
}

/*
 * Computes a^b mod m, where a is a quadratic integer.
 */
template <long rad>
QuadInt<rad> modular_power(const QuadInt<rad>& a, long b, long m)
{
    assert(b >= 0);
    assert(m > 1);

    QuadInt<rad> result = ONE.copy();
    QuadInt<rad> base = a % m;
    while (b > 0) {
        if (b & 1)  // if (b % 2) == 1
        {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        b >>= 1;
    }
    return result;
}

template <long rad>
long order(const QuadInt<rad>& x, long m, const std::vector<int>& factor_sieve)
{
    // compute the totient for quadratic integers
    const auto& facts = prime_factorize_quad_totient<rad>(m, factor_sieve);

    // compute the totient from its prime factors
    long order = 1;
    for (const auto& fact : facts) {
        order *= pow(fact.base, fact.exp);
    }

    // go through divisors of the totient and check for a smaller order
    for (const auto& fact : facts) {
        for (int i = 0; i < fact.exp; i++) {
            if (modular_power(x, order / fact.base, m) == ONE) {
                order /= fact.base;
            } else {
                break;
            }
        }
    }
    return order;
}

long p752()
{
    constexpr int limit = 1'000'000;
    constexpr QuadInt<7> init = {1, 1};  // 1 + sqrt(7)

    const auto sieve = mf::prime_factor_sieve(limit + 1);

    long sum = 0;
    for (int x = 2; x <= limit; x++) {
        if ((x % 2 != 0) && (x % 3 != 0)) {
            sum += order<7>(init, x, sieve);
        }
    }
    return sum;
}

int main()
{
    TIMED(printf("%ld\n", p752()));
}
