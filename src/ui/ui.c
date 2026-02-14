#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "ui.h"

uint32_t UI_GenerateID(const char *label)
{
    if (!label)
    {
        return 0;
    }

    uint32_t hash = 2166136261U;

    while (*label)
    {
        hash ^= (unsigned char)(*label++);
        hash *= 16777619U;
    }

    return hash;
}