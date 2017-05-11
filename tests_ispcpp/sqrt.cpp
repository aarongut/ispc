#include <stdio.h>
#include <algorithm>
#include <pthread.h>
#include <math.h>
#include <cmath>

#include "CycleTimer.h"
#include "sqrt.h"

using namespace ispc;

void sqrtSerial(int N,
                float initialGuess,
                float values[],
                float output[])
{

    static const float kThreshold = 0.00001f;

    for (int i=0; i<N; i++) {

        float x = values[i];
        float guess = initialGuess;

        float error = fabs(guess * guess * x - 1.f);

        while (error > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            error = fabs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;
    }
}

void sqrtSerial(int N,
                double initialGuess,
                double values[],
                double output[])
{

    static const double kThreshold = 0.00001f;

    for (int i=0; i<N; i++) {

        double x = values[i];
        double guess = initialGuess;

        double error = std::abs(guess * guess * x - 1.);

        while (error > kThreshold) {
            guess = (3. * guess - x * guess * guess * guess) * 0.5;
            error = std::abs(guess * guess * x - 1.);
        }

        output[i] = x * guess;
    }
}

static void verifyResult(int N, float* result, float* gold) {
    for (int i=0; i<N; i++) {
        if (fabs(result[i] - gold[i]) > 1e-4) {
            printf("Error: [%d] Got %f expected %f\n", i, result[i], gold[i]);
        }
    }
}

static void verifyResult(int N, double* result, double* gold) {
    for (int i=0; i<N; i++) {
        if (std::abs(result[i] - gold[i]) > 1e-4) {
            printf("Error: [%d] Got %f expected %f\n", i, result[i], gold[i]);
        }
    }
}

int main() {

    const unsigned int N = 20 * 1000 * 1000;
    const float initialGuess = 1.0f;
    const double dinitialGuess = 1.0;

    float* values = new float[N];
    float* output = new float[N];
    float* gold = new float[N];

    double* dvalues = new double[N];
    double* doutput = new double[N];
    double* dgold = new double[N];

    for (unsigned int i=0; i<N; i++)
    {
        // random input values
        values[i] = .001f + 2.998f * static_cast<float>(rand()) / RAND_MAX;
        dvalues[i] = .001 + 2.998 * static_cast<double>(rand()) / RAND_MAX;
        output[i] = 0.f;
        doutput[i] = 0.;
    }

    // generate a gold version to check results
    for (unsigned int i=0; i<N; i++) {
        gold[i] = sqrt(values[i]);
        dgold[i] = sqrt(dvalues[i]);
    }

    //
    // And run the serial implementation 3 times, again reporting the
    // minimum time.
    //
    double minSerial = 1e30;
    for (int i = 0; i < 5; ++i) {
        double startTime = CycleTimer::currentSeconds();
        sqrtSerial(N, initialGuess, values, output);
        double endTime = CycleTimer::currentSeconds();
        minSerial = std::min(minSerial, endTime - startTime);
    }

    printf("[sqrt float serial]:\t\t[%.3f] ms\n", minSerial * 1000);
    verifyResult(N, output, gold);

    double minDSerial = 1e30;
    for (int i = 0; i < 5; ++i) {
        double startTime = CycleTimer::currentSeconds();
        sqrtSerial(N, dinitialGuess, dvalues, doutput);
        double endTime = CycleTimer::currentSeconds();
        minDSerial = std::min(minDSerial, endTime - startTime);
    }

    printf("[sqrt double serial]:\t\t[%.3f] ms\n", minDSerial * 1000);
    verifyResult(N, doutput, dgold);

    // Clear out the buffer
    for (unsigned int i = 0; i < N; ++i) {
        output[i] = 0;
        doutput[i] = 0;
    }


    //
    // Compute the image using the ispc implementation; report the minimum
    // time of three runs.
    //
    double minISPC = 1e30;
    for (int i = 0; i < 5; ++i) {
        double startTime = CycleTimer::currentSeconds();
        ispc::sqrt_ispc(N, initialGuess, values, output);
        double endTime = CycleTimer::currentSeconds();
        minISPC = std::min(minISPC, endTime - startTime);
    }

    printf("[sqrt float ispc]:\t\t[%.3f] ms\n", minISPC * 1000);

    verifyResult(N, output, gold);

    double minDISPC = 1e30;
    for (int i = 0; i < 5; ++i) {
        double startTime = CycleTimer::currentSeconds();
        ispc::sqrt_ispc(N, dinitialGuess, dvalues, doutput);
        double endTime = CycleTimer::currentSeconds();
        minDISPC = std::min(minDISPC, endTime - startTime);
    }

    printf("[sqrt double ispc]:\t\t[%.3f] ms\n", minDISPC * 1000);

    verifyResult(N, doutput, dgold);

    // Clear out the buffer
    for (unsigned int i = 0; i < N; ++i) {
        output[i] = 0;
        doutput[i] = 0;
    }

    //
    // Tasking version of the ISPC code
    //
    double minTaskISPC = 1e30;
    for (int i = 0; i < 3; ++i) {
        double startTime = CycleTimer::currentSeconds();
        ispc::sqrt_ispc_withtasks(N, initialGuess, values, output);
        double endTime = CycleTimer::currentSeconds();
        minTaskISPC = std::min(minTaskISPC, endTime - startTime);
    }

    printf("[sqrt float task ispc]:\t[%.3f] ms\n", minTaskISPC * 1000);

    verifyResult(N, output, gold);

    double minDTaskISPC = 1e30;
    for (int i = 0; i < 3; ++i) {
        double startTime = CycleTimer::currentSeconds();
        ispc::sqrt_ispc_withtasks(N, initialGuess, values, output);
        double endTime = CycleTimer::currentSeconds();
        minDTaskISPC = std::min(minDTaskISPC, endTime - startTime);
    }

    printf("[sqrt double task ispc]:\t[%.3f] ms\n", minTaskISPC * 1000);

    verifyResult(N, output, gold);

    printf("\t\t\t\t(%.2fx speedup from ISPC float)\n", minSerial/minISPC);
    printf("\t\t\t\t(%.2fx speedup from task ISPC float)\n", minSerial/minTaskISPC);
    printf("\t\t\t\t(%.2fx speedup from ISPC double)\n", minDSerial/minDISPC);
    printf("\t\t\t\t(%.2fx speedup from task ISPC double)\n", minDSerial/minDTaskISPC);

    delete[] values;
    delete[] output;
    delete[] gold;
    delete[] dvalues;
    delete[] doutput;
    delete[] dgold;

    return 0;
}
