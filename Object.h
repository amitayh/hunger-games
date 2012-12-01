#ifndef _OBJECT_H
#define _OBJECT_H

#include "Grid.h"

class Object
{
public:
    Object();
    ~Object();

    virtual void setSquare(Grid::Square& square);
    
    virtual void draw() const = 0;
    Grid::Square& getSquare() const;

protected:
    Grid::Square *pSquare;
};

#endif