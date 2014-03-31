#ifndef SCREENLOGOSCHISM_H
#define SCREENLOGOSCHISM_H

#include "../D2SDL/D2SDLscreen.h"


class screenLogoSchism : public D2SDLscreen
{
    public:
        screenLogoSchism(D2SDLgraph* graph);
        virtual ~screenLogoSchism();
        //virtual int on_loop();
        virtual void on_mouseButtonDown(SDL_Event event);
        virtual void on_keyDown(SDL_Event event);
    protected:
    private:
};

#endif // SCREENLOGOSCHISM_H
