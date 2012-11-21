#ifndef _INFO_BOX_H
#define _INFO_BOX_H

#include "Square.h"
#include "Dimensions.h"

class InfoBox
{
    enum {
        WIDTH = 10,
        HEIGHT = 5
    };

    Square* pSquare;
    Dimensions size;

public:
    InfoBox();

    void setSquare(Square& square);

    void draw(const List& players) const;
    const Dimensions& getSize() const;
    bool inArea(const Square& square) const;
};

#endif