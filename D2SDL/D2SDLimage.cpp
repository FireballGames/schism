#include <SDL/SDL_image.h>

#include "D2SDLimage.h"

D2SDLimage::D2SDLimage()
{
    //ctor
}

D2SDLimage::~D2SDLimage()
{
    //dtor
}

/**
 * Loading image into SDL
 * @param filename image file
 * @return optimized image
 */
SDL_Surface* D2SDLimage::load(const char* filename, int color_key)
{
    SDL_Surface* image = IMG_Load(filename);

    if(image)
    {
        surface = SDL_DisplayFormat(image);
        SDL_FreeSurface(image);

        if(color_key){
            Uint32 colorkey = SDL_MapRGB(surface->format, 0xFF, 0, 0xFF);
            SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorkey );
        }

        width  = image->w;
        height = image->h;
    }

    return image;
}
