#ifndef _INFO_BOX_H
#define _INFO_BOX_H

#include "Object.h"
#include "Dimensions.h"

class InfoBox : public Object
{
    enum {
        WIDTH = 10,
        HEIGHT = 5
    };

    Dimensions size;

public:
    InfoBox();

    void setSquare(Grid::Square& square);

    void draw() const;
    bool inArea(const Grid::Square& square) const;
};

#endif