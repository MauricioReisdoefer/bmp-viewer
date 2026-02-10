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

    if (file_header->signature == 0x4D42)
    {
        printf("Is a Bitmap image\n");
    }
    else
    {
        printf("Is not a Bitmap image\n");
        printf("%" PRIu16 "\n", file_header->signature);
    }
}