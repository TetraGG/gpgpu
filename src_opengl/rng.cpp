#include "rng.h"
#include <cmath>

double boxMuller2Rand;

/******************************************************************************
* Return uniformly distributed random double within range [-range,range]
******************************************************************************/
double uniformRandom(double range)
{
  return (rand() / (double)RAND_MAX * 2.0 - 1.0) * range;
}

/******************************************************************************
* Return gaussian random variable with mean "mean" and standard
* deviation "stdDev". Uses two uniform random variables for generation of
* a normally distributed one (Box-Muller transform)
******************************************************************************/
double gaussianRandom(double mean, double stdDev)
{
  double uniform1, uniform2, w;

  do {
    uniform1 = uniformRandom(1.0);
    uniform2 = uniformRandom(1.0);
    w = uniform1 * uniform1 + uniform2 * uniform2;
  } while ( w >= 1.0 );

  w = sqrt((-2.0 * log(w)) / w);
  boxMuller2Rand = uniform2 * w * stdDev + mean;
  return uniform1 * w * stdDev + mean;
}
