#ifndef _WALL_H
#define _WALL_H

#include "Object.h"

class Wall: public Object 
{
public:
    virtual void setSquare(Grid::Square& square);

    virtual void draw() const;
};

#endif