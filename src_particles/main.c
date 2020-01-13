#include <time.h>
#include <stdlib.h>

#include "emitter.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    particles_init();
    graphics_init(argc, argv);
    // TODO: infinite loop
	graphics_mainloop();
    return 0;
}
