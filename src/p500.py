#!/usr/bin/python
#ANSWER 35407281

"""

See solution explanations

"""

from time import time

def prime_generator(iterable):
    """ Generates primes into iterable. """
    iterable.append(2)
    yield 2
    x = 1
    while True:
        x += 2
        is_prime = True 
        for y in iterable:
            if y*y > x:
                break
            if x%y == 0:
                is_prime = False
                break
        if is_prime:
            iterable.append(x)
            yield x

def get_minimum(num_list, power_list):
    """ Return minimum replacement given by lists. """
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
        next_power = (power+1)*2-1
        L.append( (x**(next_power-power), i) )
    return min(L)

def p500():
    ## Generate primes
    p_list = []
    PrimeGenerator = prime_generator(p_list)
    for i in range(500500):
        next(PrimeGenerator)

    ## Shave off larger primes in favor of adding powers on smaller primes
    p_powers = [1 for _ in range(len(p_list))]
    while True:
        p_large = p_list[-1]
        x, index = get_minimum(p_list, p_powers)
        if x < p_large:
            p_list.pop()
            p_powers.pop()
            p_powers[index] = (p_powers[index]+1)*2-1
        else:
            break

    ## Multiply to get number in mod 500500507
    x = 1
    for i, p in enumerate(p_list):
        for _ in range(p_powers[i]):
            x = (x*p) % 500500507

    return x

if __name__ == '__main__':
    time_start = time()
    print(p500())
    print("Time: {0:.3f}".format(time()-time_start))

