#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"

class Game;

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
    ~MovingObject();

    virtual void move(Game& game) = 0;

    Direction getDirection() const;

protected:
    Direction direction;
    int moveInterval;

    Grid::Square& getNextSquare(const Grid& grid, const Grid::Square& square, Direction direction);
};

#endif