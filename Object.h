#ifndef _OBJECT_H
#define _OBJECT_H

#include "Dimensions.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

class Square;
class Game;

class Object
{
    Dimensions size;
    Game* game;
    Square* square;

public:
	Object();

    virtual bool Update();
    virtual void Draw() {};
    virtual void SetSquare(Square* square);

    void GotoPosition();
    void SetGame(Game* game);

    Dimensions* GetSize();
    Game* GetGame();
    Square* GetSquare();
};

#endif