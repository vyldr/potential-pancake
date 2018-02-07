#include "include/character.h"

Character::Character(int x, int y) : xCoord(x), yCoord(y)
{
  xCoord += random(0.2, 0.8);
  yCoord += random(0.2, 0.8);
  moving = 0;
  power = 1;
  speed = random(CHARACTER_SPEED * 0.8, CHARACTER_SPEED * 1.2);
  task.targetX = 0;
  task.targetY = 0;

  //instructions.push_back('i'); // Start at idle
}

Character::~Character()
{
  // TODO: remove variables from Chvar before destroying them to prevent segfaults
  // This must be done if the character can be killed before the game ends
}

void Character::draw(int xOffset, int yOffset, float scale) const
{
  drawCharacter(xCoord, yCoord, xOffset, yOffset, scale);
}

void Character::advance(Chvar &chvar)
{
  //std::cout << instructions.top() << '\n';
  if (!moving and !instructions.empty())
  {
    switch (instructions.back()) {
      case 'n': // move up
        chvar.changeIt(xCoord, (int)xCoord + random(0.2, 0.8), speed);
        chvar.changeIt(yCoord, (int)yCoord + random(0.2, 0.8) + 1, speed);
        moving = -1; // Because of integer rounding, some positive values don't work here.  -1 should always work for a countdown
        chvar.changeIt(moving, 0, speed); // Wait until the task is finished
        instructions.pop_back();
        break;
      case 's': // move down
        chvar.changeIt(xCoord, (int)xCoord + random(0.2, 0.8), speed);
        chvar.changeIt(yCoord, (int)yCoord + random(0.2, 0.8) - 1, speed);
        moving = -1; // Because of integer rounding, some positive values don't work here.  -1 should always work for a countdown
        chvar.changeIt(moving, 0, speed); // Wait until the task is finished
        instructions.pop_back();
        break;
      case 'w': // move left
        chvar.changeIt(xCoord, (int)xCoord + random(0.2, 0.8) - 1, speed);
        chvar.changeIt(yCoord, (int)yCoord + random(0.2, 0.8), speed);
        moving = -1; // Because of integer rounding, some positive values don't work here.  -1 should always work for a countdown
        chvar.changeIt(moving, 0, speed); // Wait until the task is finished
        instructions.pop_back();
        break;
      case 'e': // move right
        chvar.changeIt(xCoord, (int)xCoord + random(0.2, 0.8) + 1, speed);
        chvar.changeIt(yCoord, (int)yCoord + random(0.2, 0.8), speed);
        moving = -1; // Because of integer rounding, some positive values don't work here.  -1 should always work for a countdown
        chvar.changeIt(moving, 0, speed); // Wait until the task is finished
        instructions.pop_back();
        break;
    }

  }
}

// Can we take new instructions?
bool Character::isIdle()
{
  if (not moving and (getInstruction() == 'i'))
    return true;
  return false;
}
