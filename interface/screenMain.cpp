#include "screenMain.h"

const char* MAIN_LOGO_FILENAME = "images/background.bmp";

screenMain::screenMain()
{
    m = new map;
    x = 128;
    y = 128;

    bigmap  = new mapBig;
    minimap = new mapMini;

    loadImage(MAIN_LOGO_FILENAME);

    show_cursor = 0;

    m->generate();
    printf("Map generated\n");

    bigmap->initialize();
    minimap->initialize();
}

screenMain::~screenMain()
{
    //dtor
}

int screenMain::on_loop(D2SDLgraph* graph) {
    //moveMouse(graph);

    int showscreen = true;

    cursor->getPosition();

    int mx = cursor->x;
    int my = cursor->y;

    //SDL_GetMouseState(&mx, &my);

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

    while(graph->pollEvent()) {
        /*
        if(graph->event.type == SDL_MOUSEMOTION) {
            repaint = true;
        }
        */
        if(graph->event.type == SDL_KEYDOWN) {
            switch( graph->event.key.keysym.sym ) {
                case SDLK_UP:    moveView(-1, -1); break;
                case SDLK_DOWN:  moveView( 1,  1); break;
                case SDLK_LEFT:  moveView(-1,  1); break;
                case SDLK_RIGHT: moveView( 1, -1); break;
                case SDLK_ESCAPE: showscreen = false; break;
                default: break;
            }
        }
    }

    repaint = true;

    return showscreen;
}

int screenMain::moveView(int dx, int dy) {
    if((dx < 0)&&(x > 0    )) x--;
    if((dx > 0)&&(x < max_x)) x++;
    if((dy < 0)&&(y > 0    )) y--;
    if((dy > 0)&&(y < max_y)) y++;

    repaint = true;

    return 0;
}

int screenMain::on_paint(D2SDLgraph* graph)
{
    int res = 0;

    bigmap->generateMap(x, y, m);
    //graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
    bigmap->show(0, 0, screen->image);

    minimap->generateMap(-1, -1, m);
    minimap->setViewpoint(x,y);
    minimap->show(528, 0, screen->image);

    return res;
}

