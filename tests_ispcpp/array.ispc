export void array(uniform int N, uniform integer * uniform X) {
    integer *A = new integer[N/2];

    foreach (i = 0 ... N/2) {
        A[i] = X[i] + X[N/2 + i];
    }

    foreach (i = 0 ... N) {
        X[i] = A[i/2];
    }

    delete[] A;
}
