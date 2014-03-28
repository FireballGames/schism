#include <SDL/SDL.h>

#include "D2SDLtimer.h"

D2SDLtimer::D2SDLtimer(){
    startTicks  = 0;
    pausedTicks = 0;
    paused      = false;
    started     = false;
}

D2SDLtimer::~D2SDLtimer(){
    //dtor
}

void D2SDLtimer::start() {
    started = true;
    paused  = false;

    startTicks = SDL_GetTicks();
}

void D2SDLtimer::stop() {
    started = false;
    paused  = false;
}

int D2SDLtimer::get_ticks() {
    if( started ) {
        if( paused ) {
            return pausedTicks;
        } else {
            return SDL_GetTicks() - startTicks;
        }
    }

    return 0;
}

void D2SDLtimer::pause() {
    if( started && !paused) {
        paused      = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void D2SDLtimer::unpause() {
    if( paused ) {
        paused      = false;

        startTicks  = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

bool D2SDLtimer::is_started() {
    return started;
}

bool D2SDLtimer::is_paused() {
    return paused;
}
