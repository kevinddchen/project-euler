from mathfuncs import is_prime, prime_factorize, prime_sieve


def test_is_prime() -> None:
    assert is_prime(2)
    assert is_prime(3)
    assert not is_prime(4)
    assert is_prime(5)
    assert not is_prime(6)
    assert is_prime(7)
    assert not is_prime(8)
    assert not is_prime(9)
    assert not is_prime(10)
    assert is_prime(11)
    assert not is_prime(12)
    assert is_prime(13)
    assert not is_prime(14)
    assert not is_prime(15)
    assert not is_prime(16)
    assert is_prime(17)
    assert not is_prime(18)
    assert is_prime(19)
    assert not is_prime(20)
    assert is_prime(2147483647)  # largest int, 2^31 - 1
    assert not is_prime(2147483649)
    assert not is_prime(2147483651)
    assert not is_prime(2147483653)
    assert not is_prime(2147483655)
    assert not is_prime(2147483657)
    assert is_prime(2147483659)


def test_prime_sieve() -> None:
    # Test sieve
    sieve = prime_sieve(9)
    assert len(sieve) == 9
    assert not sieve[0]
    assert not sieve[1]
    assert sieve[2]
    assert sieve[3]
    assert not sieve[4]
    assert sieve[5]
    assert not sieve[6]
    assert sieve[7]
    assert not sieve[8]

    # Test with `is_prime`
    sieve = prime_sieve(1000)
    assert not sieve[0]
    assert not sieve[1]
    for i in range(2, 1000):
        assert is_prime(i) == sieve[i]

    # Test no crash for small sizes
    sieve = prime_sieve(0)
    assert sieve == []
    sieve = prime_sieve(1)
    assert sieve == [False]
    sieve = prime_sieve(2)
    assert sieve == [False, False]


def test_prime_factorize() -> None:
    factors = prime_factorize(2)
    assert len(factors) == 1
    assert factors[0].base == 2 and factors[0].exp == 1

    factors = prime_factorize(12)
    assert len(factors) == 2
    assert factors[0].base == 2 and factors[0].exp == 2
    assert factors[1].base == 3 and factors[1].exp == 1

    factors = prime_factorize(49)
    assert len(factors) == 1
    assert factors[0].base == 7 and factors[0].exp == 2

    factors = prime_factorize(60)
    assert len(factors) == 3
    assert factors[0].base == 2 and factors[0].exp == 2
    assert factors[1].base == 3 and factors[1].exp == 1
    assert factors[2].base == 5 and factors[2].exp == 1

    factors = prime_factorize(2 * 2 * 3 * 5 * 7 * 7 * 17 * 23)
    assert len(factors) == 6
    assert factors[0].base == 2 and factors[0].exp == 2
    assert factors[1].base == 3 and factors[1].exp == 1
    assert factors[2].base == 5 and factors[2].exp == 1
    assert factors[3].base == 7 and factors[3].exp == 2
    assert factors[4].base == 17 and factors[4].exp == 1
    assert factors[5].base == 23 and factors[5].exp == 1
