#include "../lib/mysdl.h"

#define WIN_WIDTH 720
#define WIN_HEIGHT 480

void begin(SDL_Renderer * r);

void play_clap_sound();

void fill_audio(void *udata, Uint8 *stream, int len);