#ifndef _OBJECT_H
#define _OBJECT_H

#include "Grid.h"

class Object
{
protected:
    Grid::Square* pSquare;

public:
    virtual void setSquare(Grid::Square& square);
    virtual void draw() const = 0;
};

#endif