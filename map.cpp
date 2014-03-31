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
    for(int i=0; i<max_x; i++) {
        //locations[i] = new location[256];
        for(int j=0; j<max_y; j++) {
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
        int lx = rand() % max_x;
        int ly = rand() % max_y;

        printf("Lake %d: %d, %d\n", i, lx, ly);
        flow(lx, ly, terr_type, lake_size);
    }

    printf("Map builder : Generating forests\n");
    terr_type = 2;
    for(int i=0; i<forests; i++) {
        int lx = rand() % max_x;
        int ly = rand() % max_y;

        printf("Forest %d: %d, %d\n", i, lx, ly);
        flow(lx, ly, terr_type, forest_size);
    }

    printf("Map builder : Generating mountains\n");
    terr_type = 3;
    for(int i=0; i<mountains; i++) {
        int lx = rand() % max_x;
        int ly = rand() % max_y;

        printf("Mountain %d: %d, %d\n", i, lx, ly);
        flow(lx, ly, terr_type, mountain_size);
    }

    return 0;
}

int map::save(const char* filename)
{
    unsigned short int mapsize[] = {max_x, max_y};

    char item_size  = 0;
    char block_size = 0;

    FILE* f = fopen(filename, "w+");

    item_size  = sizeof(unsigned short int);
    block_size = sizeof(mapsize) / item_size;
    fwrite(mapsize, item_size, block_size, f);

    char locdata[4];
    item_size  = sizeof(char);
    block_size = sizeof(locdata) / item_size;

    for(int j=0; j<max_y; j++)
    {
        for(int i=0; i<max_x; i++)
        {
            location* loc = locations[i][j];

            locdata[0] = loc->loctype;
            locdata[1] = loc->style;
            locdata[2] = loc->object;
            locdata[3] = 0;

            printf("Locdata %d, %d \n", item_size, block_size);

            fwrite(locdata, item_size, block_size, f);
        }
    }

    fclose(f);

    return 0;
}

int map::load(const char* filename)
{
    unsigned short int mapsize[2];

    char item_size  = 0;
    char block_size = 0;

    FILE* f = fopen(filename, "r");

    item_size  = sizeof(unsigned short int);
    block_size = sizeof(mapsize) / item_size;
    fread(mapsize, item_size, block_size, f);

    char locdata[4];
    item_size  = sizeof(char);
    block_size = sizeof(locdata) / item_size;

    for(int j=0; j<max_y; j++)
    {
        for(int i=0; i<max_x; i++)
        {
            fread(locdata, item_size, block_size, f);

            location* loc = locations[i][j];
            loc->loctype = locdata[0];
            loc->style   = locdata[1];
            loc->object  = locdata[2];
        }
    }

    fclose(f);

    return 0;
}

int map::flow(int x, int y, int terr_type, int iterations) {
  if(can_flow(x, y, terr_type) && (iterations > 0)) {
    if((y > 0) && ((rand() % 2) > 0)) {
        int can_go = (locations[x][y-1]->loctype == 0);
        if(can_go) {
            // printf("Go %d, %d(%d)\n", x, y-1,locations[x][y-1]->loctype);
            flow(x, y-1, terr_type, iterations-1);
        }
    }
    if((x < (max_x-1)) && ((rand() % 2) > 0)) {
        int can_go = (locations[x+1][y]->loctype == 0);
        if(can_go) {
            // printf("Go %d, %d(%d)\n", x+1, y,locations[x+1][y]->loctype);
            flow(x+1, y, terr_type, iterations-1);
        }
    }
    if((y < (max_y-1)) && ((rand() % 2) > 0)) {
        int can_go = (locations[x][y+1]->loctype == 0);
        if(can_go) {
            // printf("Go %d, %d(%d)\n", x, y+1,locations[x][y+1]->loctype);
            flow(x, y+1, terr_type, iterations-1);
        }
    }
    if((x > 0) && ((rand() % 2) > 0)) {
        int can_go = (locations[x-1][y]->loctype == 0);
        if(can_go) {
            // printf("Go %d, %d(%d)\n", x-1, y,locations[x-1][y]->loctype);
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
