#include <cstdio>
#include <ctime>
#include <cmath>


/*

Using calculus, we can show that the maximal values are x_j = 2j/(m+1).

ANSWER 371048281

*/


int P(int m)
{
    double product = 1;
    for (int j=1; j<=m; j++)
    {
        product *= pow(2*j/(m+1.), j);
    }
    return (int) product;
}


long p190() 
{
    long S = 0;
    for (int m=2; m<=15; m++)
        S += P(m);
    return S;
}


int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p190());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
