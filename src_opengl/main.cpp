#include <iostream>

#include "main.h"

#include "graphics.h"

#include "rng.h"

/******************************************************************************
* Particle systems declaration
******************************************************************************/
Smoke smokeEmitter;

/******************************************************************************
* Current value of gravity acceleration
******************************************************************************/
double gravity;


/******************************************************************************
* Global vaiables for wind effect simulation
******************************************************************************/
int angle;
double windSpeed, xWind, zWind;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	initParticleSystem();
	graphics_init(argc, argv);
	graphics_mainloop();
	return 0;
}

void generic_display()
{
  graphics_setView();

  graphics_clear();

  spawnParticles();                     // Generate new particles to replace dead ones
  graphics_particles();
  progressTime();                       // Update particle coordinates and properties

  graphics_refresh();
}

void initParticleSystem()
{
  // Set the initial values of particle system parameters
  smokeEmitter.totalParticles = DEFAULT_NO_OF_PARTICLES;
  smokeEmitter.aliveParticles = 0;
  smokeEmitter.r = smokeEmitter.g = smokeEmitter.b = SMOKE_SHADE;
  smokeEmitter.chaoticSpeed = SMOKE_CHAOS_SPEED_VAR;
  gravity = DEFAULT_GRAVITY;
  windSpeed = SMOKE_WIND_INIT_SPEED;
  angle = SMOKE_WIND_INIT_DIRECTION;
  computeWind();
}

/******************************************************************************
* Calculate the wind vector based on wind angle and speed
******************************************************************************/
void computeWind(void)
{
  xWind = SMOKE_PARTICLE_MASS * windSpeed * cos(DEG_TO_RAD * angle) / 10;
  zWind = SMOKE_PARTICLE_MASS * windSpeed * sin(DEG_TO_RAD * angle) / 10;
}

/******************************************************************************
* Spawn particles
******************************************************************************/
void spawnParticles()
{
  // Dead particles are stored at the end of array, thus no need for 'alive'
  // parameter for each particle
  int index;

  // Spawn smoke particles with only vertical speed being nonzero. Set their initial colour
  // according to the current value of colour parameters (with some random noise). Particles
  // are generated from a square area with linear distribution.
  for (index = smokeEmitter.aliveParticles; index < smokeEmitter.totalParticles; index++)
  {
    smokeEmitter.particles[index].xpos = uniformRandom(SMOKE_EMITTER_SIZE) + SMOKE_EMITTER_X;
    smokeEmitter.particles[index].ypos = SMOKE_EMITTER_Y;
    smokeEmitter.particles[index].zpos = uniformRandom(SMOKE_EMITTER_SIZE) + SMOKE_EMITTER_Z;
    smokeEmitter.particles[index].xvel = 0.0;
    smokeEmitter.particles[index].yvel = gaussianRandom(SMOKE_SPEED_MEAN, SMOKE_SPEED_VAR);
    smokeEmitter.particles[index].zvel = 0.0;
    smokeEmitter.particles[index].r = gaussianRandom(smokeEmitter.r, SMOKE_SHADE_INIT_VAR);
    smokeEmitter.particles[index].g = gaussianRandom(smokeEmitter.g, SMOKE_SHADE_INIT_VAR);
    smokeEmitter.particles[index].b = gaussianRandom(smokeEmitter.b, SMOKE_SHADE_INIT_VAR);
    smokeEmitter.aliveParticles++;
    smokeEmitter.particles[index].alpha = gaussianRandom(SMOKE_INIT_ALHPA_MEAN, SMOKE_INIT_ALPHA_VAR);
    smokeEmitter.particles[index].textureID = smokeEmitter.textures[index % SMOKE_TEXTURE_NUMBER];
  }
}

void progressTime()
{
  int index;
  double shadeChange;

  // Update each smoke particle parameters.
  for (index = 0; index < smokeEmitter.aliveParticles; index++)
  {
    // if the particle has faded out, kill it
    if ((smokeEmitter.particles[index].r <= SMOKE_DEATH_THRES &&
      smokeEmitter.particles[index].g <= SMOKE_DEATH_THRES &&
      smokeEmitter.particles[index].b <= SMOKE_DEATH_THRES) ||
      smokeEmitter.particles[index].alpha <= SMOKE_DEATH_THRES) {
      smokeEmitter.particles[index] = smokeEmitter.particles[smokeEmitter.aliveParticles - 1];
      smokeEmitter.aliveParticles--;
    }

    // Otherwise
    else {
      // Move the particle. If smoke hits the ground, make it crawl on it
      smokeEmitter.particles[index].xpos += smokeEmitter.particles[index].xvel;
      smokeEmitter.particles[index].zpos += smokeEmitter.particles[index].zvel;
      smokeEmitter.particles[index].ypos += smokeEmitter.particles[index].yvel;
      if (smokeEmitter.particles[index].ypos < SMOKE_EMITTER_Y)
        smokeEmitter.particles[index].ypos = SMOKE_EMITTER_Y;

      // Apart from minor gravitational force each particle has some chaotic
      // movement in every dimension and is affected by the wind (direction and speed)
      // The vertical chaotic movement is slighlty faster than horizontal one
      smokeEmitter.particles[index].xvel += gaussianRandom(SMOKE_CHAOS_SPEED_MEAN, smokeEmitter.chaoticSpeed) +
                                            smokeEmitter.particles[index].ypos * xWind;;
      smokeEmitter.particles[index].zvel += boxMuller2Rand + smokeEmitter.particles[index].ypos * zWind;
      smokeEmitter.particles[index].yvel += SMOKE_PARTICLE_MASS * gravity + gaussianRandom(SMOKE_CHAOS_SPEED_MEAN,
                                            smokeEmitter.chaoticSpeed * SMOKE_CHAOS_VERTICAL_MUL);

      // Each particle fades away at slighlty different pace. It both becomes
      // darker and more transparent
      shadeChange = gaussianRandom(SMOKE_SHADE_CHANGE_MEAN, SMOKE_SHADE_CHANGE_VAR);
      smokeEmitter.particles[index].r -= shadeChange;
      smokeEmitter.particles[index].g -= shadeChange;
      smokeEmitter.particles[index].b -= shadeChange;
      smokeEmitter.particles[index].alpha -= SMOKE_ALPHA_CHANGE;
    }
  }
}
