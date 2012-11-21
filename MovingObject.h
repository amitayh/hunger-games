#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Grid.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Square& getNextSquare(const Grid& grid, const Square& square, Direction direction);

#endif