#ifndef D2SDLSCREEN_H
#define D2SDLSCREEN_H

#include "../SDLgraph.h"
#include "D2SDLimage.h"

class D2SDLscreen
{
    public:
        D2SDLscreen();
        virtual ~D2SDLscreen();

        D2SDLimage* screen;

        int   delay;
        char* logo_filename;

        int loadImage(const char* filename);
        int show(SDLgraph* graph);
    protected:
        int   loaded;
    private:
};

#endif // D2SDLSCREEN_H
