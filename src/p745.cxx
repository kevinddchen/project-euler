#include <cstdio>
#include <ctime>

#include "mathfuncs.h"

/*


*/


long p745()
{
    return 0;
}


int main()
{
    clock_t t;
    t = clock();
    printf("%ld\n", p745());
    t = clock()-t;
    printf("Time: %.3f\n", ((float) t)/CLOCKS_PER_SEC);
}
