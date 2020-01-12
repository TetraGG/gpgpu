#pragma once

#include "point.h"

typedef struct
{
    point position;
    point center;
    point direction;
} view;

static view current_view =
{
    .position.x = 0.0,
    .position.y = 0.0,
    .position.z = 0.0,
    .center.x = 0.0,
    .center.y = 0.0,
    .center.z = 250.0,
    .direction.x = 0.0,
    .direction.y = 0.0,
    .direction.z = 1.0
};

void set_view(void);
