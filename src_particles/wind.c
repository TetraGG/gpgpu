#include "defines.h"
#include "wind.h"

void compute_wind(void)
{
    wind.velocity.x = PARTICLE_MASS * wind.speed * cos(wind.angle * TO_RADIAN) / 10;
    wind.velocity.y = 0;
    wind.velocity.z = PARTICLE_MASS * wind.speed * sin(wind.angle * TO_RADIAN) / 10;
}
