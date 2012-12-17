#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "BaseObject.h"

class BasePlayer;

class DroppingObject: public BaseObject
{
public:
    enum Type {
        FOOD,
        QUIVER,
        BOMB
    };

    DroppingObject();
    ~DroppingObject();

    virtual void affect(BasePlayer& player) = 0;
    virtual void setSquare(Grid::Square& square);

    bool getPickedUp() const;
    Type getType() const;

protected:
    bool pickedUp;
    Type type;
};

#endif