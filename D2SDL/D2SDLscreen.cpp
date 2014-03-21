#include "D2SDLscreen.h"
#include "D2SDLimage.h"

D2SDLscreen::D2SDLscreen()
{
    screen      = NULL;
    cursor      = NULL;
    loaded      = 0;
    show_cursor = 1;
}

D2SDLscreen::~D2SDLscreen()
{
    screen->free();
}

int D2SDLscreen::loadImage(const char* filename)
{
    screen = new D2SDLimage(filename);
    loaded = (screen != false);

    return loaded;
}

int D2SDLscreen::show(SDLgraph* graph)
{
    if(!loaded && logo_filename){
        printf("Loading %s\n", logo_filename);
        loadImage(logo_filename);
    }

    SDL_ShowCursor(show_cursor);

    if(screen){
        printf("Blitting\n");
        SDL_BlitSurface(screen->image, NULL, graph->screen, NULL);
    }

    int res = graph->flip();

    if(delay){
        SDL_Delay(delay);
    }

    return res;
}
