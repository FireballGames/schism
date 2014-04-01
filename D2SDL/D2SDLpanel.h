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
        D2SDLsurface* surface;  // Panel image

        D2SDLcomponent* parent;   // Parent panel
        D2SDLcomponent* children; // Children panel

        int x; // Panel top
        int y; // Panel left
        int width;  // Panel width
        int height; // Panel height

        bool painted; // If painted

        int init(int w, int h);
        virtual int paint();
        virtual int paint_children();
        virtual void on_paint();
    protected:
    private:
};

#endif // D2SDLPANEL_H
