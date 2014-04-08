#include "mapBig.h"

const char* MAP_TILES = "images/terrain/terrain.png";

mapBig::mapBig()
{
    pack = 1;
    objects = 1;
}

mapBig::~mapBig()
{
    //dtor
}

SDL_Surface* mapBig::screen() {
    //D2SDLimage_old* img = new D2SDLimage_old("images/logo_sdl.bmp"); //"images/background.bmp"

    D2SDLsurface* surface = new D2SDLsurface();
    surface->init(1024 * 2, 768 *  2, false);

    return surface->surface;
}
