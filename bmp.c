#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "bmp.h"

unsigned char *BMP_Get_Image(char image_name[])
{

    FILE *bitmap_image = fopen(image_name, "rb");
    if (bitmap_image == NULL)
    {
        printf("Image could not be open\n");
        return NULL;
    }

    BMP_FILE_HEADER *file_header = malloc(sizeof(BMP_FILE_HEADER));
    BMP_INFO_HEADER *info_header = malloc(sizeof(BMP_INFO_HEADER));

    if (!file_header || !info_header)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    fread(file_header, sizeof(BMP_FILE_HEADER), 1, bitmap_image);
    fread(info_header, sizeof(BMP_INFO_HEADER), 1, bitmap_image);

    if (file_header->signature != 0x4D42)
    {
        printf("Is not a Bitmap image\n");
        return NULL;
    }

    if (info_header->bits_per_pixel != 24)
    {
        printf("It's not 24 bit\n");
        return NULL;
    }
    if (info_header->compression != 0)
    {
        printf("Compression is not 0\n");
        return NULL;
    }

    fseek(bitmap_image, file_header->pixel_offset, SEEK_SET);

    int width = info_header->width;
    int height = info_header->height;

    int bytes_per_pixel = 3;
    int row_bytes = width * bytes_per_pixel;

    int padding = (4 - (row_bytes % 4)) % 4;
    int stride = row_bytes + padding;

    unsigned char *row_buffer = malloc(stride);
    unsigned char *image = malloc(width * height * 3);

    for (int y = 0; y < height; y++)
    {
        fread(row_buffer, 1, stride, bitmap_image);

        int target_y = height - 1 - y;

        for (int x = 0; x < width; x++)
        {
            int src = x * 3;
            int dst = (target_y * width + x) * 3;

            image[dst + 0] = row_buffer[src + 2]; // R
            image[dst + 1] = row_buffer[src + 1]; // G
            image[dst + 2] = row_buffer[src + 0]; // B
        }
    }

    free(row_buffer);

    free(info_header);
    free(file_header);

    return image;
}