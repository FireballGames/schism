#include "D2SDLscreen.h"
#include "D2SDLimage.h"
#include "D2SDLtimer.h"
#include "D2SDLgraph.h"

const int BASIC_MAX_FPS = 500;

D2SDLscreen::D2SDLscreen()
{
    graph       = NULL;
    screen      = NULL;
    cursor      = NULL;
    loaded      = 0;
    show_cursor = 1;
    repaint     = true;

    timer_fps = NULL;
    frame     = 0;
    fps       = BASIC_MAX_FPS;
    timer_fps = new D2SDLtimer();
}

D2SDLscreen::D2SDLscreen(D2SDLgraph* graph)
{
    D2SDLscreen();
    this->graph = graph;
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

int D2SDLscreen::show()
{
    int res = 0;

    if(!loaded && logo_filename){
        res = loadImage(logo_filename);
        if(res<0) return res;
    }

    SDL_ShowCursor(show_cursor);

    showing = (res==0);
    repaint = true;

    while(showing)
    {
        while(graph->pollEvent())
        {
            if(graph->event.type == SDL_MOUSEMOTION)
            {
                if(cursor) repaint = true;
                on_mouseMotion(graph->event);
            }
            else if(graph->event.type == SDL_MOUSEBUTTONDOWN)
            {
                on_mouseButtonDown(graph->event);
            }
            else if(graph->event.type == SDL_MOUSEBUTTONUP)
            {
                on_mouseButtonUp(graph->event);
            }
            else if(graph->event.type == SDL_KEYDOWN)
            {
                on_keyDown(graph->event);
            }
            //else
                // printf("Basic %d\n", graph->event.type);
        }

        on_loop();

        /*
         * Counting FPS
         */
        if(timer_fps->is_started() && (timer_fps->get_ticks() < 1000))
        {
            frame++;
        }
        else
        {
            frame = 0;
            timer_fps->start();
        }

        /*
         * Painting
         */
        repaint =true;
        if(repaint && (frame < fps))
        {
            res = paint();
            if(res<0) return res;
        }

        /*
         * Quiting
         */
        if(graph->stopped)
        {
            showing = false;
            res = 1;
        }
    }

    return res;
}

int D2SDLscreen::paint()
{
    int res = 0;

    if(screen){
        if(!screen->image)
            printf("No screen\n");
        int res = SDL_BlitSurface(screen->image, NULL, graph->surface, NULL);
        if (res<0) {
            printf("%s\n", SDL_GetError());
        }
        moveMouse();
    }
    if(res<0) return res;

    on_paint();

    res = graph->flip();
    if(res<0) return res;

    repaint = false;

    return res;
}

void D2SDLscreen::on_loop() {
}

void D2SDLscreen::on_paint() {
}

void D2SDLscreen::on_mouseMotion(SDL_Event event) {
}

void D2SDLscreen::on_mouseButtonDown(SDL_Event event) {
}

void D2SDLscreen::on_mouseButtonUp(SDL_Event event) {
}

void D2SDLscreen::on_keyDown(SDL_Event event) {
}

void D2SDLscreen::moveMouse() {
    if(cursor)
    {
        cursor->getPosition();

        SDL_Rect offset;
        offset.x = cursor->x;
        offset.y = cursor->y;

        SDL_BlitSurface(cursor->image->image,  NULL, graph->surface, &offset);
    }
}
