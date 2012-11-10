#ifndef _OBJECT_H
#define _OBJECT_H

#include "Dimensions.h"
#include "Gotoxy.h"
#include "Console.h"
#include <iostream>

using namespace std;

class Square;
class Game;

class Object
{
    Dimensions size;
    Game* game;
    Square* square;

    void GotoPosition();

public:
    Object();

    virtual void Draw() {};
    void SetSquare(Square* square);
    void SetGame(Game* game);
    Dimensions* GetSize();
    Game* GetGame();
    Square* GetSquare();
};

#endif