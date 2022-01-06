#include <cstdio>
#include <ctime>
#include <cmath>
#include <numeric>


/*

Brute force. Note that the number of strictly contained lattice points is equal to

    (ab + bc + cd + da - g(a,b) - g(b,c) - g(c,d) - g(d,a))/2 + 1

where g is the greatest common divisor function, which can be calculated
quickly the Euclidian algorithm.

ANSWER 694687

*/


bool is_square(int x) 
{
    int y = sqrt(x);
    return x == y*y;
}


long p504() 
{
    const int size = 100;
    long count = 0;

    // generate table of values for gcd
    int ** G = new int *[size+1];
    for (int i=1; i<=size; i++) 
    {
        G[i] = new int [size+1];
        for (int j=1; j<=size; j++)
            G[i][j] = std::gcd(i, j);
    }

    // iterate through all quadrilaterals
    for (int a=1; a<=size; a++) 
    {
        for (int b=1; b<=size; b++) 
        {
            for (int c=1; c<=size; c++) 
            {
                for (int d=1; d<=size; d++) 
                {
                    int x = (a*b + b*c + c*d + d*a - G[a][b] - G[b][c] - G[c][d] - G[d][a])/2 + 1;
                    if (is_square(x)) 
                        count++;
                }
            }
        }
    }
    return count;
}



int main() 
{
    clock_t t;
    t = clock();
    printf("%ld\n", p504());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
