#include "../lib/mysdl.h"

#define WIN_WIDTH 720
#define WIN_HEIGHT 480

int main(int argc, char ** argv)
{
    SDL_Window * w;
    SDL_Renderer * r;
    if(mySDL_Init(SDL_INIT_EVERYTHING,&w,WIN_WIDTH,WIN_HEIGHT,0,&r))
    {
        return EXIT_FAILURE;
    }

    SDL_Delay(5000);

    mySDL_Close(LEVEL_WIN,w,r);
    return EXIT_SUCCESS;
}