#include "screenMain.h"

//const char* MAIN_LOGO_FILENAME = "images/background.bmp";
const int   TILE_WIDTH  = 118;
const int   TILE_HEIGHT =  60;
const char* TILE_IMAGES = "images/terrain/terrain.png";
const int   MINI_TILE_WIDTH  = 2;
const int   MINI_TILE_HEIGHT = 2;
const char* MINI_TILE_IMAGES = "images/terrain/terrain_small.png";

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

    unsigned int size_x = (4*graph->width ) / TILE_WIDTH;

    bigmap  = new mapBig;
    bigmap->loadGraph(graph);
    bigmap->init(graph->width, graph->height);
    bigmap->surface->x = 0; //-graph->width/2;
    bigmap->surface->y = 0; //-graph->width/2;
    add_child(bigmap);
    printf("Added as child\n");
    bigmap->size_x  = size_x;
    bigmap->size_y  = size_x;
    bigmap->x0 = -size_x*TILE_WIDTH/4; //-graph->width/2;
    bigmap->y0 = -size_x*TILE_HEIGHT/4; // + size_x*TILE_HEIGHT/4;

    bigmap->loadTiles( TILE_WIDTH, TILE_HEIGHT, TILE_IMAGES);
    printf("Bigmap  %d %d\n",  bigmap->size_x,  bigmap->size_y);

    minimap  = new mapMini;
    minimap->loadGraph(graph);
    minimap->init(256*MINI_TILE_WIDTH, 256*MINI_TILE_HEIGHT);
    //p->loadImage(filename);
    minimap->surface->x = surface->width-(256*MINI_TILE_WIDTH) - 8;//272;
    minimap->surface->y = 8;
    add_child(minimap);
    minimap->size_x = 512;
    minimap->size_y = 512;
    minimap->x0 = 0;
    minimap->y0 = 0;
    minimap->loadTiles( MINI_TILE_WIDTH, MINI_TILE_HEIGHT, MINI_TILE_IMAGES);
    printf("Minimap %d %d\n", minimap->size_x, minimap->size_y);

    //bigmap->initialize();
    //minimap->initialize();
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
    //bigmap->show(0, 0, surface->surface);

    minimap->generateMap(0, 0, m);
    minimap->setViewpoint(x,y);
    //minimap->show(surface->width-272, 0, surface->surface); //528

    //graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
    int vx = x-y+256;
    int vy = x+y;
    graph->fillImage(minimap->surface->surface, vx, vy, "images/terrain/userloc.png");
}
