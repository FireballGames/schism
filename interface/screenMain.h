#ifndef SCREENMAIN_H
#define SCREENMAIN_H

#include "../D2SDL/D2SDLscreen.h"

#include "../map.h"
#include "mapBig.h"
#include "mapMini.h"

class screenMain : public D2SDLscreen
{
    public:
        map* m;
        int x;
        int y;

        screenMain(D2SDLgraph* graph);
        virtual ~screenMain();
        virtual void on_loop();
        virtual void on_paint();
        virtual void on_keyDown(SDL_Event event);
    protected:
        mapBig*  bigmap;
        mapMini* minimap;

        int moveView(int dx, int dy);
    private:
};

#endif // SCREENMAIN_H
