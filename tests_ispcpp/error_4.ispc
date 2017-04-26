//@error
// cannot determine return type for mult


floating mult(floating<0> x, floating<1>y) {
    return x * y;
}

export void saxpy(uniform int N,
                  uniform floating<0> scale,
                  uniform floating<1> X[],
                  uniform floating<1> Y[],
                  uniform floating<2> result[])
{
    foreach (i = 0 ... N) {
        floating<2> tmp = mult(scale, X[i]) + Y[i];
        result[i] = tmp;
    }
}
