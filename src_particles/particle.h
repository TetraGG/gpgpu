#pragma once

#include "color.h"
#include "point.h"

// Particle
typedef struct
{
    // Position
    point position;

    // Velocity
    point velocity;

    // Color
    color color;

    // Texture ID
    int texture_id;
} particle;
