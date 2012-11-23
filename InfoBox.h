#ifndef _INFO_BOX_H
#define _INFO_BOX_H

#include "Grid.h"
#include "Dimensions.h"

class InfoBox
{
    enum {
        WIDTH = 10,
        HEIGHT = 5
    };

    Grid::Square* pSquare;
    Dimensions size;

public:
    InfoBox();

    void setSquare(Grid::Square& square);

    void draw(const List& players) const;
    const Dimensions& getSize() const;
    bool inArea(const Grid::Square& square) const;
};

#endif