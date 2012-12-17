#ifndef _WALL_H
#define _WALL_H

#include "BaseObject.h"

class Wall: public BaseObject 
{
public:
    virtual void setSquare(Grid::Square& square);

    virtual void draw() const;
};

#endif