#include "mapMini.h"

const char* IMG_USERLOC        = "images/terrain/userloc.png";
const char* MINIMAP_BACKGROUND = "images/minimap.png";

mapMini::mapMini()
{
    x0 = 8; //128 + 5;
    y0 = 8; //40;
    size_x = 256;
    size_y = 256;
    tile_w = 4;
    tile_h = 2;
    map_tiles = "images/terrain/terrain_small.png";
    max_style = 4;

    pack = 4;
}

mapMini::~mapMini()
{
    //dtor
}

SDL_Surface* mapMini::screen() {
    D2SDLimage_old* img = new D2SDLimage_old(MINIMAP_BACKGROUND);

    return img->image;
}

int mapMini::setViewpoint(int x, int y) {
    int px = ((x - y) + (size_x - 1)) * (tile_w / 2) / pack + x0;
    int py = ((x + y)               ) * (tile_h / 2) / pack + y0;

    SDL_Rect offset;
    offset.x = px;
    offset.y = py;

    D2SDLimage_old* src = NULL;

    src = new D2SDLimage_old(IMG_USERLOC);
    SDL_BlitSurface(src->image, NULL, image, &offset);
    src->free();

    return 0;
}
