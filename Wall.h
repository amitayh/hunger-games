#ifndef _WALL_H
#define _WALL_H

#include "Grid.h"

class Wall
{
    Grid::Square* pSquare;

public:
    Wall(Grid::Square& square);

    void draw() const;
};

#endif