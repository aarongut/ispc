number pow(number b, int a) {
    number out = b;
    for (int i = 1; i<a; i++) {
        out *= b;
    }

    return out;
}

export void square(uniform int N, uniform number b[], uniform number out[]) {
    foreach (i = 0 ... N) {
        out[i] = pow(b[i], 2);
    }
}
