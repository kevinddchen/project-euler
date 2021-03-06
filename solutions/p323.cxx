// p323.cxx
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "cmathfuncs.h"
using namespace std;


/*

At index N, the probability that x_N will be all 1's is,

    P(N) = ( 1 - 2^(-N) )^32

so the probability that N is the first integer where x_N is all 1's is,

    P(N) - P(N-1)

Then we simply calculate the expected value.

    E = sum{i=1} i * (P(i) - P(i-1))

ANSWER 6.3551758451

*/ 


double p323() {

    double cum, prev_cum, prob;
    double exp_val = 0;

    prev_cum = 0;

    for (int N=1; true; N++) { 

        cum = pow(1 - pow(2, -N), 32);
        prob = cum - prev_cum;

        if (prob < 1e-13)
            break;

        exp_val += N * prob;
        prev_cum = cum;

    }

    return exp_val;

}

    

int main() {
    clock_t t;
    t = clock();
    printf("%.10f\n", p323());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
