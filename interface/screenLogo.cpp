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
