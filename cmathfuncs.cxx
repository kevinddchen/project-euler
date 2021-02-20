// cmathfuncs.cxx
#include <vector>

bool isPrime(long long x) {
    /* Returns True if x is prime. */
    if (x < 2)
        return false;
    else if (x == 2)
        return true;
    else if (x % 2 == 0)
        return false;
    for (long long y=3; y*y<=x; y+=2) {
        if (x%y == 0)
            return false;
    }
    return true;
}



bool * primeSieve(int size) {
    /* Creates prime sieve. */
    bool * sieve = new bool[size+1];
    for (int i=0; i<=size; i++) {
        sieve[i] = true;
    }

    sieve[0] = sieve[1] = false;
    for (int i=2; i*i<=size; i++) {
        if (sieve[i]) {
            for (int j=i*i; j<=size; j+=i) {
                sieve[j] = false;
            }
        }
    }
    return sieve;
}



std::vector<long long> primeFactorize(long long x) {
    /* Returns prime factors of x with multiplicities. */
    std::vector<long long> facts;
    for (long long i=2; i*i<=x; i++) {
        if (x%i == 0) {
            int c = 0;
            while (x%i == 0) {
                x /= i;
                c++;
            }
            facts.push_back(i);
            facts.push_back(c);
        }
    }
    if (x != 1) {
        facts.push_back(x);
        facts.push_back(1);
    }
    return facts;
}



long long gcd(long long a, long long b) {
    /* Returns greatest common divisor of a and b. */
    long long m;
    while (b != 0) {
        m = a%b;
        a = b;
        b = m;
    }
    return a;
}



long long modularInverse(long long a, long long n) {
    /* Returns multiplicative inverse of a mod n. */ 
    long long t(0), newt(1), r(n), newr(a);
    long long quotient, x;
    while (newr != 0) {
        quotient = r / newr;

        x = t;
        t = newt;
        newt = x - quotient*newt;

        x = r;
        r = newr;
        newr = x - quotient*newr;
    }
    if (r > 1)
        return 0;
    if (t < 0)
        t += n;
    return t;
}



long long modpow(long long b, long long e, long long m) {
    /* Returns base^exp in mod m. */
    b %= m;
    long long result = 1;
    while (e > 0) {
        if (e & 1)
            result = (result * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return result;
}

// for factor sieve and prime sieve factorization, see p549.
// for modular inverse, see p407.
