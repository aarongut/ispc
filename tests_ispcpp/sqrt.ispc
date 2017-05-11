
static const float kThreshold = 0.00001f;

export void sqrt_ispc(uniform int N,
                      uniform floating initialGuess,
                      uniform floating values[],
                      uniform floating output[])
{
    foreach (i = 0 ... N) {

        floating x = values[i];
        floating guess = initialGuess;

        floating pred = abs(guess * guess * x - 1.f);

        while (pred > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            pred = abs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;

    }
}

task void sqrt_ispc_task(uniform int N,
                         uniform int span,
                         uniform floating initialGuess,
                         uniform floating values[],
                         uniform floating output[])
{

    uniform int indexStart = taskIndex * span;
    uniform int indexEnd = min(N, indexStart + span);

    foreach (i = indexStart ... indexEnd) {

        floating x = values[i];
        floating guess = initialGuess;

        floating pred = abs(guess * guess * x - 1.f);

        while (pred > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            pred = abs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;

    }
}

export void sqrt_ispc_withtasks(uniform int N,
                                uniform floating initialGuess,
                                uniform floating values[],
                                uniform floating output[])
{

    uniform int span = N / 64;  // 64 tasks

    launch[N/span] sqrt_ispc_task(N, span, initialGuess, values, output);
}
