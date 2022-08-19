# ANSWER 35407281

"""

Given an integer and its prime factorization, n = p1^a1 * p2^a2 * ... * pk^ak,
the number of divisors of n is (a_1 + 1)(a_2 + 1)...(a_k+1). So a number with
2^{500500} divisors is 2 * 3 * ... * p_{500500}. However, this is not the
smallest number, as we can replace p_{500500} with 2^2. We repeat this,
replacing the largest primes in the product with powers of smaller primes.

"""


def prime_generator(iterable):
    """Generates primes into iterable."""
    iterable.append(2)
    yield 2
    x = 1
    while True:
        x += 2
        is_prime = True
        for y in iterable:
            if y * y > x:
                break
            if x % y == 0:
                is_prime = False
                break
        if is_prime:
            iterable.append(x)
            yield x


def get_minimum(num_list, power_list):
    """Return minimum replacement given by lists."""
    L = []
    prev_power = 0
    for i, x in enumerate(num_list):
        power = power_list[i]
        if power == prev_power:
            if power == 1:
                break
            else:
                continue
        prev_power = power
        next_power = (power + 1) * 2 - 1
        L.append((x ** (next_power - power), i))
    return min(L)


def p500():
    # Generate primes
    p_list = []
    PrimeGenerator = prime_generator(p_list)
    for i in range(500500):
        next(PrimeGenerator)

    # Shave off larger primes in favor of adding powers on smaller primes
    p_powers = [1 for _ in range(len(p_list))]
    while True:
        p_large = p_list[-1]
        x, index = get_minimum(p_list, p_powers)
        if x < p_large:
            p_list.pop()
            p_powers.pop()
            p_powers[index] = (p_powers[index] + 1) * 2 - 1
        else:
            break

    # Multiply to get number in mod 500500507
    x = 1
    for i, p in enumerate(p_list):
        for _ in range(p_powers[i]):
            x = (x * p) % 500500507

    return x
