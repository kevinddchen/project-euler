#include "mathfuncs.h"

#include <numeric>

#include <cassert>
#include <cstdio>

/**
 * Tests equality between two floats, up to specified numerical tolerance.
 */
bool is_equal(double a, double b, double eps = 1e-15)
{
    return abs(a - b) < eps;
}

void test_is_prime()
{
    printf("Testing `is_prime()`... ");

    assert(mf::is_prime(2));
    assert(mf::is_prime(3));
    assert(!mf::is_prime(4));
    assert(mf::is_prime(5));
    assert(!mf::is_prime(6));
    assert(mf::is_prime(7));
    assert(!mf::is_prime(8));
    assert(!mf::is_prime(9));
    assert(!mf::is_prime(10));
    assert(mf::is_prime(11));
    assert(!mf::is_prime(12));
    assert(mf::is_prime(13));
    assert(!mf::is_prime(14));
    assert(!mf::is_prime(15));
    assert(!mf::is_prime(16));
    assert(mf::is_prime(17));
    assert(!mf::is_prime(18));
    assert(mf::is_prime(19));
    assert(!mf::is_prime(20));
    assert(mf::is_prime(2147483647));  // largest int, 2^31 - 1
    assert(!mf::is_prime(2147483649));
    assert(!mf::is_prime(2147483651));
    assert(!mf::is_prime(2147483653));
    assert(!mf::is_prime(2147483655));
    assert(!mf::is_prime(2147483657));
    assert(mf::is_prime(2147483659));

    printf("Done!\n");
}

void test_prime_sieve()
{
    printf("Testing `prime_sieve()`... ");

    auto sieve = mf::prime_sieve(9);
    assert(!sieve[0]);
    assert(!sieve[1]);
    assert(sieve[2]);
    assert(sieve[3]);
    assert(!sieve[4]);
    assert(sieve[5]);
    assert(!sieve[6]);
    assert(sieve[7]);
    assert(!sieve[8]);

    // Test using `is_prime`
    sieve = mf::prime_sieve(100);
    assert(!sieve[0]);
    assert(!sieve[1]);
    for (int i = 2; i < 100; i++) {
        assert(mf::is_prime(i) == sieve[i]);
    }

    // Test no crash for small sizes
    sieve = mf::prime_sieve(0);
    sieve = mf::prime_sieve(1);
    assert(!sieve[0]);
    sieve = mf::prime_sieve(2);
    assert(!sieve[0]);
    assert(!sieve[1]);

    printf("Done!\n");
}

void test_prime_factor_sieve()
{
    printf("Testing `prime_factor_sieve()`... ");

    auto sieve = mf::prime_factor_sieve(9);
    assert(sieve[0] == 0);
    assert(sieve[1] == 0);
    assert(sieve[2] == 2);
    assert(sieve[3] == 3);
    assert(sieve[4] == 2);
    assert(sieve[5] == 5);
    assert(sieve[6] == 2);
    assert(sieve[7] == 7);
    assert(sieve[8] == 2);

    // Test using `is_prime` and divisibility
    sieve = mf::prime_factor_sieve(100);
    assert(sieve[0] == 0);
    assert(sieve[1] == 0);
    for (int i = 2; i < 100; i++) {
        if (mf::is_prime(i)) {
            assert(sieve[i] == i);
        }
        assert(i % sieve[i] == 0);
    }

    // Test no crash for small sizes
    sieve = mf::prime_factor_sieve(0);
    sieve = mf::prime_factor_sieve(1);
    assert(sieve[0] == 0);
    sieve = mf::prime_factor_sieve(2);
    assert(sieve[0] == 0);
    assert(sieve[1] == 0);

    printf("Done!\n");
}

