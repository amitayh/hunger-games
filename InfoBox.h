#ifndef _INFO_BOX_H
#define _INFO_BOX_H

#include "BaseObject.h"
#include "Dimensions.h"

namespace HungerGames
{

    class InfoBox: public BaseObject
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

}

#endif