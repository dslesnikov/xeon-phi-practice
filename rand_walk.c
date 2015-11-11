#include <stdlib.h>
#include <stdio.h>
#include "mkl.h"
#include "mkl_vsl.h"
#include "omp.h"
#define M_PI 3.14159265358979323846


int main(int argc, char **argv) {
    const int steps = 100;
    double *angles = (double *)malloc(steps * sizeof(double));
    VSLStreamStatePtr rand_stream;
    vslNewStream(&rand_stream, VSL_BRNG_WH, 777);
    vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rand_stream, steps, angles, 0.0, 2*M_PI);
    vslDeleteStream(&rand_stream);
    double mean = 0;
    for (int i = 0; i < steps; ++i)
        mean += angles[i];
    mean /= steps;
    printf("%lf\n", mean);
    return 0;
}

