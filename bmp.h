#pragma once

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct BMP_FILE_HEADER
{
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint32_t pixel_offset;
} BMP_FILE_HEADER;

typedef struct BMP_INFO_HEADER
{
    uint32_t info_header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} BMP_INFO_HEADER;

typedef struct BMP_Image
{
    int width;
    int height;
    unsigned char *pixels;
} BMP_Image;

BMP_Image BMP_Load(const char *filename);
void BMP_Free(BMP_Image *image);
unsigned char *BMP_Get_Image(char image_name[]);

BMP_Image BMP_Black_And_White(BMP_Image image);
BMP_Image BMP_Invert_Colors(BMP_Image image);
BMP_Image BMP_Brightness(BMP_Image image, int brightness);
BMP_Image BMP_Contrast(BMP_Image image, float contrast);