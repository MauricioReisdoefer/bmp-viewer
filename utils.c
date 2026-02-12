#include <stdio.h>
#include "utils.h"

void PrintHelp()

{
    printf("BMP_Viewer - MauricioReisdoefer\n\n");

    printf("USAGE:\n");
    printf("  bmp_viewer <width_ratio> <height_ratio> <image.bmp> [filters]\n\n");

    printf("ARGUMENTS:\n");
    printf("  <width_ratio>     Horizontal scale factor (e.g. 1, 2, 4)\n");
    printf("  <height_ratio>    Vertical scale factor (e.g. 1, 2, 4)\n");
    printf("  <image.bmp>       Path to 24-bit BMP file\n\n");

    printf("FILTERS:\n");
    printf("  bw                Convert image to black and white\n");
    printf("  inv               Invert image colors\n");
    printf("  bright <value>    Adjust brightness (-255 to 255)\n\n");

    printf("PROJECT:\n");
    printf("  https://github.com/MauricioReisdoefer/bmp-viewer\n");
}
