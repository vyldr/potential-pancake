#ifndef CHVAR_H
#define CHVAR_H

#include "definitions.h"
#include <list>

// TODO: Chvar might be waiting an extra frame before it starts.  Check on this later

// This struct contains everything we need to keep track of a variable
struct Ints {
  int startValue;
  int endValue;
  int * target;
  int currentFrame;
  int totalFrame;
};
struct Floats {
  float startValue;
  float endValue;
  float * target;
  int currentFrame;
  int totalFrame;
};

// Chvar class will take a variable and smoothly update it to a new value
// over a specified number of frames
class Chvar
{
private:
  std::list<Ints> ints;
  std::list<Floats> floats;
public:
  Chvar() {}
  void changeIt(int &start, int end, int frames);
  void changeIt(float &start, float end, int frames);
  void update();
};

#endif // CHVAR_H
