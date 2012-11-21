#ifndef _WALL_H
#define _WALL_H

#include "Square.h"

class Wall
{
    Square* pSquare;

public:
    Wall(Square& square);

    void draw() const;
};

#endif