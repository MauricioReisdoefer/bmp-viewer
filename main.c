#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    const int WIDTH_RATIO = atoi(argv[1]);
    const int HEIGHT_RATIO = atoi(argv[2]);

    BMP_Image image = BMP_Load((argv[3]));

    if (argc > 4 && strcmp(argv[4], "bw") == 0)
    {
        image = BMP_Black_And_White(image);
    }

    if (argc > 4 && strcmp(argv[4], "inv") == 0)
    {
        image = BMP_Invert_Colors(image);
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
