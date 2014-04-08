#ifndef D2SDLPANEL_H
#define D2SDLPANEL_H

#include "D2SDLcomponent.h"
#include "D2SDLgraph.h"
#include "D2SDLsurface.h"

class D2SDLpanel : public D2SDLcomponent
{
    public:
        D2SDLpanel();
        D2SDLpanel(D2SDLgraph* graph);
        virtual ~D2SDLpanel();

        D2SDLgraph*   graph;  // Main graphical object
        D2SDLsurface*   surface; // Panel image

        D2SDLcomponent* children; // Children panel

        int init(unsigned int w, unsigned int h, bool paint);
        int loadGraph(D2SDLgraph* graph);
        int loadImage(const char* filename);
        int add_child(D2SDLcomponent* child);
        virtual int paint(D2SDLsurface* new_surface);
        virtual int paint_children();
        virtual void on_paint();
        //virtual void on_mouseMotion(SDL_Event event);

        bool hover(const int x, const int y);
        void do_mouseMotion(const int x, const int y);
        void do_mouseButtonUp(const int x, const int y);
        void do_mouseButtonDown(const int x, const int y);
        void do_keyDown();


        void(*on_mouseMotion)(D2SDLcomponent* sender, const SDL_Event);
        void(*on_mouseButtonDown)(D2SDLcomponent* sender, const SDL_Event);
        void(*on_mouseButtonUp)(D2SDLcomponent* sender, const SDL_Event);
        void(*on_keyDown)(D2SDLcomponent* sender, const SDL_Event);
        /*
        virtual void on_paint();
        virtual void on_mouseButtonDown(SDL_Event event);
        virtual void on_mouseButtonUp(SDL_Event event);
        virtual void on_keyDown(SDL_Event event);
        */

    protected:
    private:
};

#endif // D2SDLPANEL_H
