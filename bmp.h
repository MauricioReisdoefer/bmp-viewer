#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct BMP_FILE_HEADER
{
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint32_t pixel_offset;
} BMP_FILE_HEADER;