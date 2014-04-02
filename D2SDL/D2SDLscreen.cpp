#include "D2SDLscreen.h"
#include "D2SDLimage.h"
#include "D2SDLtimer.h"
#include "D2SDLgraph.h"

const int BASIC_MAX_FPS = 50;

D2SDLscreen::D2SDLscreen()
{
    //graph       = NULL;
    //image       = NULL;
    surface     = new D2SDLimage();//NULL;
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
    setGraph(graph);
}

D2SDLscreen::~D2SDLscreen()
{
    //if(surface) delete surface;
}

int D2SDLscreen::loadBackground(const char* filename)
{
    D2SDLpanel* p   = new D2SDLpanel();
    p->loadGraph(graph);
    int errorcode = p->loadImage(filename);
    add_child(p);

    printf("bg loaded\n");

    return errorcode;
}


int D2SDLscreen::show()
{
    int errorcode = 0;

    SDL_ShowCursor(show_cursor);

    showing = (errorcode==0);
    repaint = true;

    bool repainting = false;

    while(showing)
    {
        while(graph->pollEvent())
        {
            if(graph->event.type == SDL_MOUSEMOTION)
            {
                if(cursor) repainting = true;
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

        // Counting FPS
        if(timer_fps->is_started() && (timer_fps->get_ticks() < 1000))
        {
            frame++;
        }
        else
        {
            frame = 0;
            timer_fps->start();
        }

        // Painting
        repaint = true;
        if(repainting || (frame < fps))
        {
            errorcode = paint(graph->surface);
            if(errorcode<0) return errorcode;

            moveMouse();

            errorcode = graph->flip();
            if(errorcode<0) return errorcode;
        }

        // Quiting
        if(graph->stopped)
        {
            showing = false;
            errorcode = 1;
        }
    }

    return errorcode;
}

/*
int D2SDLscreen::paint()
{
    int res = 0;

    if(image){
        if(!image->image)
            printf("No screen\n");
        int res = SDL_BlitSurface(image->image, NULL, graph->surface, NULL);
        if (res<0) {
            printf("%s\n", SDL_GetError());
        }
    }
    if(res<0) return res;

    on_paint();

    res = graph->flip();
    if(res<0) return res;

    repaint = false;

    return res;
}
*/

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

        SDL_BlitSurface(cursor->image->image,  NULL, graph->surface->surface, &offset);
    }
}

void D2SDLscreen::setGraph(D2SDLgraph* graph)
{
    this->graph = graph;
    init(this->graph->width, this->graph->height);
}
