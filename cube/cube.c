#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct {
    SDL_rect pixel;
} Corner;



int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Added SDL_WINDOW_SHOWN just as a best practice, though 0 usually works
    SDL_Window* window = SDL_CreateWindow("Spinning Cube", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          WIDTH, HEIGHT, 
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // --- The Fix: Using an Event Loop instead of SDL_Delay ---
    int running = 1;
    Uint32 start_time = SDL_GetTicks();
    SDL_Event event;

    static Corner cube[] = {{-1, -1, -1}};

    while (running) {
        // 1. Process OS and Window events (This makes Wayland happy!)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        //Do stuff here

        // 2. Perform rendering

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
        SDL_RenderFillRect(renderer, &(SDL_Rect){WIDTH/2, HEIGHT/2, 10, 10});
        SDL_RenderPresent(renderer);

        // 4. Brief pause to prevent the loop from maxing out your CPU
        SDL_Delay(16); 
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
