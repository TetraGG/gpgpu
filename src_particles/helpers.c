#include <math.h>
#include <stdlib.h>

#include "helpers.h"

double random_uniform(double range)
{
    return (rand() / (double) RAND_MAX * 2.0 - 1.0) * range; 
}

double random_gaussian(double mean, double stddev)
{
    double uniform1;
    double uniform2;
    double w;

    do {
        uniform1 = random_uniform(1.0);
        uniform2 = random_uniform(1.0);
        w = uniform1 * uniform1 + uniform2 * uniform2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    box_muller = uniform2 * w * stddev + mean;
    return uniform1 * w * stddev + mean;
}

void compute_fps(void)
{
    frame_count++;

    current_time = clock();
    double time_interval = (current_time - previous_time) / CLOCKS_PER_SEC;

    if (time_interval > 1.0)
    {
        fps = frame_count / time_interval;
        previous_time = current_time;
        frame_count = 0;
    }
}
