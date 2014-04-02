#include "screenMain.h"

const char* MAIN_LOGO_FILENAME = "images/background.bmp";

void main_keyDown(D2SDLcomponent* sender, SDL_Event event) {
    screenMain* screen = dynamic_cast<screenMain*>(sender);
    if(screen)
    {
        switch( event.key.keysym.sym ) {
            case SDLK_UP:    screen->moveView(-1, -1); break;
            case SDLK_DOWN:  screen->moveView( 1,  1); break;
            case SDLK_LEFT:  screen->moveView(-1,  1); break;
            case SDLK_RIGHT: screen->moveView( 1, -1); break;
            case SDLK_ESCAPE: screen->showing = false; break;
            default: break;
        }
    }
}

screenMain::screenMain(D2SDLgraph* graph)
{
    setGraph(graph);

    show_cursor = 0;
    on_keyDown  = main_keyDown;

    x = 128;
    y = 128;

    bigmap  = new mapBig;
    minimap = new mapMini;

    bigmap->initialize();
    minimap->initialize();
}

screenMain::~screenMain()
{
    //dtor
}

void screenMain::on_loop() {
    cursor->getPosition();

    int mx = cursor->x;
    int my = cursor->y;

    if(mx < 10) {
        moveView(-1,  1);
    }
    if(mx > 790) {
        moveView( 1, -1);
    }
    if(my < 10) {
        moveView(-1, -1);
    }
    if(my > 590) {
        moveView( 1,  1);
    }
}

int screenMain::moveView(int dx, int dy) {
    if((dx < 0)&&(x > 0    )) x--;
    if((dx > 0)&&(x < max_x)) x++;
    if((dy < 0)&&(y > 0    )) y--;
    if((dy > 0)&&(y < max_y)) y++;

    repaint = true;

    return 0;
}

void screenMain::on_paint()
{
    bigmap->generateMap(x, y, m);
    bigmap->show(0, 0, surface->surface);

    minimap->generateMap(-1, -1, m);
    minimap->setViewpoint(x,y);
    minimap->show(surface->width-272, 0, surface->surface); //528

    //graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
}
