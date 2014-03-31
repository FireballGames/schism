#ifndef SCREENLOGOSDL_H
#define SCREENLOGOSDL_H

#include "screenLogo.h"


class screenLogoSDL : public screenLogo
{
    public:
        screenLogoSDL(D2SDLgraph* graph);
        virtual ~screenLogoSDL();
    protected:
    private:
};

#endif // SCREENLOGOSDL_H
