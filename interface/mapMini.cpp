#include "mapMini.h"

const char* IMG_USERLOC        = "images/terrain/userloc.png";
const char* MINIMAP_BACKGROUND = "images/minimap.png";

mapMini::mapMini()
{
    x0 = 8; //128 + 5;
    y0 = 8; //40;
    max_style = 4;

    pack = 2;
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
    /*
    int px = ((x - y) + (size_x - 1)) * (tile_w / 2) / pack + x0;
    int py = ((x + y)               ) * (tile_h / 2) / pack + y0;

    SDL_Rect offset;
    offset.x = px;
    offset.y = py;

    D2SDLimage_old* src = NULL;

    src = new D2SDLimage_old(IMG_USERLOC);
    SDL_BlitSurface(src->image, NULL, image, &offset);
    src->free();
    */

    return 0;
}

int mapMini::initialize()
{
    D2SDLimage* image = new D2SDLimage;
    //background->init(tile_w*size_x*2, tile_h*size_y*2);
    image->load(MINIMAP_BACKGROUND);

    background = image;
    printf("Mini background blitted\n");

    return 0;
}


