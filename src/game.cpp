// Main file for this game

#include "include/game.h"

// Create the Game
Game::Game() : gameOver(false), xOffset(X_SIZE / 2), yOffset(Y_SIZE / 2), scale(SCALE)
{
  // Set up the map
  int intmap[X][Y]; // Create a temporary array of ints so mapgen doesn't depend on Tile
  mapgen(intmap);
  for (int x = 0; x < X; x++)
    for (int y = 0; y < Y;  y++)
    {
      map[x][y].setType(intmap[x][y]);
      map[x][y].setx(x);
      map[x][y].sety(y);

      // Set the starting base to the correct tile
      if (intmap[x][y] == -1)
      {
        map[x][y].setBase();

        // Make the view start on the base
        // xOffset = (x + 0.5) * TILE_SIZE;
        // yOffset = (y + 0.5) * TILE_SIZE;

        // Start the camera at the base
        // Position
        camera[0] = -(x + 0.5);
        camera[2] = -(y + 0.5);
        camera[1] = -0.2;
        // Angle
        camera[4] = 0;

        // Starting characters
        for (int i = 0; i < 3; i++)
          charList.push_back(Character(x, y)); // Initialize characters at the base
      }

      // Items
      if (map[x][y].getType() > 0 && map[x][y].getType() < 5)
      {
        for (int i = 0; i < random(4, 10); i++)
        {
          Item item;
          item.x = x + random(0.0, 1.0);
          item.y = y + random(0.0, 1.0);
          item.type = random(0, 2);
          items.push_back(item);
        }
      }
    }


  calculateVisibility(map); // Set initial visibility

  // Set up the models
  loadModels();
}

// advance the game one frame
void Game :: advance()
{
  // Update all the changing variables
  chvar.update();

  // Update each character
  std::list<Character>::iterator it = charList.begin();
  while (it != charList.end())
  {
    // Give the character some new instructions
    giveOrders(it);

    // Attack the current tile, if required
    attackHere(it);

    // Check if task is already done
    isTaskDone(it);

    it->advance(chvar);

    it++;
  }

}

void Game :: giveOrders(auto it)
{
  if (it->isIdle() and !taskList.empty())
  {
    it->setInstructions(findTargetTile(map, it->getX(), it->getY(), taskList.front().targetX, taskList.front().targetY));
    it->setTask(taskList.front());
    taskList.pop_front();
  }
}

void Game :: attackHere(auto it)
{
  if (it->getInstruction() == 'd' and !it->isMoving())
  {
    map[it->getX()][it->getY()].takeDamage(it->getPower());
    if (map[it->getX()][it->getY()].getType() == 0)
    {
      it->doneWithTask();
      while(restructure(map)); // Call this function until it returns false
      calculateVisibility(map);
    }
  }
}

void Game :: isTaskDone(auto it)
{
  Task task = it->getTask();
  if (map[task.targetX][task.targetY].getType() == 0)
    it->doneWithTask();
}

// Get the keypresses.  The game would be pretty boring without this
void Game :: input(const GameWindow & gameWindow)
{
  // Shift the view
  // if (gameWindow.keyUp())
  //   chvar.changeIt(yOffset, yOffset + TILE_SIZE, VIEW_SPEED);
  // if (gameWindow.keyDown())
  //   chvar.changeIt(yOffset, yOffset - TILE_SIZE, VIEW_SPEED);
  // if (gameWindow.keyLeft())
  //   chvar.changeIt(xOffset, xOffset - TILE_SIZE, VIEW_SPEED);
  // if (gameWindow.keyRight())
  //   chvar.changeIt(xOffset, xOffset + TILE_SIZE, VIEW_SPEED);
  if (gameWindow.keyUp())
  {
    float dz = 0.05 * cos(camera[4]);
    float dx = 0.05 * sin(camera[4]);

    // Make sure we don't hit a wall
    if (map[-(int)(camera[0] - dx)][-(int)(camera[2] + dz)].getType() == 0)
    {
      camera[2] += dz;
      camera[0] -= dx;
    }
  }
  if (gameWindow.keyDown())
  {
    float dz = 0.01 * cos(camera[4]);
    float dx = 0.01 * sin(camera[4]);

    // Make sure we don't hit a wall
    if (map[(int) -(camera[0] + dx)][(int) -(camera[2] - dz)].getType() == 0)
    {
      camera[2] -= dz;
      camera[0] += dx;
    }
  }
  if (gameWindow.keyLeft())
    camera[4] -= 0.02;
  if (gameWindow.keyRight())
    camera[4] += 0.02;

  // Zoom in and out
  if (gameWindow.keyPlus())
    chvar.changeIt(scale, scale * 2, VIEW_SPEED * 2);
  if (gameWindow.keyMinus())
    chvar.changeIt(scale, scale / 2, VIEW_SPEED * 2);

  // Some action
  if (gameWindow.keySpace())
    addClearOrder();
}

