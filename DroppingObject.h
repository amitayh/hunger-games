#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Object.h"
#include "Player.h"

class DroppingObject: public Object
{
public:
    enum Type {
        FOOD,
        QUIVER,
        BOMB
    };

    DroppingObject();
    ~DroppingObject();

    virtual void affect(Player& player) = 0;
    virtual void setSquare(Grid::Square& square);

    bool getPickedUp() const;
    Type getType() const;

protected:
    bool pickedUp;
    Type type;
};

#endif