#include "D2SDLpanel.h"
#include "D2SDLimage.h"

D2SDLpanel::D2SDLpanel()
{
    graph   = NULL;
    surface = new D2SDLsurface;

    parent   = NULL;
    children = NULL;
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
    printf("Delete children\n");
    if(children)
        delete children;
    printf("Delete surface\n");
    if(surface)
    {
        delete surface;

        if(graph)
        {
            graph->surfaces --;
            printf("Surfaces %d\n", graph->surfaces);
        }
    }
    printf("Deleted\n");
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
    else
    {
        printf("Orphan\n");
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
    if(!children)
    {
        children = child;
        return 0;
    }

    D2SDLcomponent* c = children;
    while(c->next)
    {
        c = c->next;
        printf("Next sibling\n");
    }

    c->next = child;

    return 0;

    /*
    child->next = children;
    children    = child;
    */
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
        printf("Paint basic\n");
        on_paint();
        printf("Paint children\n");
        paint_children();
        printf("Paint all\n");
    }
    printf("Paint leave\n");

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
            errorcode = child->paint(surface);
            child     = child->next;
        }
    }

    return errorcode;
}

void D2SDLpanel::on_paint() { }
