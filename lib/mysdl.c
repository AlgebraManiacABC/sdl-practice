#include "mysdl.h"

int mySDL_Init(Uint32 init_flags, SDL_Window ** w, int win_w, int win_h,
    Uint32 win_flags, SDL_Renderer ** r)
{
    if(SDL_Init(init_flags))
    {
        fprintf(stderr,"Initialization failure: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    if(SDL_CreateWindowAndRenderer(win_w,win_h,win_flags,w,r))
    {
        fprintf(stderr,"Window/Renderer creation failure: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int mySDL_Close(int level, ...)
{
    va_list vars;
    va_start(vars,level);
    switch(level)
    {
        case LEVEL_WIN:
            SDL_DestroyWindow(va_arg(vars,SDL_Window*));
        case LEVEL_REND:
            SDL_DestroyRenderer(va_arg(vars,SDL_Renderer*));
        case LEVEL_INIT:
            SDL_Quit();
            break;
        default:
            fprintf(stderr,"Unknown mySDL_Close level!\n");
            va_end(vars);
            return EXIT_FAILURE;
            break;
    }
    va_end(vars);
    return EXIT_SUCCESS;
}