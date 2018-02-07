#include <iostream>
#include "include/chvar.h"

// TODO: maybe use templates to reduce code duplication

void Chvar::changeIt(int &start, int end, int frames)
{
  // Check if it is already there
  std::list<Ints>::iterator it = ints.begin();
  while (it != ints.end())
  {
    if (it->target == &start)
      return;
    it++;
  }
  Ints addNew;
  addNew.startValue = start;
  addNew.endValue = end;
  addNew.target = &start;
  addNew.currentFrame = 0;
  addNew.totalFrame = frames;
  ints.push_back(addNew);
  //std::cout << start << ' ' << end << '\n'; // Debug
}
void Chvar::changeIt(float &start, float end, int frames)
{
  std::list<Floats>::iterator it = floats.begin();
  while (it != floats.end())
  {
    if (it->target == &start)
      return;
    it++;
  }
  Floats addNew;
  addNew.startValue = start;
  addNew.endValue = end;
  addNew.target = &start;
  addNew.currentFrame = 0;
  addNew.totalFrame = frames;
  floats.push_back(addNew);
}
void Chvar::update()
{
  // Integers:
{
  // Iterate through the list
  std::list<Ints>::iterator it = ints.begin();
  while (it != ints.end())
  {
    // Remove the entry if it is done
    if (!(it->totalFrame - it->currentFrame))
    {
      //std::cout << it->startValue << ' ' << it->endValue << '\n'; // Debug
      *(it->target) = it->endValue;  //  Set the actual variable to the final value at the end just to be sure
      ints.erase(it++);
    }
    // Update the entry
    else
    {
      float inc = (it->endValue - it->startValue) / it->totalFrame;  //  Calculate the amount to increment
      *(it->target) = it->startValue + inc * ++it->currentFrame; //  Change the actual variable to its current value
      it++;
    }
  }
}

  // Floats:
  {
    // Iterate through the list
    std::list<Floats>::iterator it = floats.begin();
    while (it != floats.end())
    {
      // Remove the entry if it is done
      if (!(it->totalFrame - it->currentFrame))
      {
        //std::cout << it->startValue << ' ' << it->endValue << '\n'; // Debug
        *(it->target) = it->endValue;  //  Set the actual variable to the final value at the end just to be sure
        floats.erase(it++);
      }
      // Update the entry
      else
      {
        float inc = (it->endValue - it->startValue) / it->totalFrame;  //  Calculate the amount to increment
        *(it->target) = it->startValue + inc * ++it->currentFrame; //  Change the actual variable to its current value
        it++;
      }
    }
  }
}
