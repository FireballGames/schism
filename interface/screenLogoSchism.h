#ifndef SCREENLOGOSCHISM_H
#define SCREENLOGOSCHISM_H

#include "../D2SDL/D2SDLscreen.h"


class screenLogoSchism : public D2SDLscreen
{
    public:
        screenLogoSchism(D2SDLgraph* graph);
        virtual ~screenLogoSchism();
        D2SDLpanel* addButton(int x, int y, const char* filename);
    protected:
    private:
};

#endif // SCREENLOGOSCHISM_H
