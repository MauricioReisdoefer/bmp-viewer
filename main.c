#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "bmp.h"

int main()
{

    FILE *bitmap_image = fopen("bitmap_image.bmp", "rb");
    if (bitmap_image == NULL)
    {
        printf("Image could not be open\n");
        return -1;
    }

    BMP_FILE_HEADER *file_header = malloc(sizeof(BMP_FILE_HEADER));
    BMP_INFO_HEADER *info_header = malloc(sizeof(BMP_INFO_HEADER));

    if (!file_header || !info_header)
    {
        printf("Memory allocation failed\n");
        return -1;
    }

    fread(file_header, sizeof(BMP_FILE_HEADER), 1, bitmap_image);
    fread(info_header, sizeof(BMP_INFO_HEADER), 1, bitmap_image);

    if (file_header->signature != 0x4D42)
    {
        printf("Is not a Bitmap image\n");
    }

    fseek(bitmap_image, file_header->pixel_offset, SEEK_SET);

    if (info_header->bits_per_pixel != 24)
    {
        printf("It's not 24 bit\n");
        return 0;
    }
    if (info_header->compression != 0)
    {
        printf("Compression is not 0\n");
        return 0;
    }
    free(info_header);
    free(file_header);
}