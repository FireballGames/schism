#include "D2SDLsurface.h"

const int ERROR_NO_SURFACE = -1;

D2SDLsurface::D2SDLsurface()
{
    x = 0;
    y = 0;
    width  = 100;
    height = 100;

    surface = NULL;
}

D2SDLsurface::~D2SDLsurface()
{
    if(surface)
        SDL_FreeSurface(surface);

    printf("- Surface\n");
}

/**
 * Initializing SDL surface
 * @param int w Surface width
 * @param int h Surface height
 * @return int errorcode
 */
int D2SDLsurface::init(unsigned int w = 0, unsigned int h = 0, bool paint = true)
{
    if(w) width  = w;
    if(h) height = h;

    surface = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);

    if(!paint)
    {
        Uint32 colorkey = SDL_MapRGB(surface->format, 0xFF, 0, 0xFF);
        SDL_FillRect(   surface, NULL,            colorkey );
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorkey );

    }
    printf("+ Surface\n");

    return 0;
}

/**
 * Painting image
 * @param D2SDLgraph graph Main graphical object
 * @return errorcode
 */
int D2SDLsurface::paint(D2SDLsurface* new_surface)
{
    int errorcode = 0;

    if(!surface) return ERROR_NO_SURFACE;

    SDL_Rect r;
    r.x = x;
    r.y = y;

    //if(x) printf("X %d, %d\n", r.x, new_surface->width);
    //if(y) printf("Y %d, %d\n", r.y, new_surface->height);

    errorcode = SDL_BlitSurface(surface, NULL, new_surface->surface, &r);

    if (errorcode<0) printf("%s\n", SDL_GetError());

    return errorcode;
}
