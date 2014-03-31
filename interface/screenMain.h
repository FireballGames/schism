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

        screenMain();
        virtual ~screenMain();
    protected:
        mapBig*  bigmap;
        mapMini* minimap;

        int moveView(int dx, int dy);
    private:
        virtual int on_loop(D2SDLgraph* graph);
        virtual int on_paint(D2SDLgraph* graph);
};

#endif // SCREENMAIN_H
