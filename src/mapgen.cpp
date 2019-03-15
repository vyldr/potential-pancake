#include <iostream>
#include "include/mapgen.h"

void mapgen(int map[X][Y])
{
  // Create the variables
  int tmap1[X][Y];
  int tmap2[X][Y];

  // Initialize the arrays
  mapgenInitialize(tmap1, tmap2);

  // Generate random noise
  mapgenRandomize(tmap1, mapgenRandom(50, 65));  // This value changes the density of the noise

  // Refine map
  mapgenSmooth(tmap1, tmap2);

/* Remove small bits
 * Called twice because the first time misses some.
 *   example:
 *
 *    +------+    +------+    +------+    +------+
 *    |   #  |    |   +  |    |      |    |      |
 *    | #### | -> | #+#+ | -> | + +  | -> |      |
 *    | # #  |    | + +  |    |      |    |      |
 *    +------+    +------+    +------+    +------+
 *
 */
  mapgenCleanup(tmap1);
  mapgenCleanup(tmap1);

  // Fill in inaccessable areas
  mapgenFillExtra(tmap1);

  // Set the tiles
  mapgenSetTiles(map, tmap1);

  // Finished the base map, starting the destructable part
  // This part starts with the same functions
  mapgenRandomize(tmap1, mapgenRandom(30, 60));  // This value changes the density of the noise
  mapgenSmooth(tmap1, tmap2);
  mapgenCleanup(tmap1);
  mapgenCleanup(tmap1);

  // Finally something different!
  // Add the details
  mapgenDetails(tmap1);
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      if (map[i][j] != 5)
        map[i][j] = tmap1[i][j];

  mapgenspecials(map, 6);
  mapgenspecials(map, 7);
  //mapgenspecials(map, 8);

  //debugDisplay(tmap1);

  mapgenChooseBase(map, 1);
}

void mapgenChooseBase(int map[X][Y], int number)
{
  for (number; number > 0; number--)
  {
    int x = 0;
    int y = 0;
    while(map[x][y])   // Repeat until a space is found
    {                    //   There is a negligible chance of no valid spaces
      x = mapgenRandom(0, X);
      y = mapgenRandom(0, Y);
    }
    map[x][y] = -1;
  }
}

void mapgenCleanup(int tmap1[X][Y])
{
  for (int i = 1; i < X - 1; i++)
    for (int j = 1; j < Y - 1; j++)
    {
      if(((tmap1[i - 1][j] == 0) and (tmap1[i + 1][j] == 0)) or ((tmap1[i][j - 1] == 0) and (tmap1[i][j + 1] == 0)))
        tmap1[i][j] = 0;
    }
}

void mapgenFillExtra(int tmap1[X][Y])
{
  int tmap[X][Y];
  int record = 0;

  // Copy the tmap
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      if (tmap1[i][j])
        tmap[i][j] = -1;
      else
        tmap[i][j] = 0;

  // Search for open spaces and record their size
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      if (!tmap[i][j])  // Opening found
      {
        tmap[i][j] = -2;  // Arbitrary negative number
        int size = 1;
        bool change = true;
        while (change)
        {
          change = false;
          for (int k = 1; k < X - 1; k++)
            for (int l = 1; l < Y - 1; l++)
              if ((!tmap[k][l])   // Space connected to current opening
                and ((tmap[k + 1][l] == -2)
                or  (tmap[k - 1][l] == -2)
                or  (tmap[k][l + 1] == -2)
                or  (tmap[k][l - 1] == -2)))
              {
                change = true;
                size++;
                tmap[k][l] = -2;
              }
        }
        if (size > record)  // Update record if necessary
          record = size;
        for (int k = 1; k < X; k++)  // Update spaces with their size
          for (int l = 1; l < Y; l++)
            if (tmap[k][l] == -2)
              tmap[k][l] = size;
      }

  // Close all but the largest opening and write back to tmap1
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      if (tmap[i][j] == record)
        tmap1[i][j] = 0;
      else
        tmap1[i][j] = 5;
}

