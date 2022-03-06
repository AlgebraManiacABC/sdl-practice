#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdarg.h>

#define LEVEL_WIN 2
#define LEVEL_REND 1
#define LEVEL_INIT 0

int mySDL_Init(Uint32 init_flags, SDL_Window ** w, int win_w, int win_h, Uint32 win_flags, SDL_Renderer ** r);

int mySDL_Close(int level, ...);