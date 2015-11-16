#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <omp.h>
#include <mkl.h>
#define M_PI 3.14159265358979323846


typedef struct point
{
    double x;
    double y;
} point;


__attribute__( (target(mic)) ) point generate_sample(point start_point, int length, int seed) {
    double angles[100];
    double steps[100];
    double res_x = start_point.x;
    double res_y = start_point.y;
    VSLStreamStatePtr rand_stream;
    vslNewStream(&rand_stream, VSL_BRNG_MT2203, seed);
    vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rand_stream, length, angles, 0.0, 2*M_PI);
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, rand_stream, length, steps, 50.0, 7.0);
    vslDeleteStream(&rand_stream);
    #pragma omp parallel for reduction(+:res_x, res_y)
    for (int i = 0; i < length; ++i) {
        res_x += steps[i]*cos(angles[i]);
        res_y += steps[i]*sin(angles[i]);
    }
    point result;
    result.x = res_x;
    result.y = res_y;
    return result;
}


int main(int argc, char **argv) {
    const int steps = 100;
    const int num_of_samples = 1000000;
    point *results = (point *)memalign(64, num_of_samples * sizeof(point));
    point start;
    start.x = 0.0;
    start.y = 0.0;
    #pragma offload target(mic) \
     out( results : length(num_of_samples) )
    {
     #pragma omp parallel for
     for (int i = 0; i < num_of_samples; ++i)
         results[i] = generate_sample(start, steps, i);
    }
    FILE *fp = fopen("points.txt", "w+");
    for (int i = 0; i < num_of_samples; ++i)
        fprintf(fp, "%lf %lf\n", results[i].x, results[i].y);
    fclose(fp);
    free(results);
    return 0;
}
