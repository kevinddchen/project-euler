#include "common.h"
#include "mathfuncs.h"

#include <cstring>

/*

We apply the inverse of the map "UDDD..." to get the preimage of the map. The
input is related to an output n by an affine map,

    input = (a * n + b) / c

We then simply find the first integer input that exceeds the target.

ANSWER 1125977393124310

*/

inline void inv_D(long *affine)
{
    affine[0] *= 3;
    affine[1] *= 3;
}

inline void inv_U(long *affine)
{
    affine[0] *= 3;
    affine[1] = 3 * affine[1] - 2 * affine[2];
    affine[2] *= 4;
}

inline void inv_d(long *affine)
{
    affine[0] *= 3;
    affine[1] = 3 * affine[1] + affine[2];
    affine[2] *= 2;
}

long p277()
{
    const char seq[] = "UDDDUdddDDUDDddDdDddDDUDDdUUDd";
    const long target = 1'000'000'000'000'000;

    long affine[3] = {1, 0, 1}; // output is n

    // go through characters in reverse order and apply inverse maps
    const int length = std::strlen(seq);
    for (int i = length - 1; i >= 0; i--)
    {
        if (seq[i] == 'D')
        {
            inv_D(affine);
        }
        else if (seq[i] == 'U')
        {
            inv_U(affine);
        }
        else
        {
            inv_d(affine);
        }
    }
    // overall map is (affine[0] * n + affine[1]) / affine[2]  -->  n

    // find n mod affine[2] needed to yield an integer
    long a = affine[0] % affine[2];
    long b = affine[1] % affine[2];
    long m = modular_inverse(a, affine[2]) * (affine[2] - b) % affine[2];
    // n = affine[2] * k + m

    // input = affine[0] * k + (affine[0] * m + affine[1]) / affine[2]
    //                         ^----------- call this r -------------^
    long a_n = affine[0] / affine[2];
    long b_n = affine[1] / affine[2];
    long r = a_n * m + b_n + (a * m + b) / affine[2];

    // find k needed to exceed the target
    long k = (target - r) / affine[0] + 1;

    return affine[0] * k + r;
}

int main()
{
    TIMED(printf("%ld\n", p277()));
}
