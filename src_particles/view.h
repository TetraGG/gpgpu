#pragma once

#include "point.h"
#include "defines.h"

typedef struct
{
    point position;
    point center;
    point direction;
} view;

/*
static view current_view =
{
    .position.x = EMITTER_X - 400,
    .position.y = EMITTER_Y,
    .position.z = EMITTER_Z,
    .center.x = EMITTER_X,
    .center.y = EMITTER_Y + 200,
    .center.z = EMITTER_Z,
    .direction.x = 0.0,
    .direction.y = 1.0,
    .direction.z = 0.0
};
*/

static view current_view =
{
    .position.x = 0.0,
    .position.y = 240.0,
    .position.z = 500.0,
    .center.x = 0.0,
    .center.y = 240.,
    .center.z = 0.,
    .direction.x = 0.0,
    .direction.y = 1.0,
    .direction.z = 0.0
};


void set_view(void);
