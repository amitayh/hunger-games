#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"
#include "Grid.h"

class Game;

class MovingObject : public Object
{
public:
    virtual void update(Game& game) = 0;
};

/////////////////////////////////////////////////////////////////////

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Grid::Square& getNextSquare(const Grid& grid, const Grid::Square& square, Direction direction);

#endif