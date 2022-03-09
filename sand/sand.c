#include "sand.h"

void draw_sandbox(SDL_Rect *background, sandbox box, SDL_Renderer * r, int mx, int my, int brush_size)
{
    static SDL_Rect brush;
    brush.h = brush_size*GRAIN_SIZE;
    brush.w = brush_size*GRAIN_SIZE;
    brush.x = win_x(box_x(mx) - brush_size/2);
    brush.y = win_y(box_y(my) - brush_size/2);

    int c[][4] =   //  [Material][RGBA]
    {
        {0,0,0,255},        //  EMPTY
        {237,201,175,255},  //  SAND
        {65,102,245,255},   //  WATER
        {89,39,32,255}      //  WOOD
    };

    SDL_SetRenderDrawColor(r,0,0,0,255);
    SDL_RenderClear(r);
    SDL_RenderFillRect(r,background);

    grain g;
    for(int i=0; i<box->h; i++)
    {
        for(int j=0; j<box->w; j++)
        {
            g = box->sand[i][j];
            if(!g)
                continue;
            SDL_SetRenderDrawColor(r,c[g->type][0],c[g->type][1],c[g->type][2],c[g->type][3]);
            SDL_RenderFillRect(r,&(g->draw));
        }
    }
    SDL_SetRenderDrawColor(r,255,255,255,50);
    SDL_RenderFillRect(r,&brush);

    SDL_RenderPresent(r);
}

int box_x(int x)
{
    return x/GRAIN_SIZE;
}

int box_y(int y)
{
    return y/GRAIN_SIZE;
}

int win_x(int x)
{
    return x*GRAIN_SIZE;
}

int win_y(int y)
{
    return y*GRAIN_SIZE;
}

void play_Game(SDL_Renderer * r)
{
    bool close = false;
    SDL_Event event;
    sandbox box = create_sandbox(BOX_WIDTH,BOX_HEIGHT);
    SDL_Rect background = {0,0,WIN_WIDTH,WIN_HEIGHT};
    int material = EMPTY;
    int brush_size = 1;
    if(!box)
    {
        fprintf(stderr,"Sandbox creation failure!\n");
        return;
    }

    while(!close)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    close = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_1:
                            material = SAND;
                            break;
                        case SDL_SCANCODE_2:
                            material = WATER;
                            break;
                        case SDL_SCANCODE_3:
                            material = WOOD;
                            break;
                        case SDL_SCANCODE_0:
                            material = EMPTY;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    if(event.wheel.y > 0)   //  Scroll up
                    {
                        if(brush_size<20) brush_size++;
                    }
                    else if(event.wheel.y < 0)  //  Scroll down
                    {
                        if(brush_size>1) brush_size--;
                    }
                default:
                    break;
            }
        }

        int mouse_x, mouse_y;
        Uint32 buttons = SDL_GetMouseState(&mouse_x,&mouse_y);

        if(buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
            add_sand(box,box_x(mouse_x),box_y(mouse_y),material,brush_size);
        if(buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
            remove_sand(box,box_x(mouse_x),box_y(mouse_y),brush_size);

        draw_sandbox(&background,box,r,mouse_x,mouse_y,brush_size);

        SDL_Delay(1000/60);
    }
    free_sandbox(box);
}

sandbox create_sandbox(int w, int h)
{
    sandbox sb = malloc(sizeof(__BOX));
    if(!sb)
        return NULL;

    sb->h = h;
    sb->w = w;
    sb->sand = malloc(sizeof(grain*)*h);
    if(!sb->sand)
    {
        free_sandbox(sb);
        return NULL;
    }
    for(int i=0; i<h; i++)
    {
        sb->sand[i] = malloc(sizeof(grain)*w);
        if(!sb->sand[i])
        {
            free_sandbox(sb);
            return NULL;
        }
        for(int j=0; j<w; j++)
            sb->sand[i][j] = NULL;
    }
    return sb;
}

int add_sand(sandbox box, int x, int y, int material, int brush_size)
{
    if(material == EMPTY)
        remove_sand(box,x,y,brush_size);

    int low_half = brush_size/2;
    int up_half  = ceil((float)brush_size/2);

    for(int h=y-low_half; h<y+up_half; h++)
    {
        for(int w=x-low_half; w<x+up_half; w++)
        {
            if(h < 0 || h > BOX_HEIGHT-1 || w < 0 || w > BOX_WIDTH-1)
                continue;
            if(box->sand[h][w])
                continue;
            box->sand[h][w] = new_grain(w,h,material);
        }
    }
    return EXIT_SUCCESS;
}

grain new_grain(int x, int y, int material)
{
    switch(material)
    {
        case SAND:
        case WATER:
        case WOOD:
            break;
        default:
            return NULL;
            break;
    }
    if(x < 0 || x > BOX_WIDTH)
        return NULL;
    if(y < 0 || y > BOX_HEIGHT)
        return NULL;

    grain p = malloc(sizeof(__PART));
    SDL_Rect rect = {win_x(x),win_y(y),5,5};
    __PART part = {x,y,material,rect};
    *p = part;
    return p;
}

void remove_sand(sandbox box, int x, int y, int brush_size)
{
    int low_half = brush_size/2;
    int up_half  = ceil((float)brush_size/2);

    for(int h=y-low_half; h<y+up_half; h++)
    {
        for(int w=x-low_half; w<x+up_half; w++)
        {
            if(h < 0 || h > BOX_HEIGHT-1 || w < 0 || w > BOX_WIDTH-1)
                continue;
            if(box->sand[h][w])
            {
                free(box->sand[h][w]);
                box->sand[h][w] = NULL;
            }
        }
    }
}

void free_sandbox(sandbox sb)
{
    if(!sb && !sb->sand)
        return;
    else if(!sb->sand)
    {
        free(sb);
        return;
    }

    for(int i=0; i<sb->h; i++)
    {
        if(!sb->sand[i])
            continue;
        for(int j=0; j<sb->w; j++)
        {
            if(sb->sand[i][j])
                free(sb->sand[i][j]);
        }
        free(sb->sand[i]);
    }

    free(sb->sand);
    free(sb);
}