#include "clap.h"

void begin(SDL_Renderer * r)
{
    SDL_Texture *hands_sheet = NULL;
    SDL_Surface *temp = IMG_Load("claps.png");
    if(!temp)
    {
        fprintf(stderr,"Surface creation failure: %s\n",SDL_GetError());
        return;
    }
    hands_sheet = SDL_CreateTextureFromSurface(r,temp);
    if(!hands_sheet)
    {
        fprintf(stderr,"Texture creation failure: %s\n",SDL_GetError());
        return;
    }
    SDL_FreeSurface(temp);

    SDL_Rect clap = {0,0,0,0};  //  x,y,w,h
    SDL_Rect screen = {0,0,250,250};

    SDL_QueryTexture(hands_sheet,NULL,NULL,&clap.w,&clap.h);
    clap.w /= 4;

    bool close = false;
    bool clapping_clap = false;
    bool clapping_release = false;
    int frame = 0;
    SDL_Event event;
    while(!close)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    close = true;
                default:
                    break;
            }
        }

        int mouse_x, mouse_y;
        int click = SDL_GetMouseState(&mouse_x,&mouse_y);

        if(click & SDL_BUTTON(SDL_BUTTON_LEFT))
            if(!clapping_release) clapping_clap = true;

        switch(frame)
        {
            case 0:
                if(clapping_clap)
                    frame++;
                else if(clapping_release)
                    clapping_release = false;
                break;
            case 1:
            case 2:
                if(clapping_clap)
                    frame++;
                else if(clapping_release)
                    frame--;
                break;
            case 3:
                play_clap_sound();
                clapping_clap = false;
                clapping_release = true;
                frame--;
                break;
        }
        
        clap.x = frame * 500;
        screen.x = mouse_x - (screen.w/2);
        screen.y = mouse_y - (screen.h/2);

        SDL_RenderClear(r);
        SDL_RenderCopy(r,hands_sheet,&clap,&screen);
        SDL_RenderPresent(r);
        SDL_Delay(1000/60);
    }
}

void play_clap_sound()
{
    SDL_AudioSpec wanted;
    extern void fill_audio(void *udata, Uint8 *stream, int len);

    /* Set the audio format */
    wanted.freq = 22050;
    wanted.format = AUDIO_S16;
    wanted.channels = 2;    /* 1 = mono, 2 = stereo */
    wanted.samples = 1024;  /* Good low-latency value for callback */
    wanted.callback = fill_audio;
    wanted.userdata = NULL;

    /* Open the audio device, forcing the desired format */
    if ( SDL_OpenAudio(&wanted, NULL) < 0 )
    {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        return;
    }

    
    ///
    ///

    static Uint8 *audio_chunk;
    static Uint32 audio_len;
    static Uint8 *audio_pos;


    /* Load the audio data ... */

    ;;;;;

    audio_pos = audio_chunk;

    /* Let the callback function play the audio chunk */
    SDL_PauseAudio(0);

    /* Do some processing */

    ;;;;;

    /* Wait for sound to complete */
    while ( audio_len > 0 ) {
        SDL_Delay(100);         /* Sleep 1/10 second */
    }
    SDL_CloseAudio();
}

/* The audio function callback takes the following parameters:
stream:  A pointer to the audio buffer to be filled
len:     The length (in bytes) of the audio buffer
*/
void fill_audio(void *udata, Uint8 *stream, int len)
{
    /* Only play if we have data left */
    if ( audio_len == 0 )
        return;

    /* Mix as much data as possible */
    len = ( len > audio_len ? audio_len : len );
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}