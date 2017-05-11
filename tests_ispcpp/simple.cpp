#include <stdlib.h>
#include <stdio.h>

#include "simple.h"

int main() {
    double A[256];

    for (int i=0; i<256; i++) {
        A[i] = i / 11.;
    }

    ispc::foo(256, (double*)&A);

    for (int i=0; i<256; i++) {
        printf("%f\n", A[i]);
    }

    return 0;
}
