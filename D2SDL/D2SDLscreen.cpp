#include "D2SDLscreen.h"
#include "D2SDLimage.h"

D2SDLscreen::D2SDLscreen()
{
    screen = NULL;
    //ctor
}

D2SDLscreen::~D2SDLscreen()
{
    //dtor
}

int D2SDLscreen::loadImage(const char* filename)
{
    screen = new D2SDLimage(filename);

    return 0;
}

int D2SDLscreen::show(SDLgraph* graph)
{
    if(logo_filename)
    {
        loadImage(logo_filename);
    }
    if(screen)
    {
        /*
        const int x = 0;
        const int y = 0;

        SDL_Rect offset;
        offset.x = x;
        offset.y = y;
        */

        SDL_BlitSurface(screen->image, NULL, graph->screen, NULL);
        screen->free();
    }

    int res = graph->flip();

    if(delay)
    {
        SDL_Delay(delay);
    }

    return res;
}
