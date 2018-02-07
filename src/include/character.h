#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <list>
#include "uiDraw.h"
#include "chvar.h"
#include "task.h"
//#include "game.h"
//class Game;

class Character
{
private:
  float xCoord;
  float yCoord;
  std::list<char> instructions;
  Task task;
  int moving; // How long will we be working on the current task
  int power;
  int speed;

public:
  Character(int x, int y);
  ~Character();
  void draw(int xOffset, int yOffset, float scale) const;
  void advance(Chvar &chvar);

  bool isIdle();
  bool isMoving() { return moving; }

  void doneWithTask() { instructions.clear(); }

  // Getters
  int  getX()           { return xCoord;             }
  int  getY()           { return yCoord;             }
  char getInstruction() { if (!instructions.empty()) return instructions.back(); else return 'i'; }
  int  getPower()       { return power;              }
  Task getTask()        { return task; }

  // Setters
  void setInstructions(std::list<char> newInstructions) { instructions = newInstructions; }
  void setTask(Task nTask) {task = nTask; }


};






#endif // CHARACTER_H
