#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Object.h"
#include "Player.h"

class DroppingObject : public Object
{
    bool pickedUp;

public:
    DroppingObject();
    ~DroppingObject();

    void DroppingObject::SetSquare(Square* square);
    virtual void Affect(Player* player);
    bool GetPickedUp();
};

#endif