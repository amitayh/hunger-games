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

    Square *square;
    Dimensions size;

public:
    InfoBox();

    void SetSquare(Square *square);
    void Draw(List &players) const;
    const Dimensions& GetSize() const;
    bool InArea(const Square *square) const;
};

#endif