#include "sand.h"

int main(int argc, char ** argv)
{
    srand((Uint64) main);
    SDL_Window * w;
    SDL_Renderer * r;
    if(mySDL_Init(SDL_INIT_EVERYTHING,&w,DEFAULT_WIN_WIDTH,DEFAULT_WIN_HEIGHT,0,"I don't like sand. It's coarse and rough and irritating, and it gets everywhere.",&r))
    {
        return EXIT_FAILURE;
    }
    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);

    play_Game(r);
    mySDL_Close(LEVEL_REND,r,w);
    return EXIT_SUCCESS;
}