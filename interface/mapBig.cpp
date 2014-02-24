#include "mapBig.h"

mapBig::mapBig()
{
    tile_w = 118; //100;
    tile_h =  60; // 50;
    size_x = 20;
    size_y = 20;
    x0 = -tile_w*(size_x+1)/4;
    y0 = -tile_h*(size_y+1)/4;
    map_tiles = "images/terrain/terrain.png";

    pack = 1;
}

mapBig::~mapBig()
{
    //dtor
}

SDL_Surface* mapBig::screen() {
    D2SDLimage* img = new D2SDLimage("images/logo_sdl.bmp"); //"images/background.bmp"

    return img->image;
}