void Game :: addClearOrder()
{
  Task task;
  bool targetFound = false;
  for (float i = 0; i < 3; i += 0.1)
  {
    float dz = i * cos(camera[4]);
    float dx = i * sin(camera[4]);

    // Find the wall we are pointing at
    if (map[-(int)(camera[0] - dx)][-(int)(camera[2] + dz)].getType() != 0)
    {
      targetFound = true;
      task.targetX = -(int)(camera[0] - dx);
      task.targetY = -(int)(camera[2] + dz);
      break;
    }

  }

  // Don't continue if we didn't hit anything
  if (!targetFound)
    return;

  // Don't try if the target is indestructable
  if (map[task.targetX][task.targetY].getType() == 5)
    return;

  task.action = 'd';
  taskList.push_back(task);
}


// Draw the frame.  Our hard work here will last for milliseconds!
void Game :: draw() const
{
  // Draw the Tiles
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      map[i][j].draw(xOffset, yOffset, scale);

  // Draw the Characters
  {
    std::list<Character>::const_iterator it = charList.begin();
    while (it != charList.end())
    {
      it->draw(xOffset, yOffset, scale);
      it++;
    }
  }

  // Draw the Items
  {
    std::list<Item>::const_iterator it = items.begin();
    while (it != items.end())
    {
      if (!map[(int) it->x][(int) it->y].getType())
        drawItem(it->x, it->y, it->type, xOffset, yOffset, scale);
      it++;
    }
  }

  // Draw the yellow box
  drawCenterBox(scale);

}

void Game :: loadModels()
{
  // Open space
  Model model;
  Vertex ver[8];
  ver[0] = {0,0,0};
  ver[1] = {0,0,1};
  ver[2] = {0,1,0};
  ver[3] = {0,1,1};
  ver[4] = {1,0,0};
  ver[5] = {1,0,1};
  ver[6] = {1,1,0};
  ver[7] = {1,1,1};
  for (int i = 0; i < 8; i++)
  {
    model.vertices.push_back(ver[i]);
  }

  Triangle tri[4];
  tri[0] = {0,1,5};
  tri[1] = {0,5,4};
  tri[2] = {2,3,7};
  tri[3] = {2,7,6};
  for (int i = 0; i < 4; i++)
  {
    model.triangles.push_back(tri[i]);
  }
  models.push_back(model);
}

// Draw the frame in 3D.  This is better than 2D in every way
void Game :: draw3D() const
{
  setup3DFrame(camera);

  // Draw the tiles
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      if (map[i][j].isVisible())
        drawTile3D(map[i][j].getx(),
                   map[i][j].gety(), 
                   map[i][j].getType(), 
                   map[i][j].getBase(),
                   models);
      // map[i][j].draw3D();


}

// Callback function, runs once every frame
void callBack(const GameWindow *pUI, void *p)
{
  Game *pGame = (Game *)p;

  pGame->input(*pUI);
  pGame->advance();
  pGame->draw3D();
}

// Main just initializes the game and calls the display engine
int main(int argc, char ** argv)
{
  GameWindow gameWindow(argc, argv, "potential-pancake");
  Game game;
  gameWindow.run(callBack, &game);

  return 0;
}
