#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "bmp.h"
#include "utils.h"

BMP_Image BMP_Load(const char *filename)
{
    BMP_Image result = {0};

    FILE *bitmap_image = fopen(filename, "rb");
    if (!bitmap_image)
    {
        printf("Image could not be open\n");
        return result;
    }

    BMP_FILE_HEADER file_header;
    BMP_INFO_HEADER info_header;

    fread(&file_header, sizeof(BMP_FILE_HEADER), 1, bitmap_image);
    fread(&info_header, sizeof(BMP_INFO_HEADER), 1, bitmap_image);

    fclose(bitmap_image);

    if (file_header.signature != 0x4D42)
    {
        printf("Is not a Bitmap image\n");
        return result;
    }

    result.width = info_header.width;
    result.height = info_header.height;
    result.pixels = BMP_Get_Image((char *)filename);

    return result;
}

void BMP_Free(BMP_Image *image)
{
    if (image && image->pixels)
    {
        free(image->pixels);
        image->pixels = NULL;
    }
}

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

            image[dst + 0] = row_buffer[src + 2];
            image[dst + 1] = row_buffer[src + 1];
            image[dst + 2] = row_buffer[src + 0];
        }
    }

    free(row_buffer);
    free(info_header);
    free(file_header);
    fclose(bitmap_image);

    return image;
}

BMP_Image BMP_Black_And_White(BMP_Image image)
{
    for (int i = 0; i < image.height * image.width * 3; i += 3)
    {
        int R = image.pixels[i];
        int G = image.pixels[i + 1];
        int B = image.pixels[i + 2];
        float gray = 0.299f * R + 0.587f * G + 0.114f * B;

        image.pixels[i] = gray;
        image.pixels[i + 1] = gray;
        image.pixels[i + 2] = gray;
    }
    return image;
}

BMP_Image BMP_Invert_Colors(BMP_Image image)
{
    for (int i = 0; i < image.height * image.width * 3; i += 3)
    {
        int R = image.pixels[i];
        int G = image.pixels[i + 1];
        int B = image.pixels[i + 2];

        image.pixels[i] = 255 - R;
        image.pixels[i + 1] = 255 - G;
        image.pixels[i + 2] = 255 - B;
    }
    return image;
}

BMP_Image BMP_Brightness(BMP_Image image, int brightness)
{
    for (int i = 0; i < image.height * image.width * 3; i += 3)
    {
        image.pixels[i] = Clamp(brightness + image.pixels[i], 255, 0);
        image.pixels[i + 1] = Clamp(brightness + image.pixels[i + 1], 255, 0);
        image.pixels[i + 2] = Clamp(brightness + image.pixels[i + 2], 255, 0);
    }
    return image;
}

BMP_Image BMP_Contrast(BMP_Image image, float contrast)
{
    for (int i = 0; i < image.height * image.width * 3; i += 3)
    {
        image.pixels[i] = Clamp((image.pixels[i] - 128) * contrast + 128, 255, 0);
        image.pixels[i + 1] = Clamp((image.pixels[i + 1] - 128) * contrast + 128, 255, 0);
        image.pixels[i + 2] = Clamp((image.pixels[i + 2] - 128) * contrast + 128, 255, 0);
    }
    return image;
}

BMP_Image BMP_Sepia(BMP_Image image)
{
    for (int i = 0; i < image.height * image.width * 3; i += 3)
    {
        int R = image.pixels[i];
        int G = image.pixels[i + 1];
        int B = image.pixels[i + 2];

        float newR = 0.393f * R + 0.769 * G + 0.189 * B;
        float newG = 0.349f * R + 0.686 * G + 0.168 * B;
        float newB = 0.272f * R + 0.534 * G + 0.131 * B;

        image.pixels[i] = Clamp(newR, 255, 0);
        image.pixels[i + 1] = Clamp(newG, 255, 0);
        image.pixels[i + 2] = Clamp(newB, 255, 0);
    }
    return image;
}