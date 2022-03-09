#include "sand.h"

int main(int argc, char ** argv)
{
    SDL_Window * w;
    SDL_Renderer * r;
    if(mySDL_Init(SDL_INIT_EVERYTHING,&w,WIN_WIDTH,WIN_HEIGHT,0,&r))
    {
        return EXIT_FAILURE;
    }

    play_Game(r);
    mySDL_Close(LEVEL_REND,r,w);
    return EXIT_SUCCESS;
}