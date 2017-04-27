floating saxpy_helper(floating scale,
                      floating<0> x,
                      floating<0> y) {
    return scale * x + y;
}


export void saxpy(uniform int N,
                  uniform floating<0> scale,
                  uniform floating<1> X[],
                  uniform floating<1> Y[],
                  uniform floating<2> result[])
{
    foreach (i = 0 ... N) {
        result[i] = saxpy_helper(scale, X[i], Y[i]);
    }
}
