#include "include/tile.h"


// Constructor
Tile::Tile()
{
  base     = 0;
  type     = 100; // If any type ends up with a value of 100, we know that the real value was never set
  strength = 0;
  visible  = false;
}

// Give the display function everything it needs to draw the tile
void Tile::draw(int xOffset, int yOffset, float scale) const
{
  if (visible)
    drawTile(xCoord, yCoord, xOffset, yOffset, scale, type, base);
}

// Reduce the strength.  Destroy if strength hits 0
void Tile::takeDamage(int damage)
{
  strength -= damage;
  if (strength <= 0)
  {
    strength = 0;
    type = 0;
  }
}

// This function will decide what tiles should be marked as visible.  It starts at the base spreads out from there until it runs out of open spaces.
void calculateVisibility(Tile map[X][Y])
{
  struct Pair
  {
    int x;
    int y;
  };

  std::list<Pair> queue;
  int intmap[X][Y]; // Create a temporary array to work with
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
    {
      // Fill in the int array
      intmap[i][j] = map[i][j].getType();

      // Find the starting point
      if (map[i][j].getBase())
      {
        Pair base = {i, j};
        queue.push_back(base);
      }
    }

  while (!queue.empty()) // loop until there is nothing else to check
  {
    // Get the coordinates to work with
    int x = queue.front().x;
    int y = queue.front().y;
    queue.pop_front();

    // Check surrounding spaces
    for (int i = -1; i <= 1; i++)   // | 010 | From the x and y values we want to look up, down, left,
      for (int j = -1; j <= 1; j++)//  | 111 | and right.  The for loops will give us a 3*3 grid
      {
        map[x + i][y + j].setVisible();
        if (intmap[x + i][y + j] == 0)
        {
          intmap[x + i][y + j] = 1; // So it won't go in the queue again
          Pair pair = {x + i, y + j};
          queue.push_back(pair);
        }
      }

  }

  calculateShape(map);
}

// This function will restructure the map so that no wall sections are alone
bool restructure(Tile map[X][Y])
{
  bool changed = false;

  // Check every non-border tile
  for (int i = 1; i < X - 1; i++)
    for (int j = 1; j < Y - 1; j++)
    {
      // Only check visible non-ground tiles
      if (map[i][j].isVisible() and map[i][j].getType())
      {
        // Check if the tile has two open tiles on opposite sides
        if ((map[i - 1][j].isOpen() and map[i + 1][j].isOpen()) or 
            (map[i][j - 1].isOpen() and map[i][j + 1].isOpen()))
            {
              map[i][j].setType(0);
              changed = true;
            }
      }
    }
  return changed;
}

// Determine the 3D model to use for each tile
void calculateShape(Tile map[X][Y])
{
  
  for (int i = 1; i < X - 1; i++)
    for (int j = 1; j < Y - 1; j++)
    {
        map[i][j].setShape(0);
        map[i][j].setDirection(0);
      // Only check visible non-ground tiles
      if (map[i][j].isVisible() and map[i][j].getType())
      {
        // Check the bordering spaces
        bool b[3][3];
        for (int k = 0; k < 3; k++)
          for (int l = 0; l < 3; l++)
            b[k][l] = map[i + k - 1][j + l - 1].isOpen();

        /* Explanation of the following mess
         *
         * This will check which bordering tiles are 'open'
         * and use that to determine the correct shape and model
         * and then determine the direction to rotate it
         * 
         * Shapes:
         *   1   2   3   4 
         *  --- --- --- ---
         * |## |###| ##|###|
         * |#* |#*#|#*#|#*#|
         * |   |   |## |## |
         *  --- --- --- ---
         */


        // Check for two open edges
        if ((b[0][1] and b[1][2]) or 
            (b[1][2] and b[2][1]) or 
            (b[2][1] and b[1][0]) or 
            (b[1][0] and b[0][1]))
        {
          map[i][j].setShape(1);
          if (b[0][1] and b[1][2])
            map[i][j].setDirection(0);
          else if (b[1][2] and b[2][1])
            map[i][j].setDirection(1);
          else if (b[2][1] and b[1][0])
            map[i][j].setDirection(2);
          else if (b[1][0] and b[0][1])
            map[i][j].setDirection(3);
        }

        // Check for one open edge
        else if ((b[0][1]) or 
                 (b[1][2]) or 
                 (b[2][1]) or 
                 (b[1][0]))
        {
          map[i][j].setShape(2);
          if (b[0][1])
            map[i][j].setDirection(0);
          else if (b[1][2])
            map[i][j].setDirection(1);
          else if (b[2][1])
            map[i][j].setDirection(2);
          else if (b[1][0])
            map[i][j].setDirection(3);
        }

        // // Check for two corners
        // else if ((b[0][0] and b[2][2]) or
        //           b[0][2] and b[2][0])
        // {
        //   map[i][j].setShape(4);
        //   if (b[0][0])
        //     map[i][j].setDirection(0);
        //   else if (b[0][2])
        //     map[i][j].setDirection(1);
        // }

        // Check for one corner
        else 
        {
          map[i][j].setShape(3);
          if (b[0][0])
            map[i][j].setDirection(0);
          else if (b[0][2])
            map[i][j].setDirection(1);
          else if (b[2][2])
            map[i][j].setDirection(2);
          else if (b[2][0])
            map[i][j].setDirection(3);
        }
      }
    }
}