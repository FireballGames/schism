#include "D2SDLscreen.h"
#include "D2SDLimage.h"
#include "D2SDLtimer.h"
#include "D2SDLgraph.h"

D2SDLscreen::D2SDLscreen()
{
    screen      = NULL;
    cursor      = NULL;
    timer       = NULL;
    loaded      = 0;
    show_cursor = 1;

    timer = new D2SDLtimer();
}

D2SDLscreen::~D2SDLscreen()
{
    screen->free();
}

int D2SDLscreen::loadImage(const char* filename)
{
    printf("Loading %s\n", filename);

    screen = new D2SDLimage(filename);
    loaded = (screen != false);

    return loaded ? 0 : -1;
}

int D2SDLscreen::show(D2SDLgraph* graph)
{
    int res = 0;

    if(!loaded && logo_filename){
        res = loadImage(logo_filename);
    }

    if(res<0)
        return res;

    res = SDL_ShowCursor(show_cursor);
    if(res<0)
        return res;

    if(screen){
        printf("Blitting\n");
        if(!screen->image)
            printf("No screen\n");
        int res = SDL_BlitSurface(screen->image, NULL, graph->screen, NULL);
        if (res<0) {
            printf("%s\n", SDL_GetError());
        }
    }
    if(res<0)
        return res;

    res = graph->flip();
    if(res<0)
        return res;

    timer->start();

    int show = (res==0);
    while(show) {
        show = on_loop(graph);
    }

    return res;
}

int D2SDLscreen::on_loop(D2SDLgraph* graph) {
    int show = true;

    if(timer->get_ticks() >= delay) {
        show = false;
    }

    while(graph->pollEvent()) {
        printf("Basic %d\n", graph->event.type);
    }

    return show;
}
