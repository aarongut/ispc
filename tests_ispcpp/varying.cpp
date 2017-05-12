#include <stdlib.h>
#include <stdio.h>

#include "varying.h"

int main() {
    float A[256];
    double B[256];
    float outA[256];
    double outB[256];


    for (int i=0; i<256; i++) {
        A[i] = 1. / (i+1);
        B[i] = 1. / (i+1);
    }

    ispc::square(256, (float*)&A, (float*)&outA);

    ispc::square(256, (double*)&B, (double*)&outB);

    for (int i=0; i<256; i++) {
        printf("float: %.16f\tdouble: %.16f\n", outA[i], outB[i]);
    }

    return 0;
}
