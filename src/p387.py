# ANSWER 696067597313468

"""

A direct method works fine. First build up right truncatable Harshad numbers
resursively with increasing number of digits.

"""

from time import time

from .mathfuncs import is_prime


def get_next_generation(RTHN_list):

    """A generation of RTHN (right truncatable Harshad number) is all RTHN
    with n digits. Given a generation with n digits, this returns the
    generation with n+1 digits."""

    new_RTHN_list = []
    for RTHN in RTHN_list:
        digit_sum = sum(int(c) for c in str(RTHN))
        for n in range(10):
            if (RTHN * 10 + n) % (digit_sum + n) == 0:
                new_RTHN_list.append(RTHN * 10 + n)
    return new_RTHN_list


def p387():
    N_DIGITS = 14
    SUM = 0
    RTHN_list = list(range(1, 10))
    for _ in range(N_DIGITS - 2):
        RTHN_list = get_next_generation(RTHN_list)
        for RTHN in RTHN_list:
            # check is a strong Harshad number
            digit_sum = sum(int(c) for c in str(RTHN))
            if is_prime(RTHN // digit_sum):
                # find SRTH primes
                for prime_candidate in [RTHN * 10 + i for i in [1, 3, 7, 9]]:
                    if is_prime(prime_candidate):
                        SUM += prime_candidate
    return SUM


if __name__ == "__main__":
    time_start = time()
    print(p387())
    print("Time: {0:.3f}".format(time() - time_start))
