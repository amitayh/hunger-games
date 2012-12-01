#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Arrow : public MovingObject
{
    enum {
        MOVE_INTERVAL = 1
    };

    bool hit;

    bool checkHit();

public:
    Arrow(Player& shooter, Grid::Square& square);
    ~Arrow();

    void setSquare(Grid::Square& square);
    void update(Game& game);

    void draw() const;
    bool getHit() const;
};

#endif