#include "screenMain.h"

const char* MAIN_LOGO_FILENAME = "images/background.bmp";

screenMain::screenMain(D2SDLgraph* graph)
{
    setGraph(graph);

    m = new map;
    x = 128;
    y = 128;

    bigmap  = new mapBig;
    minimap = new mapMini;

    loadImage(MAIN_LOGO_FILENAME);

    show_cursor = 0;

    m->generate();
    printf("Map generated\n");

    // m->save("test.map");
    // m->load("test.map");
    // printf("Map loaded\n");

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

void screenMain::on_keyDown(SDL_Event event) {
    switch( graph->event.key.keysym.sym ) {
        case SDLK_UP:    moveView(-1, -1); break;
        case SDLK_DOWN:  moveView( 1,  1); break;
        case SDLK_LEFT:  moveView(-1,  1); break;
        case SDLK_RIGHT: moveView( 1, -1); break;
        case SDLK_ESCAPE: showing = false; break;
        default: break;
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
    //graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
    bigmap->show(0, 0, surface->surface);

    minimap->generateMap(-1, -1, m);
    minimap->setViewpoint(x,y);
    minimap->show(528, 0, surface->surface);
}

