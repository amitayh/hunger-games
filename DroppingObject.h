#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Player.h"

class DroppingObject
{
public:
    DroppingObject();
    ~DroppingObject();

    virtual void affect(Player& player) = 0;
    void setSquare(Grid::Square& square);
    
    virtual void draw() const = 0;
    bool getPickedUp() const;
    Grid::Square& getSquare() const;

protected:
    Grid::Square *pSquare;
    bool pickedUp;
};

#endif