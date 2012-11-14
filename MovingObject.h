#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"

class MovingObject : public Object
{
public:
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    MovingObject();

    void Update();
    virtual void Move() {};
    void SetDirection(Direction direction);
    void SetMoveInterval(int moveInterval);
    Direction GetDirection();
    Square* GetNextSquare();

private:
    Direction direction;
    int moveInterval;
};

#endif