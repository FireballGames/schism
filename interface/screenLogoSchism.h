#ifndef SCREENLOGOSCHISM_H
#define SCREENLOGOSCHISM_H

#include "../D2SDL/D2SDLscreen.h"


class screenLogoSchism : public D2SDLscreen
{
    public:
        screenLogoSchism();
        virtual ~screenLogoSchism();
        virtual int on_loop(D2SDLgraph* graph);
    protected:
    private:
};

#endif // SCREENLOGOSCHISM_H
