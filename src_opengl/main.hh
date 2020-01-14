#pragma once

#include <cmath>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "point.hh"

#define PARTICLES_MAX 2000000
#define PARTICLES_TOTAL 1000
#define PARTICLE_MASS 0.00002
#define PARTICLE_DEATH 0.0000001

#define EMITTER_X 250.0
#define EMITTER_Y 0.0
#define EMITTER_Z 0.0
#define EMITTER_SIZE 15.0

#define SPEED_MEAN 0.7
#define SPEED_VAR 0.1

#define CHAOS_SPEED_MEAN 0.0
#define CHAOS_SPEED_VAR 0.002
#define CHAOS_VERTICAL_MUL 2.0

#define SHADE 0.8
#define SHADE_CHANGE_MEAN 0.0015
#define SHADE_CHANGE_VAR 0.007
#define SHADE_INIT_VAR 0.02

#define INIT_ALHPA_MEAN 0.3
#define INIT_ALPHA_VAR 0.1
#define ALPHA_CHANGE 0.0001
#define COLOUR_CHANGE 0.05
#define TEXTURE_NUMBER 25

#define WIND_DIRECTION_CHANGE 10
#define WIND_INIT_SPEED 0.1
#define WIND_INIT_DIRECTION 90.0

#define DEFAULT_GRAVITY -9.81
#define TO_RADIAN M_PI / 180

typedef struct {
    double r;
    double g;
    double b;
    double a;
} colour;

typedef struct {
    point position;
    point velocity;
    colour c;
    int texture_id;
} particle;

typedef struct {
    particle particles[PARTICLES_MAX];
    size_t particles_total;
    size_t particles_alive;
    colour c;
    double chaotic_speed;
    int textures[TEXTURE_NUMBER];
} emitter;

typedef struct {
    point direction;
    int angle;
    double speed;
} wind_t;

static emitter fire;
double gravity;
wind_t wind;

void particles_init(void);

void compute_wind(void);

void particles_spawn(void);

void particles_update(void);

void generic_display(void);
