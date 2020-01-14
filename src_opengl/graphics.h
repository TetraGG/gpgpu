#ifndef GRAPHICS_H_
#define GRAPHICS_H_

void graphics_init(int argc, char *argv[]);
void graphics_clear();
void graphics_refresh();

void graphics_mainloop();

void graphics_particles();

void graphics_reshape(int width, int height);

void graphics_setView();

#endif
