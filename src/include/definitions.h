#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define FRAMERATE 60

#define VIEW_SPEED FRAMERATE / 8

// Please keep these odd so that one tile can be in the exact center
#define X         61
#define Y         41

#define TILE_SIZE 16

#define CHARACTER_SIZE TILE_SIZE / 8
#define CHARACTER_SPEED FRAMERATE / 2

#define ITEM_SIZE TILE_SIZE / 16.0

#define SCALE 4
// 8n + 1 Size of the window
#define X_SIZE    (TILE_SIZE * X + 1)
#define Y_SIZE    (TILE_SIZE * Y + 1)





#endif // DEFINITIONS_H
