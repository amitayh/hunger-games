#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Object.h"
#include "Grid.h"

class Game;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class MovingObject : public Object
{
public:
    virtual void update(Game& game) = 0;

    Direction getDirection() const;

protected:
    Direction direction;

    Grid::Square& getNextSquare(const Grid& grid) const;
    static Grid::Square& getNextSquare(const Grid& grid, const Grid::Square& square, Direction direction);
};

#endif