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
  int  shape;
  int  direction;

public:
  Tile();

  // Getters
  int  getType()      const { return type;                }
  int  getBase()      const { return base;                }
  bool isVisible()    const { return visible;             }
  bool isOpen()       const { return (visible and !type); }
  int  getx()         const { return xCoord;              }
  int  gety()         const { return yCoord;              }
  int  getShape()     const { return shape;               }
  int  getDirection() const { return direction;           }

  // Setters
  void setType(int newtype)  { type   = newtype; strength = 100 * newtype; }
  void setBase()             { base   = 1; type = 0; } // TODO: Implement more base types
  void setVisible()          { visible   = true;     }
  void setx(int newx)        { xCoord    = newx;     }
  void sety(int newy)        { yCoord    = newy;     }
  void setShape(int newSh)   { shape     = newSh;    }
  void setDirection(int dir) { direction = dir;      }


  void draw(int xOffset, int yOffset, float scale) const;
  void takeDamage(int damage);


};

void calculateVisibility(Tile map[X][Y]);
bool restructure(Tile map[X][Y]);
void calculateShape(Tile map[X][Y]);

#endif // TILE_H
