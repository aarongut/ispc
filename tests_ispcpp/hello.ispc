export void saxpy(uniform int N,
                  uniform floating<0> scale,
                  uniform floating<1> X[],
                  uniform floating<1> Y[],
                  uniform floating<2> result[])
{
    foreach (i = 0 ... N) {
        floating<2> tmp = scale * X[i] + Y[i];
        result[i] = tmp;
    }
}
