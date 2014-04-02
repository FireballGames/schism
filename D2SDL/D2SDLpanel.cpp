#include "D2SDLpanel.h"
#include "D2SDLimage.h"

D2SDLpanel::D2SDLpanel()
{
    graph   = NULL;
    surface = new D2SDLsurface;

    parent   = NULL;
    children = NULL;

    on_mouseMotion     = NULL;
    on_mouseButtonDown = NULL;
    on_mouseButtonUp   = NULL;
    on_keyDown         = NULL;
}

/*
D2SDLpanel::D2SDLpanel(D2SDLgraph* graph)
{
    D2SDLpanel();
    printf("Panel created\n");
    this->graph = graph;

    x = (this->graph->width  - width )/2;
    y = (this->graph->height - height)/2;
}
*/

D2SDLpanel::~D2SDLpanel()
{
    if(children)
        delete children;
    if(surface)
    {
        delete surface;

        if(graph)
        {
            graph->surfaces --;
            printf("Surfaces %d\n", graph->surfaces);
        }
    }
}

/**
 * Panel initialization
 * @param int w Panel width
 * @param int h Panel height
 * @return int errorcode
 */
int D2SDLpanel::init(int w = 0, int h = 0)
{
    surface = new D2SDLsurface();

    if(graph)
    {
        graph->surfaces ++;
        printf("Surfaces %d\n", graph->surfaces);
    }

    return surface->init(w, h);
}

int D2SDLpanel::loadGraph(D2SDLgraph* graph)
{
    this->graph = graph;

    return 0;
}

int D2SDLpanel::loadImage(const char* filename)
{
    printf("Loading %s\n", filename);

    D2SDLimage* img = new D2SDLimage();
    img->load(filename);

    if(img && graph)
    {
        surface    = img;
        surface->x = (graph->width  - surface->width )/2;
        surface->y = (graph->height - surface->height)/2;
    }

    return (img) ? 0 : -1;
}

/**
 * Adding child component
 * @param D2SDLcomponent child component
 * @return int errorcode
 */
int D2SDLpanel::add_child(D2SDLcomponent* child)
{
    D2SDLpanel* p = dynamic_cast<D2SDLpanel*>(child);
    p->parent = this;

    if(!children)
    {
        children = child;
        return 0;
    }

    D2SDLcomponent* c = children;
    while(c->next)
    {
        c = c->next;
    }

    c->next = child;

    return 0;
}

/**
 * Painting panel
 * @return int errorcode
 */
int D2SDLpanel::paint(D2SDLsurface* new_surface)
{
    int errorcode = 0;


    if(surface){
        if(graph) printf("Depth %d\n", graph->depth);
        errorcode = surface->paint(new_surface);
        on_paint();
        paint_children();
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
        while(child && (!errorcode))
        {
            if(graph) graph->depth++;

            D2SDLpanel* p = dynamic_cast<D2SDLpanel*>(child);
            if(p)
                errorcode = p->paint(surface);

            child = child->next;
        }
    }

    return errorcode;
}

void D2SDLpanel::on_paint() { }

bool D2SDLpanel::hover(const int x, const int y)
{
    if(!surface)
        return false;

    int x1 = surface->x;
    int y1 = surface->y;
    int x2 = x1 + surface->width;
    int y2 = y1 + surface->height;

    return ((x >= x1)&&(x <= x2))&&((y >= y1)&&(y <= y2));

}

void D2SDLpanel::do_mouseMotion(const int x, const int y)
{
    if(on_mouseMotion) on_mouseMotion(this, graph->event);

    D2SDLcomponent* c = children;
    while(c)
    {
        D2SDLpanel* p = dynamic_cast<D2SDLpanel*>(c);
        if(p)
        {
            if(p->hover(x, y))
            {
                p->do_mouseMotion(x, y);
            }
        }
        c = c->next;
    }
}

void D2SDLpanel::do_mouseButtonUp(const int x, const int y)
{
    if(on_mouseButtonUp) on_mouseButtonUp(this, graph->event);

    D2SDLcomponent* c = children;
    while(c)
    {
        D2SDLpanel* p = dynamic_cast<D2SDLpanel*>(c);
        if(p)
        {
            if(p->hover(x, y))
            {
                p->do_mouseButtonUp(x, y);
            }
        }
        c = c->next;
    }
}

void D2SDLpanel::do_mouseButtonDown(const int x, const int y)
{
    if(on_mouseButtonDown) on_mouseButtonDown(this, graph->event);

    D2SDLcomponent* c = children;
    while(c)
    {
        D2SDLpanel* p = dynamic_cast<D2SDLpanel*>(c);
        if(p)
        {
            if(p->hover(x, y))
            {
                p->do_mouseButtonDown(x, y);
            }
        }
        c = c->next;
    }
}

void D2SDLpanel::do_keyDown()
{
    if(on_keyDown) on_keyDown(this, graph->event);

    D2SDLcomponent* c = children;
    while(c)
    {
        D2SDLpanel* p = dynamic_cast<D2SDLpanel*>(c);
        if(p)
        {
            p->do_keyDown();
        }
        c = c->next;
    }
}
