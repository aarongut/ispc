floating foo(floating a, floating b) {
    floating d = a / b;
    if (d < 0.)
        return 0.;

    return d;
}

export void bar(uniform integer * uniform X, uniform int N) {
    foreach (i = 0 ... N-1) {
        X[i] = foo(X[i], X[i+1]);
    }
}
