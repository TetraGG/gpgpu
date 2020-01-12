#include <stddef.h>

#include "emitter.h"
#include "view.h"
#include "wind.h"

void graphics_init(void)
{
    // TODO: init window and load particles
}

void particles_init(void)
{
    fire.total_particles = TOTAL_PARTICLES;
    fire.alive_particles = 0;
    fire.color.r = DEFAULT_SHADE;
    fire.color.g = DEFAULT_SHADE;
    fire.color.b = DEFAULT_SHADE;
    fire.chaotic_speed = CHAOS_SPEED_VAR;
    gravity = DEFAULT_GRAVITY;
    wind.speed = WIND_INIT_SPEED;
    wind.angle = WIND_INIT_DIRECTION;
    compute_wind();
}

void particles_spawn(void)
{
    for (size_t index = fire.alive_particles; index < fire.total_particles; index++) 
    {
        fire.particles[index].position.x = random_uniform(EMITTER_SIZE) + EMITTER_X;
        fire.particles[index].position.y = EMITTER_Y;
        fire.particles[index].position.z = random_uniform(EMITTER_SIZE) + EMITTER_Z;
        fire.particles[index].velocity.x = 0.0;
        fire.particles[index].velocity.y = random_gaussian(SPEED_MEAN, SPEED_VAR);
        fire.particles[index].velocity.z = 0.0;
        fire.particles[index].color.r = random_gaussian(fire.color.r, SHADE_INIT_VAR);
        fire.particles[index].color.g = random_gaussian(fire.color.g, SHADE_INIT_VAR);
        fire.particles[index].color.b = random_gaussian(fire.color.b, SHADE_INIT_VAR);
        fire.particles[index].color.a = random_gaussian(ALPHA_INIT_MEAN, ALPHA_INIT_VAR);
        fire.particles[index].texture_id = fire.textures[index % MAX_TEXTURES];
        fire.alive_particles++;
    }
}

void particles_draw(void)
{
    // TODO: render particles
}

void particles_update(void)
{
    for (size_t index = 0; index < fire.alive_particles; index++) 
    {
        if ((fire.particles[index].color.r <= PARTICLE_DEATH && fire.particles[index].color.g <= PARTICLE_DEATH
          && fire.particles[index].color.b <= PARTICLE_DEATH) ||fire.particles[index].color.a <= PARTICLE_DEATH)
        {
            fire.particles[index] = fire.particles[fire.alive_particles - 1];
            fire.alive_particles--;
        }
        else
        {
            fire.particles[index].position.x += fire.particles[index].velocity.x;
            fire.particles[index].position.z += fire.particles[index].velocity.z;
            fire.particles[index].position.y += fire.particles[index].velocity.y;
            if (fire.particles[index].position.y < EMITTER_Y)
                fire.particles[index].position.y = EMITTER_Y;

            fire.particles[index].velocity.x += random_gaussian(CHAOS_SPEED_MEAN, fire.chaotic_speed)
                                              + fire.particles[index].position.y * wind.velocity.x;
            fire.particles[index].velocity.z += box_muller + fire.particles[index].position.y * wind.velocity.z;
            fire.particles[index].velocity.y += PARTICLE_MASS * gravity + random_gaussian(CHAOS_SPEED_MEAN,
                                                fire.chaotic_speed * CHAOS_VERTICAL_MUL);

            double shade = random_gaussian(SHADE_CHANGE_MEAN, SHADE_CHANGE_VAR);
            fire.particles[index].color.r -= shade;
            fire.particles[index].color.g -= shade;
            fire.particles[index].color.b -= shade;
            fire.particles[index].color.a -= ALPHA_CHANGE;
        }
    }
}

void particles_display(void)
{
    // TODO: clear image, etc...
    set_view();
    particles_spawn();
    particles_draw();
    particles_update();
    compute_fps();
}
