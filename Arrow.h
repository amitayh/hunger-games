#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Game;

class Arrow
{
    enum {
        MOVE_INTERVAL = 1
    };

    Grid::Square* pSquare;
    Direction direction;
    bool hit;

    void setSquare(Grid::Square& square);
    bool checkHit();

public:
    Arrow(Player& shooter, Grid::Square& square);
    ~Arrow();

    void update(Game& game);

    void draw() const;
    bool getHit() const;
};

#endif