#ifndef D2SDLCOMPONENT_H
#define D2SDLCOMPONENT_H


class D2SDLcomponent
{
    public:
        D2SDLcomponent();
        virtual ~D2SDLcomponent();

        D2SDLcomponent* next; // Next panel
        int paint();
    protected:
    private:
};

#endif // D2SDLCOMPONENT_H
