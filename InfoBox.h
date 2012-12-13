#ifndef _INFO_BOX_H
#define _INFO_BOX_H

#include "Object.h"
#include "Dimensions.h"

class InfoBox: public Object
{
    static const int WIDTH;
    static const int HEIGHT;

    Dimensions size;

public:
    InfoBox();

    virtual void setSquare(Grid::Square& square);

    virtual void draw() const;
    bool inArea(const Grid::Square& square) const;
};

#endif