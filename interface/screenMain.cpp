#include "screenMain.h"

//const char* MAIN_LOGO_FILENAME = "images/background.bmp";
const int   TILE_WIDTH  = 118;
const int   TILE_HEIGHT =  60;
const char* TILE_IMAGES = "images/terrain/terrain.png";
const int   MINI_TILE_WIDTH  = 2;
const int   MINI_TILE_HEIGHT = 1;
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
    bigmap->init(graph->width, graph->height, true);
    bigmap->surface->x = 0; //-graph->width/2;
    bigmap->surface->y = 0; //-graph->width/2;
    add_child(bigmap);
    bigmap->size_x  = size_x;
    bigmap->size_y  = size_x;
    bigmap->x0 = -(size_x+18)*TILE_WIDTH/4;//-(size_x/4+5)*TILE_WIDTH;
    //-graph->width/2;
    bigmap->y0 = -(size_x+18)*TILE_HEIGHT/4;//-(size_x/4)*TILE_HEIGHT;
    // + size_x*TILE_HEIGHT/4;

    bigmap->loadTiles( TILE_WIDTH, TILE_HEIGHT, TILE_IMAGES);
    printf("Bigmap  %d %d\n",  bigmap->size_x,  bigmap->size_y);


    minimap  = new mapMini;
    minimap->loadGraph(graph);

    unsigned int mini_width  = max_x * MINI_TILE_WIDTH  / minimap->pack;
    unsigned int mini_height = max_y * MINI_TILE_HEIGHT / minimap->pack;
    unsigned int border_width  = 10;
    unsigned int border_height = 10;
    minimap->init(mini_width + (border_width*2), mini_height + border_height*2, true);
    //p->loadImage(filename);
    printf("Surface  %d %d\n", surface->width - minimap->surface->width - 8, surface->height);
    printf("Minimap  %d %d\n", mini_width,     mini_height    );
    minimap->surface->x = surface->width - minimap->surface->width - 8;//272;
    minimap->surface->y = 8;
    printf("Surface  %d %d\n", minimap->surface->x, minimap->surface->y);
    add_child(minimap);
    minimap->size_x = max_x;
    minimap->size_y = max_y;
    minimap->x0 = border_width;
    minimap->y0 = border_height;
    minimap->loadTiles( MINI_TILE_WIDTH, MINI_TILE_HEIGHT, MINI_TILE_IMAGES);

    printf("Minimap %d %d\n", minimap->size_x, minimap->size_y);
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
    //graph->fillImage(bigmap->image, (bigmap->size_x/2)*bigmap->tile_w+bigmap->x0, (bigmap->size_y/2)*bigmap->tile_h+bigmap->y0, IMG_UNIT      , 0);
    printf("Map generated\n");

    minimap->generateMap(128, 128, m);
    printf("Minimap generated\n");

    int vx = (x-y)/(minimap->pack * minimap->tile_h) + (minimap->surface->width)/2;
    int vy = (x+y)/(minimap->pack * minimap->tile_w) + minimap->y0;
    //minimap->setViewpoint(x,y);
    graph->fillImage(minimap->surface->surface, vx, vy, "images/terrain/userloc.png");
}
