#include "D2SDLsurface.h"

D2SDLsurface::D2SDLsurface()
{
    surface = NULL;
}

D2SDLsurface::~D2SDLsurface()
{
    //dtor
}

/**
 * Initializing SDL surface
 * @param int w Surface width
 * @param int h Surface height
 * @return int errorcode
 */
int D2SDLsurface::init(int w, int h)
{
    surface = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0);

    return 0;
}

/**
 * Freeing image from SDL
 * @return errorcode
 */
int D2SDLsurface::free()
{
    SDL_FreeSurface(surface);
    return 0;
}

/**
 * Painting image
 * @param D2SDLgraph graph Main graphical object
 * @return errorcode
 */
int D2SDLsurface::paint(D2SDLgraph* graph);
{
    int errorcode = 0;

    if(!surface)
        return -1;

    errorcode = SDL_BlitSurface(surface, NULL, graph->screen, NULL);

    if (errorcode<0)
    {
        printf("%s\n", SDL_GetError());
    }

    return errorcode;
}
