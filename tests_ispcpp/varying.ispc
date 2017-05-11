floating foo(const uniform int a, floating b) {
    floating out = b;
    for (int i = 1; i<a; i++) {
        out *= b;
    }

    return out;
}

export void square(uniform int N, uniform floating b[], uniform double out[]) {
    foreach (i = 0 ... N) {
        out[i] = foo(2, b[i]);
    }
}
