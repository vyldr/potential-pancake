#ifndef TILE_H
#define TILE_H

#include "definitions.h"
#include "uiDraw.h"
#include <iostream>
#include <list>


class Tile
{
private:
  int  xCoord;
  int  yCoord;
  int  type;
  int  base;
  int  strength;
  bool visible;

public:
  Tile();

  // Getters
  int  getType()   const    { return   type;    }
  int  getBase()   const    { return   base;    }
  bool isVisible() const    { return   visible; }

  // Setters
  void setType(int newtype) { type   = newtype; strength = 100 * newtype; }
  void setx(int newx)       { xCoord = newx;        }
  void sety(int newy)       { yCoord = newy;        }
  void setBase()            { base   = 1; type = 0; } // TODO: Implement more base types
  void setVisible()         { visible = true;       }


  void draw(int xOffset, int yOffset, float scale) const;
  void takeDamage(int damage);


};

void calculateVisibility(Tile map[X][Y]);

#endif // TILE_H
