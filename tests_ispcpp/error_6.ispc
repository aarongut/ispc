number pow(number b, int a) {
    number out = b;
    for (int i = 1; i<a; i++) {
        out *= b;
    }

    return out;
}

export void square(uniform int N, uniform number$-1 b[], uniform number$-1 out[]) {
    foreach (i = 0 ... N) {
        out[i] = pow(b[i], 2);
    }
}
