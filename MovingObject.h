#ifndef _MOVING_OBJECT_H
#define _MOVING_OBJECT_H

#include "BaseObject.h"

namespace HungerGames
{

    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class MovingObject: public BaseObject
    {
    public:
        virtual void update() = 0;
        void setDirection(Direction direction);

        Direction getDirection() const;

    protected:
        Direction direction;

        Grid::Square& getNextSquare() const;
        static Grid::Square& getNextSquare(const Grid& grid, const Grid::Square& square, Direction direction);
    };

}

#endif