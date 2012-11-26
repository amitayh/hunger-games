#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Arrow : public MovingObject
{
    bool hit;
    bool checkHit();

public:
    Arrow(Player& shooter);

    void setSquare(Grid::Square& square);
    void move(Game& game);

    void draw() const;
    bool getHit() const;
};

#endif