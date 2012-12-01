#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Object.h"
#include "Player.h"

class DroppingObject : public Object
{
public:
    DroppingObject();
    ~DroppingObject();

    virtual void affect(Player& player) = 0;
    void setSquare(Grid::Square& square);

    bool getPickedUp() const;

protected:
    bool pickedUp;
};

#endif