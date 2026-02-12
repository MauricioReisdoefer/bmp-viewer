#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        PrintHelp();
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "help") == 0)
        {
            PrintHelp();
            return 0;
        }
    }

    const int WIDTH_RATIO = atoi(argv[1]);
    const int HEIGHT_RATIO = atoi(argv[2]);

    BMP_Image image = BMP_Load(argv[3]);
    if (!image.pixels)
    {
        printf("Failed to load image.\n");
        return 1;
    }

    for (int i = 4; i < argc; i++)
    {
        if (strcmp(argv[i], "bw") == 0)
        {
            image = BMP_Black_And_White(image);
        }
        else if (strcmp(argv[i], "sepia") == 0)
        {
            image = BMP_Sepia(image);
        }
        else if (strcmp(argv[i], "inv") == 0)
        {
            image = BMP_Invert_Colors(image);
        }
        else if (strcmp(argv[i], "bright") == 0)
        {
            if (i + 1 < argc)
            {
                int value = atoi(argv[i + 1]);
                image = BMP_Brightness(image, value);
                i++;
            }
            else
            {
                printf("Missing value for bright.\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "contrast") == 0)
        {
            if (i + 1 < argc)
            {
                int value = atoi(argv[i + 1]);
                image = BMP_Contrast(image, value);
                i++;
            }
            else
            {
                printf("Missing value for contrast.\n");
                return 1;
            }
        }
        else
        {
            printf("Unknown filter: %s\n", argv[i]);
            return 1;
        }
    }

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "BMP Viewer",
        image.width / WIDTH_RATIO,
        image.height / HEIGHT_RATIO,
        0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        image.width,
        image.height);

    SDL_UpdateTexture(
        texture,
        NULL,
        image.pixels,
        image.width * 3);

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
