#include "D2SDLmap.h"
#include "../map.h"

D2SDLmap::D2SDLmap()
{
    background = NULL;
    image  = NULL;
    tiles  = NULL;
    tile_w = 1;
    tile_h = 1;
    water_modifier = 0;
    max_style = 16;
    objects = 0;
    //ctor
}

D2SDLmap::~D2SDLmap()
{
    //dtor
}

int D2SDLmap::initialize() {
    background = screen();
    if(!background) {
        return -1;
    }
    SDL_BlitSurface(background, NULL, image, NULL);

    //Clip range for the top left
    for(int i=0; i<terr_types; i++) {
        for(int j=0; j<terr_kinds; j++) {
            clip[i][j].x = j*tile_w;
            clip[i][j].y = i*tile_h;
            clip[i][j].w = tile_w;
            clip[i][j].h = tile_h;
        }
    }

    tiles = new D2SDLimage_old(map_tiles);
    obj   = new D2SDLimage_old("images/terrain/stolb.png");
    printf("Map tiles loaded\n");

    return 0;
}

int D2SDLmap::finalize() {
    SDL_FreeSurface(tiles->image);
    SDL_FreeSurface(image);
    SDL_FreeSurface(background);

    return 0;
}

int D2SDLmap::generateMap(int x, int y, map* m) {
    image = screen();
    if(!image) {
        return -1;
    }

    for(int i=0; i<size_x; i+= pack) {
        for(int j=0; j<size_y; j+= pack) {
            location* loc = NULL;
            int lx = i; // +
            int ly = j; // + y - (size_y/2);

            if(x>=0) lx += x - (size_x/2);
            if(y>=0) ly += y - (size_y/2);

            //printf("x: %d, y: %d; ", lx, ly);

            if((lx>=0)&&(ly>=0)&&(lx<=max_x)&&(ly<=max_y)) {
                loc = m->locations[lx][ly];
                int px = ((i - j) + (size_x - 1)) * (tile_w / 2) / pack;
                int py = ((j + i)               ) * (tile_h / 2) / pack; // - tile_h;

                char locstyle = loc->style;
                char loctype  = loc->loctype;
                char locobj   = loc->object;

                if(loctype == 1)
                {
                    locstyle = (locstyle + water_modifier)%16;//
                }
                if(locstyle>=max_style) locstyle = locstyle % max_style;

                fillMap(px, py, loc->loctype, &clip[loc->loctype][locstyle]);

                if(objects)
                {
                    if(locobj == 1)
                    {
                        if(loctype == 0)
                            fillObj(px, py);
                    }
                }
            }
        }
    }

    return 0;
}

/**
 * Filling image
 * @param x horizontal position
 * @param y vertical position
 * @param id id of the image
 * @return errorcode
 */
int D2SDLmap::fillMap(int x, int y, int id, SDL_Rect* clip = NULL) {
    int x1 = x + x0; //(tile_w * (x - y) ) + x0;
    int y1 = y + y0; //(tile_h * (y + x) ) + y0;

    SDL_Rect offset;
    offset.x = x1;
    offset.y = y1;

    SDL_BlitSurface(tiles->image, clip, image, &offset);

    return 0;
}

/**
 * Filling object
 * @param x horizontal position
 * @param y vertical position
 * @param id id of the image
 * @return errorcode
 */
int D2SDLmap::fillObj(int x, int y) {
    int x1 = x + x0; //(tile_w * (x - y) ) + x0;
    int y1 = y + y0 - 137; //(tile_h * (y + x) ) + y0;

    SDL_Rect offset;
    offset.x = x1;
    offset.y = y1;

    SDL_BlitSurface(obj->image, NULL, image, &offset);

    return 0;
}

/**
 * Showing map
 * @param x horizontal position
 * @param y vertical position
 * @return errorcode
 */
int D2SDLmap::show(int x, int y, SDL_Surface* screen)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(image, NULL, screen, &offset);

    water_modifier++;
    if (water_modifier>=16)
        water_modifier = 0;

    return 0;
}
