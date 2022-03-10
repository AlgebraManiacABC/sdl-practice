#include "sand.h"

int main(int argc, char ** argv)
{
    srand((Uint64) main);
    SDL_Window * w;
    SDL_Renderer * r;
    if(mySDL_Init(SDL_INIT_EVERYTHING,&w,WIN_WIDTH,WIN_HEIGHT,0,&r))
    {
        return EXIT_FAILURE;
    }
    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);

    play_Game(r);
    mySDL_Close(LEVEL_REND,r,w);
    return EXIT_SUCCESS;
}