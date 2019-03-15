#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <math.h>

#include "definitions.h"

#include "algorithms.h"
#include "mapgen.h"

#include "uiInteract.h"
#include "uiDraw.h"

#include "chvar.h"
#include "character.h"
#include "tile.h"
#include "task.h"
#include "item.h"
#include "model.h"

class Game
{
private:
    bool gameOver;
    Tile map[X][Y];
    std::list<Character> charList;
    std::list<Task> taskList;
    std::list<Item> items;
    std::vector<Model> models;
    int xOffset;
    int yOffset;
    float scale;
    Chvar chvar;
    float camera[6];
    // TODO: list of priorities


  public:
    // handle user input
    void input(const GameWindow & gameWindow);

    // advance the game
    void advance();

    // draw stuff
    void draw() const;

    // draw stuff in 3D!
    void draw3D() const;

    // create the game
    Game();

    void loadModels();

    void giveOrders(auto it);
    void attackHere(auto it);
    void isTaskDone(auto it);

    void addClearOrder();
};

#endif // GAME_H
