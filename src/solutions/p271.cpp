#include <mf/mathfuncs.hpp>

/*

The strategy is similar to those of Problems 407 and 451. Given an integer and
its prime factorization, n = p1^a1 * p2^a2 * ... * pk^ak, the Chinese Remainder
Theorem defines a ring isomorphism,

    Z_n = Z_{p1^a1} * Z_{p2^a2} * ... * Z_{pk^ak}

We note that 13082761331670030 is the product of the primes 2, 3, ..., 43. For
each prime factor p, the ring Z_p is cyclic and is generated by a (non-unique)
primitive root, g. If the totient p-1 is divisible by 3, then there are three
cube roots of unity: 1, g^[(p-1)/3], and g^[2(p-1)/2]. It can be shown that
these roots are independent of the choice of g. If the totient is not divisible
by 3, the only cube root of unity is 1.

This gives us a list of "base cube roots of unity" corresponding to the
choices,

    (1, 0, 0, ...), (g, 0, 0, ...), (g^2, 0, 0, ...), (0, 1, 0, ...), ...

We find all combinations of these base roots to obtain all cube roots of unity
in Z_n.

(Related problems: 407, 451)

ANSWER 4617456485273129588

*/

/**
 * Copied from Problem 407.
 *
 * In the ring Z_n, for a given prime factor p^a find the integer 1 <= m < n
 * such that m = 1 (mod p^a) and m = 0 (mod q^b) for all other prime factors
 * q^b of n.
 */
long get_base_idempotent(long n, const mf::PrimePower& factor)
{
    const long x = mf::pow(factor.base, factor.exp);  // pi^ai
    const long n_x = n / x;
    // find b * n_x (mod n) such that b * n_x = 1 (mod x)
    return (mf::modular_inverse(n_x, x) * n_x) % n;
}

/**
 * Get a primitive root of Z_p for prime p. Uses the strategy in:
 * https://en.wikipedia.org/wiki/Primitive_root_modulo_n#Finding_primitive_roots.
 */
long get_primitive_root(long p)
{
    const long totient = p - 1;
    const auto factors = mf::prime_factorize(totient);
    for (long g = 2; g < p; g++) {
        // for each candidate, check if g^(totient / q) = 1 (mod p) for any
        // factor q of totient. If not, then g is a primitive root.
        bool is_primitive = true;
        for (const auto& factor : factors) {
            if (mf::modular_power(g, totient / factor.base, p) == 1) {
                is_primitive = false;
                break;
            }
        }
        if (is_primitive) {
            return g;
        }
    }
    throw std::runtime_error("No primitive root found");
}

/* Recursively sum all cube roots of unity. */
long sum_all_roots(const std::vector<std::vector<long>>& base_roots, long n, int i = 0, long current_root = 0)
{
    if (i == static_cast<int>(base_roots.size())) {
        return current_root % n;
    }

    long sum = 0;
    for (const long base_root : base_roots[i]) {
        sum += sum_all_roots(base_roots, n, i + 1, current_root + base_root);
    }

    return sum;
}

long p271()
{
    const long n = 13082761331670030;

    const auto prime_factors = mf::prime_factorize(n);

    // find the base cube roots of unity corresponding to each prime factor
    std::vector<std::vector<long>> base_roots;
    base_roots.reserve(prime_factors.size());

    for (const auto& factor : prime_factors) {
        // find the multiplicative unit, like (1, 0, 0, ...)
        const long unit = get_base_idempotent(n, factor);

        std::vector<long> roots = {unit};  // base root corresponding to 1 in Z_p

        // if totient is multiple of 3, there are two more cube roots of unity
        assert(factor.exp == 1);  // things are simpler if this is true
        const long totient = factor.base - 1;
        if ((totient % 3) == 0) {
            const long g = get_primitive_root(factor.base);
            const long first_root = mf::modular_power(g, totient / 3, factor.base);
            const long second_root = mf::modular_power(first_root, 2, factor.base);

            roots.push_back((first_root * unit) % n);
            roots.push_back((second_root * unit) % n);
        }
        base_roots.push_back(roots);
    }

    return sum_all_roots(base_roots, n) - 1;  // subtract 1 since its not counted
}

int main()
{
    printf("%ld\n", p271());
}
