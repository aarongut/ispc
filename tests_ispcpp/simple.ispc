export void foo(uniform int N, floating$1 X[])
{
    foreach (i = 0 ... N) {
        X[i] = X[i] + 1.0;
    }
}
