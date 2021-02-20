// cmathfuncs.h
#ifndef _CMATHFUNCS_H
#define _CMATHFUNCS_H

#include <vector>

bool isPrime(long long);

bool * primeSieve(int);

std::vector<long long> primeFactorize(long long);

long long gcd(long long, long long);

long long modularInverse(long long, long long);

long long modpow(long long, long long, long long);

#endif
