#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Game;

class Arrow
{
    enum {
        MOVE_INTERVAL = 1
    };

    Square* pSquare;
    Direction direction;
    bool hit;

    void setSquare(Square& square);
    bool checkHit();

public:
    Arrow(Player& shooter, Square& square);
    ~Arrow();

    void update(Game& game);

    void draw() const;
    bool getHit() const;
};

#endif