void test_prime_factorize()
{
    printf("Testing `prime_factorize(long)`... ");

    auto factors = mf::prime_factorize(2);
    assert(factors.size() == 1);
    assert(factors[0].base == 2 && factors[0].exp == 1);

    factors = mf::prime_factorize(12);
    assert(factors.size() == 2);
    assert(factors[0].base == 2 && factors[0].exp == 2);
    assert(factors[1].base == 3 && factors[1].exp == 1);

    factors = mf::prime_factorize(49);
    assert(factors.size() == 1);
    assert(factors[0].base == 7 && factors[0].exp == 2);

    factors = mf::prime_factorize(60);
    assert(factors.size() == 3);
    assert(factors[0].base == 2 && factors[0].exp == 2);
    assert(factors[1].base == 3 && factors[1].exp == 1);
    assert(factors[2].base == 5 && factors[2].exp == 1);

    factors = mf::prime_factorize(2 * 2 * 3 * 5 * 7 * 7 * 17 * 23);
    assert(factors.size() == 6);
    assert(factors[0].base == 2 && factors[0].exp == 2);
    assert(factors[1].base == 3 && factors[1].exp == 1);
    assert(factors[2].base == 5 && factors[2].exp == 1);
    assert(factors[3].base == 7 && factors[3].exp == 2);
    assert(factors[4].base == 17 && factors[4].exp == 1);
    assert(factors[5].base == 23 && factors[5].exp == 1);

    printf("Done!\n");
}

void test_prime_factorize_with_sieve()
{
    printf("Testing `prime_factorize(int, int*)`... ");

    // we assume that the normal prime_factorize works
    auto sieve = mf::prime_factor_sieve(100);

    for (int i = 2; i < 100; i++)
    {
        auto factors = mf::prime_factorize(i, sieve.get());
        auto exp_factors = mf::prime_factorize(i);
        for (int j = 0; j < factors.size(); j++) {
            assert(factors[j] == exp_factors[j]);
        }
    }

    printf("Done!\n");
}

void test_extended_gcd()
{
    printf("Testing `extended_gcd()`... ");

    long s, t, r;
    mf::extended_gcd(240, 46, s, t, r);
    assert(240 * s + 46 * t == r);
    assert(r == 2);
    assert(s == -9);
    assert(t == 47);

    mf::extended_gcd(69, 420, s, t, r);
    assert(69 * s + 420 * t == r);
    assert(r == std::gcd(69, 420));

    printf("Done!\n");
}

void test_modular_inverse()
{
    printf("Testing `modular_inverse()`... ");

    long x = mf::modular_inverse(3, 7);
    assert(x == 5);
    assert((x * 3) % 7 == 1);

    assert((mf::modular_inverse(4, 15) * 4) % 15 == 1);

    assert(mf::modular_inverse(1, 11) == 1);
    assert((mf::modular_inverse(2, 11) * 2) % 11 == 1);
    assert(mf::modular_inverse(10, 11) == 10);

    // Test not coprime returns 0
    assert(mf::modular_inverse(2, 2) == 0);
    assert(mf::modular_inverse(4, 2) == 0);
    assert(mf::modular_inverse(2, 4) == 0);

    printf("Done!\n");
}

void test_modular_power()
{
    printf("Testing `modular_power()`... ");

    assert(mf::modular_power(2, 5, 7) == 4);
    assert(mf::modular_power(240, 46, 999) == 891);
    assert(mf::modular_power(69, 420, 999) == 729);

    assert(mf::modular_power(0, 0, 100) == 1);
    assert(mf::modular_power(2, 0, 100) == 1);
    assert(mf::modular_power(0, 2, 100) == 0);

    assert(mf::modular_power(-5, 5, 7) == 4);
    assert(mf::modular_power(-12, 5, 7) == 4);
    assert(mf::modular_power(-759, 46, 999) == 891);
    assert(mf::modular_power(-930, 420, 999) == 729);

    printf("Done!\n");
}

void test_round()
{
    printf("Testing `round()`... ");

    assert(is_equal(mf::round(0.90909, 0), 1.0));
    assert(is_equal(mf::round(0.90909, 1), 0.9));
    assert(is_equal(mf::round(0.90909, 2), 0.91));
    assert(is_equal(mf::round(0.90909, 3), 0.909));
    assert(is_equal(mf::round(0.90909, 4), 0.9091));
    assert(is_equal(mf::round(0.90909, 5), 0.90909));

    printf("Done!\n");
}

int main()
{
    test_is_prime();
    test_prime_sieve();
    test_prime_factor_sieve();
    test_prime_factorize();
    test_prime_factorize_with_sieve();
    test_extended_gcd();
    test_modular_inverse();
    test_modular_power();
    test_round();

    return 0;
}
