import logging

import pytest

from ..mathfuncs import PrimeSieve, is_prime

LOG = logging.getLogger(__name__)


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

    # Test basic functionality
    ps = PrimeSieve(9)
    assert ps.size == 9
    assert ps.__next__() == 2
    assert ps.__next__() == 3
    assert ps.__next__() == 5
    assert ps.__next__() == 7
    with pytest.raises(StopIteration):
        ps.__next__()

    # Test sieve
    sieve = ps.sieve
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

    # Test iteration
    expected_primes = [2, 3, 5, 7]
    actual_primes = [x for x in PrimeSieve(9)]
    assert expected_primes == actual_primes

    # Test with `is_prime`
    ps = PrimeSieve(100)
    for x in ps:
        assert is_prime(x)
    sieve = ps.sieve
    assert not sieve[0]
    assert not sieve[1]
    for i in range(2, 100):
        assert is_prime(i) == sieve[i]

    # Test getting sieve directly
    sieve = PrimeSieve(100).sieve
    assert not sieve[0]
    assert not sieve[1]
    for i in range(2, 100):
        assert is_prime(i) == sieve[i]

    # Test no crash for small sizes
    ps = PrimeSieve(0)
    assert ps.size == 0
    assert ps.sieve == []
    ps = PrimeSieve(1)
    assert ps.size == 1
    assert ps.sieve == [False]
    ps = PrimeSieve(2)
    assert ps.size == 2
    assert ps.sieve == [False, False]
