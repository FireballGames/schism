#include "D2SDLscreen.h"
#include "D2SDLimage.h"
#include "D2SDLtimer.h"
#include "D2SDLgraph.h"

const int BASIC_MAX_FPS = 500;

D2SDLscreen::D2SDLscreen()
{
    screen      = NULL;
    cursor      = NULL;
    timer       = NULL;
    delay       = 0;
    loaded      = 0;
    show_cursor = 1;
    repaint     = true;

    timer = new D2SDLtimer();

    timer_fps = NULL;
    frame     = 0;
    fps       = BASIC_MAX_FPS;
    timer_fps = new D2SDLtimer();
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

    timer->start();

    res = paint(graph);
    if(res<0)
        return res;

    int showscreen = (res==0);
    while(showscreen) {
        showscreen = on_loop(graph);

        if(timer_fps->is_started() && (timer_fps->get_ticks() < 1000))
        {
            frame++;
        }
        else
        {
            frame = 0;
            timer_fps->start();
        }

        if(repaint && (frame < fps))
        {
            paint(graph);
            repaint = false;
        }
    }

    return res;
}

int D2SDLscreen::paint(D2SDLgraph* graph)
{
    int res = 0;

    if(screen){
        if(!screen->image)
            printf("No screen\n");
        int res = SDL_BlitSurface(screen->image, NULL, graph->screen, NULL);
        if (res<0) {
            printf("%s\n", SDL_GetError());
        }
        moveMouse(graph);
    }
    if(res<0)
        return res;

    res = on_paint(graph);
    if(res<0)
        return res;

    res = graph->flip();
    if(res<0)
        return res;

    return res;
}

int D2SDLscreen::on_loop(D2SDLgraph* graph) {
    int showscreen = true;

    if(timer->get_ticks() >= delay) {
        showscreen = false;
    }

    while(graph->pollEvent()) {
        printf("Basic %d\n", graph->event.type);
    }

    return showscreen;
}

int D2SDLscreen::on_paint(D2SDLgraph* graph) {
    return 0;
}

void D2SDLscreen::moveMouse(D2SDLgraph* graph=NULL) {
    if(cursor)
    {
        cursor->getPosition();

        SDL_Rect offset;
        offset.x = cursor->x;
        offset.y = cursor->y;

        SDL_BlitSurface(cursor->image->image,  NULL, graph->screen, &offset);
    }
}
