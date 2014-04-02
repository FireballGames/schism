#include "screenLogo.h"

void logo_mouseButtonDown(D2SDLcomponent* sender, SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        D2SDLscreen* logo = dynamic_cast<D2SDLscreen*>(sender);
        if(logo)
            logo->showing = false;
    }
}

void logo_keyDown(D2SDLcomponent* sender, SDL_Event event) {
    D2SDLscreen* logo = dynamic_cast<D2SDLscreen*>(sender);
    if(logo)
        logo->showing = false;
}

screenLogo::screenLogo()
{
    delay       = 2000;
    show_cursor = 0;

    on_mouseButtonDown = logo_mouseButtonDown;
    on_keyDown         = logo_keyDown;

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
