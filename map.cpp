/*
 * File:   map.cpp
 * Author: d2emon
 *
 * Created on 23 Январь 2014 г., 0:13
 */

#include "map.h"
#include "location.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>

const int lakes     = 15;
const int lake_size = 50;
const int forests     =  7;
const int forest_size = 25;
const int mountains     =  2;
const int mountain_size = 75;

map::map() {
    srand(time( NULL ));

    //locations = new location*[256];
    for(int i=0; i<256; i++) {
        //locations[i] = new location[256];
        for(int j=0; j<256; j++) {
            location* loc = new location;
            locations[i][j] = loc;
            //printf("%d:%d,", loc->loctype, loc->style);
        }
        //printf("\n");
    }
}

map::map(const map& orig) {
}

map::~map() {
}

int map::generate() {
    int terr_type = 0;

    printf("Map builder : Generating lakes\n");
    terr_type = 1;
    for(int i=0; i<lakes; i++) {
        int lx = rand() % 256;
        int ly = rand() % 256;

        printf("Lake %d: %d, %d\n", i, lx, ly);
        flow(lx, ly, terr_type, lake_size);
    }

    printf("Map builder : Generating forests\n");
    terr_type = 2;
    for(int i=0; i<forests; i++) {
        int lx = rand() % 256;
        int ly = rand() % 256;

        printf("Forest %d: %d, %d\n", i, lx, ly);
        flow(lx, ly, terr_type, forest_size);
    }

    printf("Map builder : Generating mountains\n");
    terr_type = 3;
    for(int i=0; i<mountains; i++) {
        int lx = rand() % 256;
        int ly = rand() % 256;

        printf("Mountain %d: %d, %d\n", i, lx, ly);
        flow(lx, ly, terr_type, mountain_size);
    }

    return 0;
}

int map::flow(int x, int y, int terr_type, int iterations) {
  if(can_flow(x, y, terr_type) && (iterations > 0)) {
    if((y > 0) && ((rand() % 2) > 0)) {
        int can_go = (locations[x][y-1]->loctype == 0);
        if(can_go) {
            printf("Go %d, %d(%d)\n", x, y-1,locations[x][y-1]->loctype);
            flow(x, y-1, terr_type, iterations-1);
        }
    }
    if((x < 255) && ((rand() % 2) > 0)) {
        int can_go = (locations[x+1][y]->loctype == 0);
        if(can_go) {
            printf("Go %d, %d(%d)\n", x+1, y,locations[x+1][y]->loctype);
            flow(x+1, y, terr_type, iterations-1);
        }
    }
    if((y < 255) && ((rand() % 2) > 0)) {
        int can_go = (locations[x][y+1]->loctype == 0);
        if(can_go) {
            printf("Go %d, %d(%d)\n", x, y+1,locations[x][y+1]->loctype);
            flow(x, y+1, terr_type, iterations-1);
        }
    }
    if((x > 0) && ((rand() % 2) > 0)) {
        int can_go = (locations[x-1][y]->loctype == 0);
        if(can_go) {
            printf("Go %d, %d(%d)\n", x-1, y,locations[x-1][y]->loctype);
            flow(x-1, y, terr_type, iterations-1);
        }
    }
  }

  return 0;
}

int map::can_flow(int x, int y, int terr_type) {
    if (terr_type > 0) {
        locations[x][y]->loctype = terr_type;
        return 1;
    }
    /*
    if (build_type > 0) {
        B = build(x, y, build_type);
        return (B<>nil);
    }
    */
    return 0;
}
