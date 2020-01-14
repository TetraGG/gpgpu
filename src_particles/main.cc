#include <iostream>

#include "graphics.hh"
#include "main.hh"
#include "rng.hh"

emitter fire;
double gravity;
wind_t wind;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    particles_init();
    graphics_init(argc, argv);
    graphics_mainloop();
    return 0;
}

void generic_display(void)
{
    graphics_set_view();
    graphics_clear();
    particles_spawn();
    graphics_particles();
    particles_update();
    graphics_refresh();
}

void particles_init(void)
{
    fire.particles_total = PARTICLES_TOTAL;
    fire.particles_alive = 0;
    fire.c.r = SHADE;
    fire.c.g = SHADE;
    fire.c.b = SHADE;
    fire.chaotic_speed = CHAOS_SPEED_VAR;
    gravity = DEFAULT_GRAVITY;
    wind.speed = WIND_INIT_SPEED;
    wind.angle = WIND_INIT_DIRECTION;
    compute_wind();
}

void compute_wind(void)
{
    wind.direction.x = PARTICLE_MASS * wind.speed * cos(TO_RADIAN * wind.angle) / 10;
    wind.direction.z = PARTICLE_MASS * wind.speed * sin(TO_RADIAN * wind.angle) / 10;
}

void particles_spawn(void)
{
    for (size_t index = fire.particles_alive; index < fire.particles_total; ++index)
    {
        fire.particles[index].position.x = random_uniform(EMITTER_SIZE) + EMITTER_X;
        fire.particles[index].position.y = EMITTER_Y;
        fire.particles[index].position.z = random_uniform(EMITTER_SIZE) + EMITTER_Z;
        fire.particles[index].velocity.x = 0.0;
        fire.particles[index].velocity.y = random_gaussian(SPEED_MEAN, SPEED_VAR);
        fire.particles[index].velocity.z = 0.0;
        fire.particles[index].c.r = random_gaussian(fire.c.r, SHADE_INIT_VAR);
        fire.particles[index].c.g = random_gaussian(fire.c.g, SHADE_INIT_VAR);
        fire.particles[index].c.b = random_gaussian(fire.c.b, SHADE_INIT_VAR);
        fire.particles[index].c.a = random_gaussian(INIT_ALHPA_MEAN, INIT_ALPHA_VAR);
        fire.particles[index].texture_id = fire.textures[index % TEXTURE_NUMBER];
        fire.particles_alive++;
    }
}

void particles_update(void)
{
    for (size_t index = 0; index < fire.particles_alive; ++index)
    {
        if ((fire.particles[index].c.r <= PARTICLE_DEATH && fire.particles[index].c.g <= PARTICLE_DEATH &&
                    fire.particles[index].c.b <= PARTICLE_DEATH) || fire.particles[index].c.a <= PARTICLE_DEATH) {
            fire.particles_alive--;
            fire.particles[index] = fire.particles[fire.particles_alive];
        }
        else
        {
            fire.particles[index].position.x += fire.particles[index].velocity.x;
            fire.particles[index].position.z += fire.particles[index].velocity.z;
            fire.particles[index].position.y += fire.particles[index].velocity.y;
            if (fire.particles[index].position.y < EMITTER_Y)
                fire.particles[index].position.y = EMITTER_Y;

            fire.particles[index].velocity.x += random_gaussian(CHAOS_SPEED_MEAN, fire.chaotic_speed) +
                fire.particles[index].position.y * wind.direction.x;
            fire.particles[index].velocity.z += box_muller + fire.particles[index].position.y * wind.direction.z;
            fire.particles[index].velocity.y += PARTICLE_MASS * gravity + random_gaussian(CHAOS_SPEED_MEAN,
                    fire.chaotic_speed * CHAOS_VERTICAL_MUL);

            double shade = random_gaussian(SHADE_CHANGE_MEAN, SHADE_CHANGE_VAR);
            fire.particles[index].c.r -= shade;
            fire.particles[index].c.g -= shade;
            fire.particles[index].c.b -= shade;
            fire.particles[index].c.a -= ALPHA_CHANGE;
        }
    }
}
