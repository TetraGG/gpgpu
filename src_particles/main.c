#include <time.h>
#include <stdlib.h>

#include "emitter.h"

int main(void)
{
    srand(time(NULL));
    particles_init();
    graphics_init();
    // TODO: infinite loop
    while (1);
    return 0;
}
