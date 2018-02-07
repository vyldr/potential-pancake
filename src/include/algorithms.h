#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "definitions.h"
#include "tile.h"
#include <list>
#include <vector>
#include <iostream>

// A simple coordinate pair
struct Pair
{
  int x;
  int y;
};

// These will set up a generic array of ints that mark targets, obstacles, and open spaces
std::list<char> findTargetTile(Tile map[X][Y], int startx, int starty, int endx, int endy);
// TODO: Add findItem(), findBase(), etc

// Get the location of the nearest target
Pair             findNearest(int tmap[X][Y], int startx, int starty);

// Create a stack of instructions to the target
std::list<char> getPath(int map[X][Y], std::list<char> instructions, Pair nearest);

// Simple text display of the map
void display(int map[X][Y]);

// Generate random numbers
int algorithmRandom(int min, int max);

#endif
