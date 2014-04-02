#ifndef D2SDLSCREEN_H
#define D2SDLSCREEN_H

#include "D2SDLpanel.h"
#include "D2SDLgraph.h"
#include "D2SDLimage.h"
#include "D2SDLcursor.h"
#include "D2SDLtimer.h"

class D2SDLscreen : public D2SDLpanel
{
    public:
        D2SDLscreen();
        D2SDLscreen(D2SDLgraph* graph);
        virtual ~D2SDLscreen();

        //D2SDLgraph*  graph;
        //D2SDLimage*  image;

        D2SDLcursor* cursor;

        int   fps;
        int   show_cursor;
        int   repaint;
        int   showing;
        char* logo_filename;

        int loadBackground(const char* filename);
        int show();
        //virtual int paint();
        void moveMouse();
        void setGraph(D2SDLgraph* graph);

        virtual void on_loop();
        virtual void on_paint();
        /*
        virtual void on_mouseButtonDown(SDL_Event event);
        virtual void on_mouseButtonUp(SDL_Event event);
        virtual void on_keyDown(SDL_Event event);
        */
    protected:
        int         frame;
        D2SDLtimer* timer_fps;
        int loaded;
    private:
};

#endif // D2SDLSCREEN_H
