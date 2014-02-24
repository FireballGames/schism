#include "mapMini.h"

const char* IMG_USERLOC = "images/terrain/userloc.png";

mapMini::mapMini()
{
    x0 = 8; //128 + 5;
    y0 = 48; //40;
    size_x = 256;
    size_y = 256;
    tile_w = 4;
    tile_h = 2;
    map_tiles = "images/terrain/terrain_small.png";

    pack = 4;
}

mapMini::~mapMini()
{
    //dtor
}

SDL_Surface* mapMini::screen() {
    D2SDLimage* img = new D2SDLimage("images/minimap.png");

    return img->image;
}

int mapMini::setViewpoint(int x, int y) {
    int px = ((x - y) + (size_x - 1)) * (tile_w / 2) / pack + x0;
    int py = ((x + y)               ) * (tile_h / 2) / pack + y0;

    SDL_Rect offset;
    offset.x = px;
    offset.y = py;

    D2SDLimage* src = NULL;

    src = new D2SDLimage(IMG_USERLOC);
    SDL_BlitSurface(src->image, NULL, image, &offset);
    src->free();

    return 0;
}
