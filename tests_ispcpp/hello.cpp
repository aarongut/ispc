#include <stdlib.h>
#include <stdio.h>

#include "hello.ispc.h"

int main() {
    float A[100];
    float B[100];
    double result[100];

    for (int i=0; i<100; i++) {
        A[i] = 100 - i;
        B[i] = i*i;
    }

    ispc::saxpy(100, 3.1415926535, (float*)&A, (float*)&B, (double*)&result);

    for (int i=0; i<100; i++) {
        printf("%.6f\n", result[i]);
    }

    return 0;
}
