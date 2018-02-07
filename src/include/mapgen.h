#ifndef MAPGEN_H
#define MAPGEN_H

#include "definitions.h"


void mapgen(int map[X][Y]);
void mapgenAssignPointers(int map[X][Y]);
void mapgenChooseBase(int map[X][Y], int number);
void mapgenCleanup(int tmap1[X][Y]);
void mapgenDetails(int tmap1[X][Y]);
void mapgenFillExtra(int tmap1[X][Y]);
void mapgenInitialize(int tmap1[X][Y], int tmap2[X][Y]);
int mapgenRandom(int min, int max);
void mapgenRandomize(int tmap1[X][Y], int probability);
void mapgenSmooth(int tmap1[X][Y], int tmap2[X][Y]);
void mapgenspecials(int map[X][Y], int type);
void mapgenSetTiles(int map[X][Y], int tmap1[X][Y]);

void debugDisplay(int tmap1[X][Y]);


#endif // MAPGEN_H
