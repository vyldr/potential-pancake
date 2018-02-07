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

}
