#include "D2SDLpanel.h"

D2SDLpanel::D2SDLpanel()
{
    graph   = NULL;
    surface = new D2SDLsurface;

    parent   = NULL;
    children = NULL;
    next     = NULL;

    x = 0;
    y = 0;
    width  = 100;
    height = 100;
}

D2SDLpanel::D2SDLpanel(D2SDLgraph* graph)
{
    D2SDLpanel();
    this->graph = graph;

    x = (this->graph->width  - width )/2;
    y = (this->graph->height - height)/2;
}

D2SDLpanel::~D2SDLpanel()
{
    if(surface)
        delete surface;
}

/**
 * Panel initialization
 * @param int w Panel width
 * @param int h Panel height
 * @return int errorcode
 */
int D2SDLpanel::init(int w = 0, int h = 0)
{
    if(w) width  = w;
    if(h) height = h;

    surface = new D2SDLsurface();

    return surface->init(width, height);
}

/**
 * Painting panel
 * @return int errorcode
 */
int D2SDLpanel::paint()
{
    int errorcode = 0;

    paint_children();

    if(surface){
        errorcode = surface->paint(graph);
        on_paint();

        //moveMouse();
    }

    return errorcode;
}

/**
 * Painting children panels
 * @return int errorcode
 */
int D2SDLpanel::paint_children()
{
    int errorcode = 0;

    D2SDLcomponent* child = children;

    if(child)
    {
        errorcode = child->paint();
        if(errorcode) return errorcode;
        while(child->next && (!errorcode))
        {
            child = child->next;
            errorcode = child->paint();
        }
    }

    return errorcode;
}

void D2SDLpanel::on_paint() { }
