#ifndef _WALL_H
#define _WALL_H

#include "Square.h"

class Wall
{
    Square *square;

public:
    Wall(Square &square);

    void Draw() const;
};

#endif