#pragma once

// Gravity
#define DEFAULT_GRAVITY -9.81

// Emitter
#define MAX_PARTICLES 2000000
#define TOTAL_PARTICLES 1000
#define EMITTER_X 0.0
#define EMITTER_Y 0.0
#define EMITTER_Z 250.0
#define EMITTER_SIZE 15.0

// Speed
#define SPEED_MEAN 0.7
#define SPEED_VAR 0.1

// Chaos
#define CHAOS_SPEED_MEAN 0.0
#define CHAOS_SPEED_VAR 0.002
#define CHAOS_VERTICAL_MUL 2.0

// Shade
#define DEFAULT_SHADE 0.8
#define SHADE_CHANGE_MEAN 0.0015
#define SHADE_CHANGE_VAR 0.007
#define SHADE_INIT_VAR 0.02

// Alpha
#define ALPHA_INIT_MEAN 0.3
#define ALPHA_INIT_VAR 0.1
#define ALPHA_CHANGE 0.0001

// Particle
#define PARTICLE_MASS 0.00002
#define PARTICLE_DEATH 0.0000001

// Texture
#define MAX_TEXTURES 25

// Wind
#define WIND_DIRECTION_CHANGE 10
#define WIND_INIT_SPEED 0.1
#define WIND_INIT_DIRECTION 90.0

#define POINT_SIZE 3					// Point size (non-textured rendering)
#define POINT_SIZE_TEXTURE 100			// Point size for textured smoke rendering
#define WINDOW_WIDTH 1450				// Window size
#define WINDOW_HEIGHT 800
