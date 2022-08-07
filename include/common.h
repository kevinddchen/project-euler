#pragma once

#include <cstdio>
#include <ctime>

#define TIMED(X)                                             \
    {                                                        \
        clock_t t = clock();                                 \
        X;                                                   \
        t = clock() - t;                                     \
        printf("Time: %.3f\n", ((float)t) / CLOCKS_PER_SEC); \
    }
