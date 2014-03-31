#ifndef D2SDLSCREEN_H
#define D2SDLSCREEN_H

#include "D2SDLgraph.h"
#include "D2SDLimage.h"
#include "D2SDLcursor.h"
#include "D2SDLtimer.h"

class D2SDLscreen
{
    public:
        D2SDLscreen();
        virtual ~D2SDLscreen();

        D2SDLimage* screen;
        D2SDLcursor* cursor;
        D2SDLtimer* timer;

        int   delay;
        int   fps;
        int   repaint;
        int   show_cursor;
        char* logo_filename;

        int loadImage(const char* filename);
        int show(D2SDLgraph* graph);
        virtual int paint(D2SDLgraph* graph);
        void moveMouse(D2SDLgraph* graph);

        virtual int on_loop(D2SDLgraph* graph);
        virtual int on_paint(D2SDLgraph* graph);
    protected:
        int         frame;
        D2SDLtimer* timer_fps;
        int loaded;
    private:
};

#endif // D2SDLSCREEN_H
