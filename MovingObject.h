#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"

enum ItemType {
    FOOD,
    QUIVER,
    BOMB
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class MovingObject : public Object
{
    Direction direction;
    int moveInterval;

public:
    MovingObject();

    void Update();
    virtual void Move() {};
    void SetDirection(Direction direction);
    void SetMoveInterval(int moveInterval);
    Direction GetDirection();
    Square* GetNextSquare();
};

#endif