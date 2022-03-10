#include "../lib/mysdl.h"
#include <math.h>

#define BOX_WIDTH 150
#define BOX_HEIGHT 100
#define GRAIN_SIZE 5
#define WIN_WIDTH GRAIN_SIZE*BOX_WIDTH
#define WIN_HEIGHT GRAIN_SIZE*BOX_HEIGHT

#define FALL_SPEED 10
#define EMPTY 0
#define SAND 1
#define WATER 2
#define WOOD 3

typedef struct
{
    int x;
    int y;
    int type;
    SDL_Rect draw;
    bool settled;

}   __PART;

typedef __PART * grain;

typedef struct
{
    int w;
    int h;
    grain ** sand;

}   __BOX;

typedef __BOX * sandbox;

void draw_sandbox(SDL_Rect *background, sandbox box, SDL_Renderer * r, int mouse_x, int mouse_y, int brush_size);

int box_x(int x);

int box_y(int y);

int win_x(int x);

int win_y(int y);

void play_Game(SDL_Renderer *);

/**
 * @brief Create a sandbox in memory with the given sand particle width and height
 * 
 * @param w sandbox width in particles
 * @param h sandbox height in particles
 * @return if success return new sandbox object (pointer). NULL if failure
 */
sandbox create_sandbox(int w, int h);

int add_sand(sandbox box, int x, int y, int material, int brush_size);

grain new_grain(int x, int y, int material);

void remove_sand(sandbox box, int x, int y, int brush_size);

void apply_physics(sandbox box);

void apply_grain_gravity(sandbox box, grain s);

void swap_grains(sandbox box, int x_a, int y_a, int x_b, int y_b);

int apply_water_physics(sandbox box, grain s);

bool in_midair(sandbox box, grain s);

bool above_water(sandbox box, grain s);

void free_sandbox(sandbox box);