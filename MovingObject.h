#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"

enum Direction {
	UP,
    DOWN,
    LEFT,
    RIGHT
};

class Game;

class MovingObject : public Object
{
	Direction direction;
    int speed;

    void UpdatePosition(int& start, int end);
public:
    MovingObject();

    virtual void Update();
    void SetDirection(Direction direction);
    void SetSpeed(int speed);
    Direction GetDirection();
};

#endif