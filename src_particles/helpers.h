#pragma once

#include "defines.h"
#include "particle.h"

static double box_muller = 0.0;
static int frame_count = 0;
static int current_time = 0;
static int previous_time = 0;
static double fps = 0.0;

double random_uniform(double range);
double random_gaussian(double mean, double stddev);
void compute_fps(void);
