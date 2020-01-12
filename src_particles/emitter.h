#pragma once

#include "color.h"
#include "defines.h"
#include "helpers.h"
#include "particle.h"

// Emitter
typedef struct
{
    // Array of particles
    particle particles[MAX_PARTICLES];

    // Total particles
    size_t total_particles;

    // Current particles
    size_t alive_particles;

    // Initial color
    color color;

    // Speed
    double chaotic_speed;

    // Array of textures
    int textures[MAX_TEXTURES];
} emitter;

static double gravity = 0.0;
static emitter fire;

void graphics_init(void);

void particles_init(void);
void particles_spawn(void);
void particles_draw(void);
void particles_update(void);
void particles_display(void);
