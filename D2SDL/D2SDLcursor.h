#ifndef D2SDLCURSOR_H
#define D2SDLCURSOR_H

#include "D2SDLimage_old.h"

class D2SDLcursor
{
    public:
        int x;
        int y;
        D2SDLimage_old* image;
        D2SDLcursor();
        virtual ~D2SDLcursor();
        int load(const char* filename);
        void getPosition();
    protected:
    private:
};

#endif // D2SDLCURSOR_H
