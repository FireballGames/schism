#ifndef SCREENLOGO_H
#define SCREENLOGO_H

#include "../D2SDL/D2SDLscreen.h"


class screenLogo : public D2SDLscreen
{
    public:
        int         delay;
        D2SDLtimer* timer;

        screenLogo();
        screenLogo(D2SDLgraph* graph);
        virtual ~screenLogo();

        //int loadImage(const char* filename);
        virtual void on_loop();
        virtual void on_mouseButtonDown(SDL_Event event);
        virtual void on_keyDown(SDL_Event event);
    protected:
    private:
};

#endif // SCREENLOGO_H
