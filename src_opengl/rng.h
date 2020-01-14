#pragma once

/******************************************************************************
* Second random number generated using Box-Muller transform (used for
* improved performance)
******************************************************************************/
extern double boxMuller2Rand;

double uniformRandom(double);			// Uniform random variable generator
double gaussianRandom(double, double);	// Gaussian random variable generator