void mapgenInitialize(int tmap1[X][Y], int tmap2[X][Y])
{
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
    {
      tmap1[i][j] = 5;
      tmap2[i][j] = 5;
    }
}

int mapgenRandom(int min, int max)
{
  return ((rand() % (max - min)) + min);
}

void mapgenRandomize(int tmap1[X][Y], int probability)
{
  for (int i = 2; i < X - 2; i++) // Keep a margin of 2 to make processing the map easier
    for (int j = 2; j < Y - 2; j++)
      if(mapgenRandom(0, 100) <= probability)
        tmap1[i][j] = 0;
      else
        tmap1[i][j] = 5;
}

void mapgenSmooth(int tmap1[X][Y], int tmap2[X][Y])
{
  for (int a = 0; a < 10; a++)
  {
    for (int i = 1; i < X - 1; i++)
      for (int j = 1; j < Y - 1; j++)
      {
        // Count adjacent spaces
        int c = 0;
        if (tmap1[i + 1][j] == 5)
          c++;
        if (tmap1[i - 1][j] == 5)
          c++;
        if (tmap1[i][j + 1] == 5)
          c++;
        if (tmap1[i][j - 1] == 5)
          c++;

        // Change values
        if (c <= 0)
          tmap2[i][j] = 0;
        else if (c >= 3)
          tmap2[i][j] = 5;
        else
          tmap2[i][j] = tmap1[i][j];
      }

      // Copy map back
      for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
        {
          tmap1[i][j] = tmap2[i][j];
        }
  }

}

void mapgenSetTiles(int map[X][Y], int tmap1[X][Y])
{
  for (int i = 0; i < X; i += 1)
    for (int j = 0; j < Y; j += 1)
    {
      map[i][j] = tmap1[i][j];
    }
}

void mapgenDetails(int tmap1[X][Y])
{
  // Set type equal to distance from edge
  for (int n = 0; n < 12; n++)
    for (int i = 1; i < X - 1; i++)
      for (int j = 1; j < Y - 1; j++)
        if (((tmap1[i - 1][j] == (n / 3)) or
             (tmap1[i + 1][j] == (n / 3)) or
             (tmap1[i][j - 1] == (n / 3)) or
             (tmap1[i][j + 1] == (n / 3)))
            and (tmap1[i][j] == 5))
          tmap1[i][j] = (n / 3 + 1);

  // Set remaining values
  for (int i = 1; i < X - 1; i++)
    for (int j = 1; j < Y - 1; j++)
      if (tmap1[i][j] == 5)
        tmap1[i][j] = 4;

  // Randomize type to +/- 1 within map borders
  for (int i = 1; i < X - 1; i++)
    for (int j = 1; j < Y - 1; j++)
      switch (tmap1[i][j])
      {
        case 1:
          tmap1[i][j] = mapgenRandom(1, 3);
          break;
        case 2:
          tmap1[i][j] = mapgenRandom(1, 4);
          break;
        case 3:
          tmap1[i][j] = mapgenRandom(2, 5);
          break;
        case 4:
          tmap1[i][j] = mapgenRandom(3, 5);
          break;
        default:
          break;
      }
}

void debugDisplay(int tmap1[X][Y])
{
  for (int i = 0; i < X; i++)
  {
    for (int j = 0; j < Y; j++)
    {
      if (tmap1[i][j] >= 0)
        std::cout << tmap1[i][j];
      else
        std::cout << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void mapgenspecials(int map[X][Y], int type)
{
  int specialCount = 0;
  int maximum = mapgenRandom(0, (X * Y / 256));  // Maximum based on map size
  while (specialCount <= maximum)
  {
    int specialX = mapgenRandom(0, X);
    int specialY = mapgenRandom(0, Y);
    if ((map[specialX][specialY] >= 1) and (map[specialX][specialY] <= 4))
    {
      map[specialX][specialY] = type;
      specialCount++;
    }
  }

}
