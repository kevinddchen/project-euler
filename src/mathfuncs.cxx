#include <vector>
#include <array>
#include "mathfuncs.h"


template <typename T>
bool is_prime(T x) 
{
    if (x < 2)
        return false;
    else if (x == 2)
        return true;
    else if (x & 1)  // if (x % 2) == 1
        return false;
    for (T y=3; y*y<=x; y+=2)
    {
        if (x%y == 0)
            return false;
    }
    return true;
}
template bool is_prime<long>(long);
template bool is_prime<int>(int);


bool * prime_sieve(int size) 
{
    bool * sieve = new bool[size];

    // initialize values
    sieve[0] = sieve[1] = false;
    for (int i=2; i<size; i++) 
        sieve[i] = true;

    // sieve
    for (int i=2; i*i<size; i++) 
    {
        if (sieve[i]) 
        {
            for (int j=i*i; j<size; j+=i) 
                sieve[j] = false;
        }
    }
    return sieve;
}


template <typename T>
std::vector<std::array<T, 2>> prime_factorize(T x) 
{
    std::vector<std::array<T, 2>> facts;
    T a;
    for (T i=2; i*i<=x; i++) 
    {
        a = 0;  // power of prime factor
        while (x%i == 0) 
        {
            x /= i;
            a++;
        }
        if (a != 0)
        {
            std::array<T, 2> arr = {i, a};     
            facts.push_back(arr);
        }
    }
    if (x > 1)  // remaining part may be a prime factor
    {
        std::array<T, 2> arr = {x, 1};     
        facts.push_back(arr);
    }
    return facts;
}
template std::vector<std::array<long, 2>> prime_factorize<long>(long x);
template std::vector<std::array<int, 2>> prime_factorize<int>(int x);


template <typename T>
void extended_gcd(T a, T b, T &s, T &t, T &r)
{
    s = 1;
    t = 0;
    r = a;
    T new_s = 0, new_t = 1, new_r = b;
    T q, temp;
    while (new_r != 0)
    {
        q = r / new_r;

        temp = r;
        r = new_r;
        new_r = temp - q * new_r;

        temp = s;
        s = new_s;
        new_s = temp - q * new_s;

        temp = t;
        t = new_t;
        new_t = temp - q * new_t;
    }
}
template void extended_gcd<int>(int, int, int&, int&, int&);
template void extended_gcd<long>(long, long, long&, long&, long&);


template <typename T>
T modular_inverse(T a, T m) 
{
    // use Extended Euclidean algorithm to solve a*s + m*t = 1. Then s is the inverse.
    T s, t, r;
    extended_gcd(a, m, s, t, r);
    if (r > 1)
        return 0;
    if (s < 0)
        s += m;
    return s;
}
template long modular_inverse<long>(long, long);
template int modular_inverse<int>(int, int);


template <typename T>
int modular_power(int a, T b, int m) 
{
    long result(1), base(a%m);
    while (b > 0) 
    {
        if (b & 1)  // if (b % 2) == 1
            result = (result * base) % m;
        base = (base * base) % m;
        b >>= 1;
    }
    return (int) result;
}
template int modular_power<int>(int, int, int);
template int modular_power<long>(int, long, int);
