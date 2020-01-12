#pragma once

#include <math.h>

#include "point.h"

#define TO_RADIAN M_PI / 180.0

typedef struct
{
    point velocity;
    double speed;
    double angle;
} wind_t;

static wind_t wind;

void compute_wind(void);
