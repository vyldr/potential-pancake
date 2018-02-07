#include "include/algorithms.h"


std::list<char> findTargetTile(Tile map[X][Y], int startx, int starty, int endx, int endy)
{
  std::list<char> instructions;
  instructions.push_back('d'); // Damage

  int tmap[X][Y];

  // Mark the possible path tiles, obstacles, and targets
  for (int x = 0; x < X; x++)
    for (int y = 0; y < Y;  y++)
    {
      tmap[x][y] = -3; // Nothing should end up with this value
      switch (map[x][y].getType()) {

        // Possible path
        case 0:
          tmap[x][y] = 0;
          break;

        // Obstacle
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          tmap[x][y] = -1;
          break;

        // Target
          //tmap[x][y] = -2;
          //break;
      }
    }

    // Target
    tmap[endx][endy] = -2;

  // We might be there already
  if (tmap[startx][starty] == -2)
    return instructions;

  tmap[startx][starty] = 1; // Set start position

  return getPath(tmap, instructions, findNearest(tmap, startx, starty));
}

Pair findNearest(int map[X][Y], int x, int y)
{
  int found = false; // Did we find any? If so, how far?

  // This will be the list of nearest targets
  std::vector<Pair> nearest;

  // This will hold the possible path spaces that have yet to be checked
  std::list<Pair> queue;

  // Set the starting point
  Pair start = {x, y};
  queue.push_back(start);

  while (!queue.empty()) // loop until there is nothing else to check
  {
    int x = queue.front().x;
    int y = queue.front().y;
    queue.pop_front();

    // Check surrounding spaces
    for (int i = -1; i <= 1; i++)          // | 010 | From the x and y values we want to look up, down, left,
      for (int j = -1; j <= 1; j++)        // | 101 | and right.  The for loops will give us a 3*3 grid and the
        if ((i * j == 0) and (i + j != 0)) // | 010 | if statement filters out the corners and the center.
        {
          // Possible path
          if ((map[x + i][y + j] == 0) && !found)
          {
            Pair checkLater = {x + i, y + j};
            queue.push_back(checkLater);
            map[x + i][y + j] = map[x][y] + 1;
          }

          // Target found!
          if (map[x + i][y + j] == -2)
          {
            if (!found) // First one!
              found = map[x][y] + 1; // Set the distance
            if (found == map[x][y] + 1) // This is as close as the closest one
            {
              Pair target = {x + i, y + j};
              nearest.push_back(target);
              map[x + i][y + j] = map[x][y] + 1;
            }
          }
        }
  }

  if (!nearest.size())
  {
    return {x, y};
  }
  return nearest[algorithmRandom(0, nearest.size())]; // Randomly choose one to pathfind for
}

std::list<char> getPath(int map[X][Y], std::list<char> instructions, Pair position)
{
  int direction = 0;
  while (map[position.x][position.y] != 1)
  {
    /*  We are going to spin in place until the space in front of us is part of
     *  the path.  This will make the path have a zig-zag shape when we need to
     *  move diagonally.  Since We work backward from the end, we must add the
     *  opposite instruction each time.
     */
    direction++;
    //direction = algorithmRandom(0, 4); // This gives an interesting effect when there are hundreds of characters
    switch (direction % 4) {
      case 0: // North
        if (map[position.x][position.y] == map[position.x][position.y + 1] + 1)
        {
          instructions.push_back('s');
          position.y += 1;
        }
        break;
      case 1: // East
        if (map[position.x][position.y] == map[position.x + 1][position.y] + 1)
        {
          instructions.push_back('w');
          position.x += 1;
        }
        break;
      case 2: // South
        if (map[position.x][position.y] == map[position.x][position.y - 1] + 1)
        {
          instructions.push_back('n');
          position.y -= 1;
        }
        break;
      case 3: // West
        if (map[position.x][position.y] == map[position.x - 1][position.y] + 1)
        {
          instructions.push_back('e');
          position.x -= 1;
        }
        break;
    }
  }
  return instructions;
}

// Simple text display of the map
void display(int tmap1[X][Y])
{
  for (int i = Y - 1; i >= 0; i--)
  {
    for (int j = 0; j < X; j++)
    {
      if (tmap1[j][i] == 5)
        std::cout << "\E[30;47m" << tmap1[j][i] << "\033[0m"; // Change and reset the background color
      else if (tmap1[j][i] == 0)
        std::cout << "  ";
      else
        std::cout << tmap1[j][i];
    }
    std::cout << '\n';
  }
  std::cout << '\n';


}



// Generate a random number within a specified range
int algorithmRandom(int min, int max)
{
  if (min == max)
    return min;
  return ((rand() % (max - min)) + min);
}
