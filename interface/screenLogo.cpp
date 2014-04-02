#include "screenLogo.h"

screenLogo::screenLogo()
{
    delay       = 2000;
    show_cursor = 0;

    timer = new D2SDLtimer();
    timer->start();
}


screenLogo::screenLogo(D2SDLgraph* graph)
{
    screenLogo();
    setGraph(graph);
}

screenLogo::~screenLogo()
{
    //dtor
}

/*
int screenLogo::loadImage(const char* filename)
{
    printf("Loading %s\n", filename);

    D2SDLpanel* p   = new D2SDLpanel();
    D2SDLimage* img = new D2SDLimage();
    img->load(filename);

    p->loadGraph(graph);
    p->surface    = img;
    p->surface->x = (graph->width  - p->surface->width )/2;
    p->surface->y = (graph->height - p->surface->height)/2;

    add_child(p);

    loaded = (img != false);

    return loaded ? 0 : -1;
}
*/

void screenLogo::on_loop() {
    if(timer->get_ticks() >= delay) {
        showing = false;
    }
}

void screenLogo::on_mouseButtonDown(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
        showing = false;
}

void screenLogo::on_keyDown(SDL_Event event) {
    showing = false;
}
