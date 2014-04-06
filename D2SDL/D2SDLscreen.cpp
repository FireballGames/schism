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

    printf("Background loaded\n");

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
            if(cursor)
                cursor->getPosition();

            if(graph->event.type == SDL_MOUSEMOTION)
            {
                int x = 0;
                int y = 0;
                if(cursor)
                {
                    x = cursor->x;
                    y = cursor->y;
                    repainting = true;
                }
                do_mouseMotion(x, y);
            }
            else if(graph->event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = 0;
                int y = 0;
                if(cursor)
                {
                    x = cursor->x;
                    y = cursor->y;
                    repainting = true;
                }
                do_mouseButtonDown(x, y);
            }
            else if(graph->event.type == SDL_MOUSEBUTTONUP)
            {
                int x = 0;
                int y = 0;
                if(cursor)
                {
                    x = cursor->x;
                    y = cursor->y;
                    repainting = true;
                }
                do_mouseButtonUp(x, y);
            }
            else if(graph->event.type == SDL_KEYDOWN)
            {
                do_keyDown();
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

        printf("-----\n");
        printf("Frame %d\n", frame);
        printf("-----\n");

        // Painting
        repaint = true;
        if(repainting || (frame < fps))
        {
            graph->depth = 0;
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

            printf("Quit\n");
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
    this->graph->surfaces = 1;
    init(this->graph->width, this->graph->height);
}
