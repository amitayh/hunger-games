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

    DroppingObject(Type type, Grid::Square& square);
    ~DroppingObject();

    void affect(Player& player);

    void draw() const;
    bool getPickedUp() const;
    Grid::Square& getSquare() const;
    Type getType() const;

private:
    Grid::Square *pSquare;
    Type type;
    bool pickedUp;
};

#endif