#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 800
#define PIXEL_HEIGHT 5
#define PIXEL_WIDTH 5
#define FOCAL_LENGTH 400.0f
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {
    float x, y, z;
} point;

typedef struct {
    float x, y;
} point2d;

point cube_3d[8];
point2d points_2d[8];

int init_window(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Added SDL_WINDOW_SHOWN just as a best practice, though 0 usually works
    window = SDL_CreateWindow("Spinning cube_3d", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          WIDTH, HEIGHT, 
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    return 0;
}
//Replaces render_cube_3d
void project_points() {
    for (size_t i = 0; i < ARRAY_SIZE(cube_3d); i++){
        float p_x = cube_3d[i].x/cube_3d[i].z * FOCAL_LENGTH;
        float p_y = cube_3d[i].y/cube_3d[i].z * FOCAL_LENGTH;
        
        points_2d[i].x = p_x + (WIDTH / 2.0f);
        points_2d[i].y = -p_y + (HEIGHT / 2.0f);
    }
}

//Draws a point with the origin being the center of the screen
void draw_point(SDL_Renderer *renderer, int x, int y){
    SDL_RenderFillRect(renderer, &(SDL_Rect){x - PIXEL_WIDTH/2, y - PIXEL_WIDTH/2, PIXEL_WIDTH, PIXEL_HEIGHT});
}

void init_cube(){
    //Front Face
    cube_3d[0] = (point){-100, 100, 150};  //Top left front
    cube_3d[1] = (point){-100, -100, 150}; //Bottom left front
    cube_3d[2] = (point){100, -100, 150};   //Bottom right front
    cube_3d[3] = (point){100, 100, 150};  //Top right front
    //Back Face
    cube_3d[4] = (point){-100, 100, 350};  //Top left back
    cube_3d[5] = (point){-100, -100, 350}; //Bottom left back
    cube_3d[6] = (point){100, -100, 350};   //Bottom right back
    cube_3d[7] = (point){100, 100, 350};  //Top right back
}

void translate_z(float dz){
    for(size_t i = 0; i < ARRAY_SIZE(cube_3d); i++){
        cube_3d[i].z += dz;
    }
}

void render_points(){
    for(size_t i = 0; i < ARRAY_SIZE(points_2d); i++){
        draw_point(renderer, (int)points_2d[i].x, (int)points_2d[i].y);
    }
}

void draw_lines(int edges[][2], int length){
    //Connect front face
    for(int i = 0; i < length; i++){
        int a = edges[i][0];
        int b = edges[i][1];

        SDL_RenderDrawLine(renderer, points_2d[a].x, points_2d[a].y, points_2d[b].x, points_2d[b].y);
    }
}


int main(int argc, char *argv[])
{
    if (init_window() != 0){
        return 1;
    }
    // --- The Fix: Using an Event Loop instead of SDL_Delay ---
    int running = 1;
    Uint32 start_time = SDL_GetTicks();
    SDL_Event event;

    int edges[12][2] = {
    // Front Face
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    // Back Face
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    // Connecting Edges
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

    float dz = 0.0f;

    while (running) {
        // 1. Process OS and Window events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }


        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 95, 168, 211, 255);

        //Do stuff here
        init_cube();
        translate_z(dz);
        project_points();
        render_points();
        //apply_rotation();
        draw_lines(edges, 12);
        dz++;
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
