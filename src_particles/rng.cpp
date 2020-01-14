#include <cmath>

#include "rng.hh"

double random_uniform(double range)
{
  return (rand() / (double)RAND_MAX * 2.0 - 1.0) * range;
}

double random_gaussian(double mean, double stddev)
{
  double uniform_first = 0.0;
  double uniform_second = 0.0;
  double w = 0.0;

  do {
    uniform_first = random_uniform(1.0);
    uniform_second = random_uniform(1.0);
    w = uniform_first * uniform_first + uniform_second * uniform_second;
  } while ( w >= 1.0 );

  w = sqrt((-2.0 * log(w)) / w);
  box_muller = uniform_second * w * stddev + mean;
  return uniform_first * w * stddev + mean;
}
