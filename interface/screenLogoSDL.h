#ifndef SCREENLOGOSDL_H
#define SCREENLOGOSDL_H

#include "../D2SDL/D2SDLscreen.h"


class screenLogoSDL : public D2SDLscreen
{
    public:
        screenLogoSDL();
        virtual ~screenLogoSDL();
        virtual int on_loop(D2SDLgraph* graph);
    protected:
    private:
};

#endif // SCREENLOGOSDL_H
