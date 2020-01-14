#pragma once

/******************************************************************************
* Import relevant libraries
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

/******************************************************************************
* Simulation parameters
******************************************************************************/
#define POINT_SIZE 3					// Point size (non-textured rendering)
#define DEFAULT_GRAVITY -9.81;			// Default gravitational acceleration
#define MAX_NO_OF_PARTICLES 2000000		// Maximum and default number of
#define DEFAULT_NO_OF_PARTICLES 1000 	// particles in each particle system
#define DEG_TO_RAD 0.017453293 			// Degree to radian conversion

/******************************************************************************
* Smoke particle and smoke definitions
******************************************************************************/

// Constant parameters
#define SMOKE_EMITTER_X 250.0			// Smoke emitter location
#define SMOKE_EMITTER_Y 0.0
#define SMOKE_EMITTER_Z 0.0
#define SMOKE_EMITTER_SIZE 15.0			// Variance of possible particle spawn locations
#define SMOKE_SPEED_MEAN 0.7			// Starting vertical smoke speed
#define SMOKE_SPEED_VAR 0.1
#define SMOKE_CHAOS_SPEED_MEAN 0.0		// Velocity of particle chaotic movement
#define SMOKE_CHAOS_SPEED_VAR 0.002
#define SMOKE_CHAOS_VERTICAL_MUL 2.0	// The chaotic movement is more significant in Y dimension
#define SMOKE_SHADE 0.8					// Initial colour of smoke (gray)
#define SMOKE_SHADE_CHANGE_MEAN 0.0015	// Rate of smoke shade change, mean and variance
#define SMOKE_SHADE_CHANGE_VAR 0.007	// this os for different shades of smoke
#define SMOKE_SHADE_INIT_VAR 0.02		// Initial smoke colour variance
#define SMOKE_INIT_ALHPA_MEAN 0.3		// Mean and variance of initial alpha value
#define SMOKE_INIT_ALPHA_VAR 0.1
#define SMOKE_ALPHA_CHANGE 0.0001		// Rate of alpha change
#define SMOKE_PARTICLE_MASS 0.00002		// affects the impact of gravity
#define SMOKE_COLOUR_CHANGE 0.05 		// How quickly colour is changed due to key presses
#define SMOKE_DEATH_THRES 0.0000001      // Threshold RGB colour and alpha value for killing particle
#define SMOKE_TEXTURE_NUMBER 25			// number of different smoke textures that can be used
#define SMOKE_WIND_DIRECTION_CHANGE 10 	// Delta angle of the wind after key press
#define SMOKE_WIND_INIT_SPEED 0.1		// Initial wind speed and direction (angle)
#define SMOKE_WIND_INIT_DIRECTION 90.0

// Smoke particle
typedef struct {
    double xpos, ypos, zpos;   			// Position
    double xvel, yvel, zvel;   			// Velocity
    double r, g, b, alpha;   			// Current particle colour and aplha value
    int textureID;                      // ID of the texture applied to the particle
} SmokeParticle;

// Smoke
typedef struct {
	SmokeParticle particles[MAX_NO_OF_PARTICLES];	// Array of particles
	int totalParticles; 				// Current total number of particle
	int aliveParticles; 				// Current number of alive particles
	double r;							// Smoke initial colour
	double g;
	double b;
	double chaoticSpeed;				// Speed of chaotic movement
	int textures[SMOKE_TEXTURE_NUMBER];	// Array of smoke texture IDs
} Smoke;

extern Smoke smokeEmitter;

/******************************************************************************
* Function prototypes
******************************************************************************/

void initParticleSystem(); 			// Initialise the particle system
void computeWind();					// Calculate wind vector

void spawnParticles(); 				// Spawn particles

void progressTime(); 				// Update particle parameters according to the laws
void generic_display(); 			// Graphics callback function
