#include "mapBig.h"

const char* MAP_TILES = "images/terrain/terrain.png";

mapBig::mapBig()
{
    pack        = 1;
    objects     = 1;
    water_modifier = 0;

    timer_water = new D2SDLtimer();

    timer_water->start();
}

mapBig::~mapBig()
{
    //dtor
}

SDL_Rect mapBig::getClip(location* l)
{
    unsigned int loctype  = l->loctype;
    unsigned int locstyle = l->style;
    //unsigned int locobj   = loc->object;

    //Modifying water style
    if(loctype == 1)
    {
        locstyle += water_modifier;

        if(locstyle >= max_style)
        {
            locstyle -= max_style;
        }
    }

    if((timer_water->is_started())&&(timer_water->get_ticks() > 40))
    {
        water_modifier++;
        if(water_modifier >= max_style)
        {
            water_modifier -= max_style;
        }
        // timer_water->stop();
        timer_water->start();
    }

    return clip[loctype][locstyle];
}
