/* 
 * File:   D2SDLminimap.cpp
 * Author: d2emon
 * 
 * Created on 25 Январь 2014 г., 0:34
 */

#include "D2SDLminimap.h"
#include "D2SDLimage.h"

D2SDLminimap::D2SDLminimap() {
    image = NULL;
    terrain_small = NULL;
}

D2SDLminimap::D2SDLminimap(const D2SDLminimap& orig) {
}

D2SDLminimap::~D2SDLminimap() {
}

int D2SDLminimap::initialize() {
    D2SDLimage* img = new D2SDLimage("images/minimap.png");
    image = img->image;
    if(!image) {
        return -1;
    }
    
    //Clip range for the top left
    for(int i=0; i<4; i++) {
        for(int j=0; j<8; j++) {
            clip[i][j].x = j*4;
            clip[i][j].y = i*2;
            clip[i][j].w = 4;
            clip[i][j].h = 2;    

            clipBig[i][j].x = j*100;
            clipBig[i][j].y = i*50;
            clipBig[i][j].w = 100;
            clipBig[i][j].h = 50;    
        }
    }

    terrain       = new D2SDLimage("images/terrain/terrain.png"); 
    terrain_small = new D2SDLimage("images/terrain/terrain_small.png"); 
}

int D2SDLminimap::finalize() {
    SDL_FreeSurface(terrain->image);
    SDL_FreeSurface(terrain_small->image);
    SDL_FreeSurface(image);
    
    return 0;
}

/**
 * Filling image
 * @param x horizontal position
 * @param y vertical position
 * @param id id of the image
 * @return errorcode
 */
int D2SDLminimap::fill(int x, int y, int id, SDL_Rect* clip = NULL)
{
    int x1 = (2 * (x - y) ) + 128 + 5;
    int y1 = y + x + 40;
    
    SDL_Rect offset;
    offset.x = x1;
    offset.y = y1;

    SDL_BlitSurface(terrain_small->image, clip, image, &offset);
     
    return 0;   
}

int D2SDLminimap::fillBig(int x, int y, int id, SDL_Surface* screen, SDL_Rect* clip = NULL)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(terrain->image, clip, screen, &offset);
     
    return 0;   
}

/**
 * Showing minimap
 * @param x horizontal position
 * @param y vertical position
 * @return errorcode
 */
int D2SDLminimap::show(int x, int y, SDL_Surface* screen)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(image, NULL, screen, &offset);
 
    return 0;   
}


