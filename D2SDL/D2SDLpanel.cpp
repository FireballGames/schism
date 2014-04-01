#include "D2SDLpanel.h"

D2SDLpanel::D2SDLpanel()
{
    /*
    graph  = NULL;
    image  = NULL;
    */

    /*
    parent   = NULL;
    children = NULL;
    next     = NULL;
    */

    x = 0;
    y = 0;
    width  = 100;
    height = 100;
}

D2SDLpanel::D2SDLpanel(D2SDLgraph* graph)
{
    D2SDLpanel();
    //this->graph = graph;

    //x = (this->graph->width  - width )/2;
    //y = (this->graph->height - height)/2;
}

D2SDLpanel::~D2SDLpanel()
{
    //image->free();
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

    //image = new D2SDLsurface();

    //return image->init(width, height);

    return 0;
}

int D2SDLpanel::paint()
{
    int errorcode = 0;

    paint_children();

    /*
    if(image){
        errorcode = image->paint(graph);

        //moveMouse();
    }
    */

    if(errorcode) return errorcode;

    on_paint();

    //return graph->flip();
    return 0;
}

int D2SDLpanel::paint_children()
{
    int errorcode = 0;

    //D2SDLpanel* child = children;

    /*
    if(child)
    {
        errorcode = child->paint();
        if(errorode) return errorcode;
        while(child->next && (!errorcode))
        {
            child = child->next;
            child->paint();
        }
    }
    */

    return errorcode;
}

void D2SDLpanel::on_paint() { }
