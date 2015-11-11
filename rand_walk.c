#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mkl.h"
#include "mkl_vsl.h"
#include "omp.h"
#define M_PI 3.14159265358979323846


typedef struct point
{
    double x;
    double y;
} point;


point generate_sample(point start_point, int length) {
    double *angles = (double *)malloc(length * sizeof(double));
    double *steps = (double *)malloc(length * sizeof(double));
    double res_x = start_point.x;
    double res_y = start_point.y;
    VSLStreamStatePtr rand_stream;
    vslNewStream(&rand_stream, VSL_BRNG_WH, 777);
    vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rand_stream, length, angles, 0.0, 2*M_PI);
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, rand_stream, length, steps, 50.0, 7.0);
    vslDeleteStream(&rand_stream);
    #pragma omp parallel for reduction(+:res_x, res_y)
    for (int i = 0; i < length; ++i) {
        res_x += steps[i]*cos(angles[i]);
        res_y += steps[i]*sin(angles[i]);
    }
    free(angles);
    free(steps);
    point result;
    result.x = res_x;
    result.y = res_y;
    return result;
}


double *stats(point *samples, int length) {
    double *res = (double *)malloc(4 * sizeof(double));
    res[0] = samples[0].x;
    res[1] = samples[0].x;
    res[2] = samples[0].y;
    res[3] = samples[0].y;
    #pragma omp parallel for
    for (int i = 0; i < length; ++i) {
        if (samples[i].x < res[0])
            res[0] = samples[i].x;
        if (samples[i].x > res[1])
            res[1] = samples[i].x;
        if (samples[i].y < res[2])
            res[2] = samples[i].y;
        if (samples[i].y > res[3])
            res[3] = samples[i].y;
    }
    return res;
}


int main(int argc, char **argv) {
    const int steps = 100;
    const int num_of_samples = 1000000;
    point *results = (point *)malloc(num_of_samples * sizeof(point));
    point start;
    start.x = 0.0;
    start.y = 0.0;
    #pragma omp parallel for
    for (int i = 0; i < num_of_samples; ++i) {
        results[i] = generate_sample(start, steps);
    }
    printf("%lf %lf\n", results[53].x, results[53].y);
    double *statistics = stats(results, num_of_samples);
    printf("minimal x: %lf\n", statistics[0]);
    printf("maximal x: %lf\n", statistics[1]);
    printf("minimal y: %lf\n", statistics[2]);
    printf("maximal y: %lf\n", statistics[3]);
    return 0;
}

