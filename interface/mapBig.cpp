#include "mapBig.h"

const char* MAP_TILES = "images/terrain/terrain.png";

mapBig::mapBig()
{
    tile_w = 118; //100;
    tile_h =  60; // 50;
    size_x = (4 * 1024) / tile_w;
    size_y = (4 *  768) / tile_h;

    printf("%d %d\n", size_x, size_y);

    x0 = -tile_w*(size_x+1)/4;
    y0 = -tile_h*(size_y+1)/4;

    map_tiles = new char[strlen(MAP_TILES)];
    map_tiles = strcpy(map_tiles, MAP_TILES);

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
    surface->init(1024, 768);

    return surface->surface;
}
