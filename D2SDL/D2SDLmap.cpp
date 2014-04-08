#include "D2SDLmap.h"
#include "../map.h"

D2SDLmap::D2SDLmap()
{
    background = NULL;
    image      = NULL;

    tiles      = NULL;
    obj        = NULL;
    tiles_old  = NULL;
    obj_old    = NULL;

    tile_w = 1;
    tile_h = 1;

    water_modifier = 0;
    max_style      = 16;
    objects        = 0;
}

D2SDLmap::~D2SDLmap()
{
    //dtor
}

int D2SDLmap::initialize()
{
    /*
    background = screen();
    if(!background)
    {
        return -1;
    }
    SDL_BlitSurface(background, NULL, image, NULL);
    */
    background = new D2SDLsurface;
    background->init(tile_w*size_x*2, tile_h*size_y*2);
    printf("Background blitted\n");


    //Clip range for the top left
    for(int i=0; i<terr_types; i++) {
        for(int j=0; j<terr_kinds; j++) {
            clip[i][j].x = j*tile_w;
            clip[i][j].y = i*tile_h;
            clip[i][j].w = tile_w;
            clip[i][j].h = tile_h;
        }
    }
    printf("Rects set\n");

    /*
    tiles_old = new D2SDLimage_old(map_tiles);
    obj_old   = new D2SDLimage_old("images/terrain/stolb.png");
    printf("Old tiles\n");
    */

    tiles = new D2SDLimage;
    obj   = new D2SDLimage;
    tiles->load(map_tiles);
    obj->load("images/terrain/stolb.png");
    printf("New tiles\n");

    printf("Map tiles loaded\n");

    return 0;
}

int D2SDLmap::finalize() {
    //SDL_FreeSurface(tiles_old->image);
    //SDL_FreeSurface(obj_old->image);
    //SDL_FreeSurface(image);
    //SDL_FreeSurface(background);

    return 0;
}

void D2SDLmap::loadTiles(unsigned int w, unsigned int h, const char* filename)
{
    tile_w = w; //100;
    tile_h = h; // 50;

    map_tiles = new char[strlen(filename)];
    map_tiles = strcpy(map_tiles, filename);

    //x0 = 0; //-tile_w*(size_x+1)/2;
    //y0 = 0; //-tile_h*(size_y+1)/2;
    printf("Size is set\n");

    initialize();

    printf("Map initialized\n");
}

int D2SDLmap::generateMap(int x, int y, map* m) {
    /*
    image = screen();
    if(!image) {
        return -1;
    }
    */
    background->paint(surface);

    printf("size_x %d, size_y %d\n", size_x, size_y);

    for(unsigned int i=0; i<size_x; i+= pack) {
        for(unsigned int j=0; j<size_y; j+= pack) {
            unsigned int lx = i + x - (size_x/2); // +
            unsigned int ly = j + y - (size_y/2); // + y - (size_y/2);
            //printf("Searching location\n");

            if((lx>=0)&&(ly>=0)&&(lx<max_x)&&(ly<max_y)) {
                location* loc = m->locations[lx][ly];
                int px = isometric_x(i, j); //*tile_w;
                int py = isometric_y(i, j); //*tile_h;
                //printf("Transponing location\n");

                unsigned int loctype  = loc->loctype;
                unsigned int locstyle = loc->style;
                //unsigned int locobj   = loc->object;

                //Modifying water style
                if(loctype == 1)
                {
                    locstyle = (locstyle + (water_modifier/8))%16;//
                }
                if(locstyle>=max_style) locstyle = locstyle % max_style;
                water_modifier++;
                if(water_modifier>256) water_modifier = 0;

                //Filling map with current tile
                fillMap(px, py, loc->loctype, &clip[loc->loctype][locstyle]);
                if((!lx)&&(!ly))
                    printf("x0, y0: (%d, %d) (%d, %d)\n", i, j, px, py);

                //Filling map with objects
                /*
                if(objects)
                {
                    if(locobj == 1)
                    {
                        if(loctype == 0)
                            fillObj(px, py);
                    }
                }
                */
                //printf("(%d, %d)%d,", i, j, loctype);
            }
        }
        //printf("\n");

    }

    return 0;
}

/**
 * Filling map with tile
 * @param x horizontal position of tile
 * @param y vertical position of tile
 * @param id id of the tile
 * @return errorcode
 */
int D2SDLmap::fillMap(int x, int y, int id, SDL_Rect* clip = NULL) {
    //(tile_w * (x - y) ) + x0;
    //(tile_h * (y + x) ) + y0;

    SDL_Rect offset;
    offset.x = x + x0;
    offset.y = y + y0;

    SDL_BlitSurface(tiles->surface, clip, surface->surface, &offset);

    return 0;
}

/**
 * Filling object
 * @param x horizontal position
 * @param y vertical position
 * @param id id of the image
 * @return errorcode
 */
/*
int D2SDLmap::fillObj(int x, int y) {
    int x1 = x + x0; //(tile_w * (x - y) ) + x0;
    int y1 = y + y0 - 137; //(tile_h * (y + x) ) + y0;

    SDL_Rect offset;
    offset.x = x1;
    offset.y = y1;

    SDL_BlitSurface(obj_old->image, NULL, image, &offset);

    return 0;
}
*/

/**
 * Showing map
 * @param x horizontal position
 * @param y vertical position
 * @return errorcode
 */
/*
int D2SDLmap::show(int x, int y, SDL_Surface* screen)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(image, NULL, screen, &offset);

    water_modifier++;
    if (water_modifier>=32)
        water_modifier = 0;

    return 0;
}
*/

int D2SDLmap::isometric_x(int x, int y)
{
    return (x - y + size_x - 1)*(tile_w/2);
    // + x0; //((i - j) + (size_x - 1)) * (tile_w / 2) / pack;
}

int D2SDLmap::isometric_y(int x, int y)
{
    return (x + y)*(tile_h/2);
    // + y0; //((i + j)               ) * (tile_h / 2) / pack; // - tile_h;
}
