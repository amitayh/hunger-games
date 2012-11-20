#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Player.h"

class DroppingObject
{
public:
    enum Type {
        FOOD,
        QUIVER,
        BOMB
    };

    DroppingObject(Type type, Square *square);
    ~DroppingObject();

    void Affect(Player &player);
    Square *GetSquare();

    void Draw() const;
    bool GetPickedUp() const;
    Type GetType() const;

private:
    Square *square;
    Type type;
    bool pickedUp;
};

#endif