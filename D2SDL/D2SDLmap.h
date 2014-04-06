#ifndef D2SDLMAP_H
#define D2SDLMAP_H

#include <SDL/SDL.h>

#include "D2SDLpanel.h"
#include "D2SDLimage.h"
#include "D2SDLimage_old.h"
#include "../map.h"

const int terr_types  =  4;
const int terr_kinds  = 16;

class D2SDLmap : public D2SDLpanel
{
    public:
        unsigned int tile_w;
        unsigned int tile_h;
        unsigned int size_x;
        unsigned int size_y;
        unsigned int max_style;
        int objects;
        int x0;
        int y0;

        int pack;

        SDL_Surface* image;
        SDL_Surface* background;
        D2SDLimage_old* tiles_old;
        D2SDLimage_old* obj_old;

        D2SDLimage* tiles;
        D2SDLimage* obj;

        D2SDLmap();
        virtual ~D2SDLmap();

        int initialize();
        int finalize();
        void loadTiles(unsigned int w, unsigned int h, const char* filename);
        int generateMap(int x, int y, map* m);
        int fillMap(int x, int y, int id, SDL_Rect* clip);
        //int fillObj(int x, int y);
        //int show(int x, int y, SDL_Surface* screen);
    protected:
        char water_modifier;
        char* map_tiles;
        SDL_Rect clip[terr_types][terr_kinds];

        virtual SDL_Surface* screen() = 0;
    private:
        int isometric_x(int x, int y);
        int isometric_y(int x, int y);
};

#endif // D2SDLMAP_H
