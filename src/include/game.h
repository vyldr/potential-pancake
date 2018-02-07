#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>

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

class Game
{
private:
    bool gameOver;
    Tile map[X][Y];
    std::list<Character> charList;
    std::list<Task> taskList;
    std::list<Item> items;
    int xOffset;
    int yOffset;
    float scale;
    Chvar chvar;
    // TODO: list of priorities


  public:
    // handle user input
    void input(const GameWindow & gameWindow);

    // advance the game
    void advance();

    // draw stuff
    void draw() const;

    // create the game
    Game();

    void giveOrders(auto it);
    void attackHere(auto it);
    void isTaskDone(auto it);

    void addClearOrder();
};

#endif // GAME_H
