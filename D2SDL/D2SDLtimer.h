#ifndef D2SDLTIMER_H
#define D2SDLTIMER_H


class D2SDLtimer
{
    public:
        void start();
        void stop();
        void pause();
        void unpause();

        int get_ticks();

        bool is_started();
        bool is_paused();

        D2SDLtimer();
        virtual ~D2SDLtimer();
    protected:
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;
};

#endif // D2SDLTIMER_H
