#ifndef SCREENLOGOFIREBAL_H
#define SCREENLOGOFIREBAL_H

#include "../D2SDL/D2SDLscreen.h"

class screenLogoFireball : public D2SDLscreen
{
    public:
        screenLogoFireball();
        virtual ~screenLogoFireball();
        virtual int on_loop(D2SDLgraph* graph);
    protected:
    private:
};

#endif // SCREENLOGOFIREBAL_H
