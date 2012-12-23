#ifndef _BASE_ARROW_H
#define _BASE_ARROW_H

#include "MovingObject.h"

namespace HungerGames
{

    class BaseArrow: public MovingObject
    {
    public:
        ~BaseArrow();

        virtual void setSquare(Grid::Square& square);
        virtual void update();

        bool getHit() const;

    protected:
        static const int MOVE_INTERVAL;

        BaseArrow(); // Make the class abstract

        bool hit;

        virtual bool checkHit();
    };

}

#endif