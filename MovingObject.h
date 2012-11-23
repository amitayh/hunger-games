#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "Grid.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Grid::Square& getNextSquare(const Grid& grid, const Grid::Square& square, Direction direction);

#endif