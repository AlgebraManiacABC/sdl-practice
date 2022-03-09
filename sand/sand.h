#include "../lib/mysdl.h"

#define BOX_WIDTH 150
#define BOX_HEIGHT 100
#define WIN_WIDTH 5*BOX_WIDTH
#define WIN_HEIGHT 5*BOX_HEIGHT

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

}   __PART;

typedef __PART * grain;

typedef struct
{
    int w;
    int h;
    grain ** sand;

}   __BOX;

typedef __BOX * sandbox;

void draw_sandbox(sandbox box, SDL_Renderer * r);

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

int add_sand(sandbox box, int x, int y, int material);

grain new_grain(int x, int y, int material);

void remove_sand(sandbox box, int x, int y);

int apply_physics(sandbox box);

int apply_grain_gravity(sandbox box, grain s);

int apply_water_physics(sandbox box, grain s);

bool is_midair(sandbox box, grain s);

void free_sandbox(sandbox box);