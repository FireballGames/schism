/*
 * File:   D2SDLimage.cpp
 * Author: d2emon
 *
 * Created on 25 Январь 2014 г., 0:03
 */

#include "D2SDLimage_old.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

D2SDLimage_old::D2SDLimage_old(const char* filename, int color_key) {
    image = NULL;
    load(filename, color_key);
}

D2SDLimage_old::~D2SDLimage_old() {
}

/**
 * Loading image into SDL
 * @param filename image file
 * @return optimized image
 */
SDL_Surface* D2SDLimage_old::load(const char* filename, int color_key) {
    SDL_Surface* loaded_image    = NULL;

    loaded_image = IMG_Load(filename);
    if(loaded_image != NULL) {
        image = SDL_DisplayFormat(loaded_image);
        SDL_FreeSurface(loaded_image);

        if(color_key){
            Uint32 colorkey = SDL_MapRGB(image->format, 0xFF, 0, 0xFF);
            SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey );
        }
    }

    return image;
}

/**
 * Freeing image from SDL
 * @return errorcode
 */
int D2SDLimage_old::free() {
    SDL_FreeSurface(image);
    return 0;
}
