#ifndef D2SDLMAP_H
#define D2SDLMAP_H

#include <SDL/SDL.h>
#include "D2SDLimage_old.h"
#include "../map.h"

const int terr_types  =  4;
const int terr_kinds  = 16;

class D2SDLmap
{
    public:
        int tile_w;
        int tile_h;
        int size_x;
        int size_y;
        int max_style;
        int objects;
        int x0;
        int y0;

        int pack;

        SDL_Surface* image;
        SDL_Surface* background;
        D2SDLimage_old* tiles;
        D2SDLimage_old* obj;

        D2SDLmap();
        virtual ~D2SDLmap();

        int initialize();
        int finalize();
        int generateMap(int x, int y, map* m);
        int fillMap(int x, int y, int id, SDL_Rect* clip);
        int fillObj(int x, int y);
        int show(int x, int y, SDL_Surface* screen);
    protected:
        char water_modifier;
        char* map_tiles;
        SDL_Rect clip[terr_types][terr_kinds];

        virtual SDL_Surface* screen() = 0;
    private:
};

#endif // D2SDLMAP_H
