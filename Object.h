#ifndef _OBJECT_H
#define _OBJECT_H

#include "Dimensions.h"
#include "Gotoxy.h"
#include <iostream>

using namespace std;

enum ObjectType {
    PLAYER,
    ARROW,
    BOMB,
    FOOD,
    QUIVER,
    WALL
};

class Square;
class Game;

class Object
{
    ObjectType type;
    Dimensions size;
    Game* game;
    Square* square;

public:
	Object();

    virtual bool Update();
    virtual void Draw() {};
    virtual bool SetSquare(Square* square);

    void GotoPosition();
    void SetType(ObjectType type);
    void SetGame(Game* game);

    ObjectType GetType();
    Dimensions* GetSize();
    Game* GetGame();
    Square* GetSquare();
};

#endif