#pragma once

#include <stdint.h>

typedef struct UIContext
{
    int mouse_x;
    int mouse_y;

    int mouse_down;
    int mouse_down_last;

    int mouse_pressed;
    int mouse_released;

    uint32_t hot;
    uint32_t active;
    uint32_t focused;
} UIContext;